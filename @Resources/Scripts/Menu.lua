--[[
Menu.lua - all menu state for the Monster Hunter Wilds camp menu.

The INI files only describe how things look. Every mouse action calls one of the
functions in this file, for example:
    MouseOverAction=[!CommandMeasure MenuScript "HoverIcon('#CURRENTSECTION#')"]

Naming conventions the script depends on
  Icon_<Menu>            a main-menu icon. Custom option MenuTitle = the header text.
  Opt_<List>_<N>         option bar N of a list. Custom option MenuAction = the bang(s) to
                         run when it is clicked, e.g. MenuAction=["shell:Downloads"].
                         A list is either a menu (same name as its icon) or a sub-menu.
  Opt_<List>_<N>_Text    the label drawn on top of that bar.
  #Menu_<List>_Title#    variable holding a sub-menu's header text.
  group Menus            every list meter (hidden together).
  group Menu_<List>      the meters of one list (shown together).
  group Icons            the six icons.
  group Panels           every panel meter; group Panel_<Name> one panel.
  group <Name>Measures   a panel's measures, enabled only while it is showing.
  MeterTitle, MeterIconGlow, MeterCursor, MeterChevron   the shared indicator meters.
  MeasureAnim            ActionTimer: list 1 glides the glow, list 2 the dot (AnimStep /
                         AnimDone per meter), list 3 is the hover fall-back delay (RevertHover),
                         list 4 fades the click flash (PulseStep / PulseDone).
  MeterPulse             white flash drawn over the clicked option bar.
  mFileList, mFile<N>Name, FileRow<N>, FileIcon<N>, FileName<N>   the file list panel.

Behaviour (mirrors the in-game tent menu)
  * Hovering an icon selects it: the glow glides behind it, it tints and the title
    changes. The selection stays when the mouse leaves; it does not follow the mouse.
  * Clicking an icon opens its menu: the icon stays lit, option 1 is selected and
    the dot glides from the icon down to the left end of the selected bar.
    Clicking the same icon again closes everything, panels included.
  * Hovering an option previews it: bar highlight, chevron and dot move there. When the
    mouse leaves, the highlight falls back to the option that was actually clicked.
  * Clicking an option selects it for good and runs its MenuAction. Panels open to the
    right of the options.
  * A MenuAction of OpenSubmenu('<List>') replaces the list with that sub-menu, like the
    game drilling down. BackMenu() (also right-click on any option) returns to the parent
    list with its selection intact; at the top level it closes the menu.

Set DebugLog=1 in Variables.inc to have the script narrate in the Rainmeter log.
]]

local openMenu       = nil   -- root menu (the icon's) whose lists are showing, or nil
local listStack      = {}    -- open lists, root first; the last one is on screen
local selectedIcon   = nil   -- icon the glow rests on, or nil
local selectedOption = {}    -- [list] = option the user clicked (1 when the list opens)
local shownOption    = {}    -- [list] = option currently highlighted (hover preview or selection)
local hoveredOption  = nil   -- option under the mouse right now, or nil
local openPanel      = nil   -- panel showing to the right, or nil

local debugLog = false

-- -----------------------------------------------------------------------------
-- helpers
-- -----------------------------------------------------------------------------

local function bang(s) SKIN:Bang(s) end

local function log(s) if debugLog then print('Menu.lua: ' .. s) end end

-- Numeric value of a skin variable. Variables.inc writes sizes as fully
-- parenthesised formulas such as (4*#SizeMultiplier#); this evaluates them.
local function num(name)
  local s = SKIN:ReplaceVariables('#' .. name .. '#')
  local n = tonumber(s)
  if n then return n end
  if s:sub(1, 1) ~= '(' or s:sub(-1) ~= ')' then s = '(' .. s .. ')' end
  return SKIN:ParseFormula(s)
end

-- 'Icon_ItemBox' -> 'ItemBox'      'Opt_Pouch_2_Text' -> 'Pouch', 2
local function parse(section)
  local menu = section:match('^Icon_(%w+)$')
  if menu then return menu end
  local list, idx = section:match('^Opt_(%w+)_(%d+)')
  return list, tonumber(idx)
end

local function currentList() return listStack[#listStack] end

local function setTitle(text)
  bang('[!SetOption MeterTitle Text "' .. text .. '"][!UpdateMeter MeterTitle]')
end

-- header text for a list: the icon's MenuTitle for a menu, the Menu_<List>_Title
-- variable for a sub-menu
local function listTitle(list)
  if list == openMenu then return SKIN:GetMeter('Icon_' .. list):GetOption('MenuTitle') end
  local t = SKIN:ReplaceVariables('#Menu_' .. list .. '_Title#')
  if t:find('#', 1, true) then return list end   -- no title variable defined
  return t
end

-- tintVar is the name of a colour variable, e.g. 'IconTintHover'
local function tintIcon(menu, tintVar)
  bang('[!SetOption Icon_' .. menu .. ' ImageTint "#' .. tintVar .. '#"][!UpdateMeter Icon_' .. menu .. ']')
end

-- -----------------------------------------------------------------------------
-- movement: meters either jump or glide to a target position
-- -----------------------------------------------------------------------------

local tweens   = {}                                  -- [meter] = { x0, y0, x1, y1, frame }
local frames   = 12                                  -- frames per glide (AnimFrames)
local animList = { MeterIconGlow = 1, MeterCursor = 2 }   -- MeasureAnim list per meter

local function place(meter, x, y)
  bang('[!SetOption ' .. meter .. ' X ' .. x .. '][!SetOption ' .. meter .. ' Y ' .. y .. '][!UpdateMeter ' .. meter .. ']')
end

-- Start (or retarget) a glide from wherever the meter is right now, so rapid
-- hovering never snaps.
local function glide(meter, x, y)
  local m = SKIN:GetMeter(meter)
  local tw = tweens[meter]
  if tw and tw.x1 == x and tw.y1 == y then return end                -- already heading there
  if not tw and m:GetX() == x and m:GetY() == y then return end      -- already there, not moving
  tweens[meter] = { x0 = m:GetX(), y0 = m:GetY(), x1 = x, y1 = y, frame = 0 }
  log(('glide %s from %.0f,%.0f to %.0f,%.0f'):format(meter, m:GetX(), m:GetY(), x, y))
  local list = animList[meter]
  bang('[!CommandMeasure MeasureAnim "Stop ' .. list .. '"][!CommandMeasure MeasureAnim "Execute ' .. list .. '"]')
end

local function stopGlide(meter)
  tweens[meter] = nil
  bang('[!CommandMeasure MeasureAnim "Stop ' .. animList[meter] .. '"]')
end

local function easeOut(t) return 1 - (1 - t) ^ 3 end

-- called by MeasureAnim once per frame
function AnimStep(meter)
  local tw = tweens[meter]
  if not tw then return end
  tw.frame = tw.frame + 1
  local t = easeOut(math.min(tw.frame / frames, 1))
  place(meter, tw.x0 + (tw.x1 - tw.x0) * t, tw.y0 + (tw.y1 - tw.y0) * t)
  bang('!Redraw')
end

-- called by MeasureAnim after the last frame: land exactly on the target
function AnimDone(meter)
  local tw = tweens[meter]
  if not tw then return end
  tweens[meter] = nil
  place(meter, tw.x1, tw.y1)
  bang('!Redraw')
  log(meter .. ' glide done after ' .. tw.frame .. ' frames')
end

-- -----------------------------------------------------------------------------
-- the glow (behind icons) and the dot (on option bars)
-- -----------------------------------------------------------------------------

local function iconCentre(menu)
  local m = SKIN:GetMeter('Icon_' .. menu)
  return m:GetX() + m:GetW() / 2, m:GetY() + m:GetH() / 2
end

-- move the glow behind an icon; it glides if it is already showing
local function placeGlow(menu)
  local cx, cy = iconCentre(menu)
  local r = num('IconGlowRadius')
  if selectedIcon then
    glide('MeterIconGlow', cx - r, cy - r)
  else
    place('MeterIconGlow', cx - r, cy - r)
    bang('[!ShowMeter MeterIconGlow]')
  end
end

-- top-left corner of the dot when it sits on the left end of option bar idx
-- (bars may be hidden, so their geometry comes from the variables, not the meters)
local function dotHome(idx)
  local r = num('CursorHaloRadius')
  return num('OptionsX') + num('CursorInsetX') - r,
         num('OptionY' .. idx) + num('OptionH') / 2 - r
end

-- selected = true gives the bar the highlighted artwork, width and label colour
local function styleBar(list, idx, selected)
  local bar = 'Opt_' .. list .. '_' .. idx
  local img = selected and '#BarImageSelected#' or '#BarImageNormal#'
  local w   = selected and '#OptionSelectedW#' or '#OptionW#'
  local col = selected and '#OptionTextColorSelected#' or '#OptionTextColor#'
  local alpha = selected and '#BarSelectedAlpha#' or '255'
  bang('[!SetOption ' .. bar .. ' ImageName "' .. img .. '"][!SetOption ' .. bar .. ' W "' .. w .. '"]'
    .. '[!SetOption ' .. bar .. ' ImageAlpha "' .. alpha .. '"]'
    .. '[!SetOption ' .. bar .. '_Text FontColor "' .. col .. '"]'
    .. '[!UpdateMeter ' .. bar .. '][!UpdateMeter ' .. bar .. '_Text]')
end

-- move the highlight (bar artwork, chevron, dot) to option idx of a list
local function highlight(list, idx)
  local prev = shownOption[list]
  if prev == idx then return end
  if prev then styleBar(list, prev, false) end
  shownOption[list] = idx
  styleBar(list, idx, true)
  bang('[!SetOption MeterChevron Y "#OptionY' .. idx .. '#"][!ShowMeter MeterChevron][!UpdateMeter MeterChevron]')
  glide('MeterCursor', dotHome(idx))
end

-- click feedback: a white flash over the clicked bar that fades out (MeasureAnim list 4)
local pulseFrame, pulseFrames = 0, 10

local function pulseShape(alpha)
  return '[!SetOption MeterPulse Shape "Rectangle 0,0,#OptionSelectedW#,#OptionH#,3 | Fill Color 255,255,255,' .. alpha .. ' | StrokeWidth 0"]'
end

local function pulse(idx)
  pulseFrame, pulseFrames = 0, math.max(1, num('PulseFrames'))
  bang('[!SetOption MeterPulse Y "#OptionY' .. idx .. '#"]' .. pulseShape(num('PulsePeakAlpha'))
    .. '[!ShowMeter MeterPulse][!UpdateMeter MeterPulse][!Redraw]'
    .. '[!CommandMeasure MeasureAnim "Stop 4"][!CommandMeasure MeasureAnim "Execute 4"]')
end

-- called by MeasureAnim list 4 once per frame: fade the flash out
function PulseStep()
  pulseFrame = pulseFrame + 1
  local left = 1 - math.min(pulseFrame / pulseFrames, 1)
  bang(pulseShape(math.floor(num('PulsePeakAlpha') * left * left)) .. '[!UpdateMeter MeterPulse][!Redraw]')
end

function PulseDone()
  bang('[!HideMeter MeterPulse][!Redraw]')
end

-- -----------------------------------------------------------------------------
-- panels: the area to the right of the options
-- -----------------------------------------------------------------------------

-- panels whose measures should only run while they are showing
local panelMeasures = { NowPlaying = 'NowPlayingMeasures', Status = 'StatusMeasures' }

function HidePanels()
  if openPanel and panelMeasures[openPanel] then
    bang('[!DisableMeasureGroup ' .. panelMeasures[openPanel] .. ']')
  end
  openPanel = nil
  bang('[!HideMeterGroup Panels][!Redraw]')
end

-- name is the part after Panel_ in the group name: FileList, NowPlaying, Status, Run
function ShowPanel(name)
  if openPanel ~= name then
    if openPanel and panelMeasures[openPanel] then
      bang('[!DisableMeasureGroup ' .. panelMeasures[openPanel] .. ']')
    end
    bang('[!HideMeterGroup Panels]')
    openPanel = name
    if panelMeasures[name] then
      bang('[!EnableMeasureGroup ' .. panelMeasures[name] .. '][!UpdateMeasureGroup ' .. panelMeasures[name] .. ']')
    end
    bang('[!ShowMeterGroup Panel_' .. name .. '][!UpdateMeterGroup Panel_' .. name .. ']')
    log('panel ' .. name)
  end
  bang('!Redraw')
end

-- Point the file list at a folder and show it.
--   source   name of a variable holding the folder, e.g. 'GamesPath', or of a measure
--            whose string value is the folder, e.g. 'mDownloadsPath' (a name, not a path,
--            so backslashes never have to survive a Lua string). An empty path lists
--            the drives.
--   sort     Name, Size, Type or Date (Date lists newest first)
--   title    header text
--   exts     optional filter such as 'lnk;url'; empty or nil shows every file
function ShowFolder(source, sort, title, exts)
  sort = sort or 'Name'
  local m = SKIN:GetMeasure(source)
  local path = m and m:GetStringValue() or ('#' .. source .. '#')
  bang('[!SetOption mFileList Path "' .. path .. '"]'
    .. '[!SetOption mFileList SortType "' .. sort .. '"]'
    .. '[!SetOption mFileList SortAscending "' .. (sort == 'Date' and '0' or '1') .. '"]'
    .. '[!SetOption mFileList Extensions "' .. (exts or '') .. '"]'
    .. '[!SetOption PanelFileListTitle Text "' .. (title or 'Files') .. '"]'
    .. '[!UpdateMeasure mFileList][!CommandMeasure mFileList Update]')
  ShowPanel('FileList')
end

-- file list rows: FileRow3, FileIcon3 and FileName3 all mean row 3
local function rowOf(section) return tonumber(section:match('(%d+)$')) end

local function tintRow(n, colour)
  bang('[!SetOption FileRow' .. n .. ' Shape "Rectangle 0,0,#PanelInnerW#,#FileRowH#,3 | Fill Color ' .. colour .. ' | StrokeWidth 0"]'
    .. '[!UpdateMeter FileRow' .. n .. '][!Redraw]')
end

function FileRowHover(section)
  local n = rowOf(section)
  if n then tintRow(n, '#RowHoverColor#') end
end

function FileRowLeave(section)
  local n = rowOf(section)
  if n then tintRow(n, '0,0,0,1') end
end

-- open the file or shortcut on that row, or step into the folder
function FileRowClick(section)
  local n = rowOf(section)
  if not n then return end
  local name = SKIN:GetMeasure('mFile' .. n .. 'Name'):GetStringValue()
  if name == '' then return end
  log('open ' .. name)
  bang('[!CommandMeasure mFile' .. n .. 'Name FollowPath][!UpdateMeasure mFileList]')
end

-- dir is -1 (up) or 1 (down)
function FileListScroll(dir)
  local cmd = (tonumber(dir) or 1) < 0 and 'IndexUp' or 'IndexDown'
  bang('[!CommandMeasure mFileList ' .. cmd .. '][!UpdateMeasure mFileList]'
    .. '[!UpdateMeasureGroup FileListChildren][!UpdateMeterGroup Panel_FileList][!Redraw]')
end

function FileListBack()
  bang('[!CommandMeasure mFileList PreviousFolder][!UpdateMeasure mFileList]')
end

function FileListOpen()
  local path = SKIN:GetMeasure('mFileList'):GetStringValue()
  if path ~= '' then bang('["' .. path .. '"]') end
end

-- -----------------------------------------------------------------------------
-- lists: a menu and its sub-menus
-- -----------------------------------------------------------------------------

local function showList(list)
  bang('[!ShowMeterGroup Menu_' .. list .. '][!UpdateMeterGroup Menu_' .. list .. ']')
  setTitle(listTitle(list))
end

local function hideList(list)
  if shownOption[list] then styleBar(list, shownOption[list], false) end
  shownOption[list] = nil
  bang('[!HideMeterGroup Menu_' .. list .. ']')
end

local function closeOpenMenu()
  if not openMenu then return end
  for i = #listStack, 1, -1 do hideList(listStack[i]) end
  listStack, selectedOption, shownOption, hoveredOption = {}, {}, {}, nil
  stopGlide('MeterCursor')
  HidePanels()
  bang('[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Stop 4"]'
    .. '[!HideMeter MeterCursor][!HideMeter MeterChevron][!HideMeter MeterPulse]')
  openMenu = nil
end

-- -----------------------------------------------------------------------------
-- entry points called from the INI
-- -----------------------------------------------------------------------------

-- OnRefreshAction: everything closed, nothing selected.
function Reset()
  debugLog = num('DebugLog') == 1
  frames = math.max(1, num('AnimFrames'))
  openMenu, selectedIcon, openPanel, hoveredOption = nil, nil, nil, nil
  listStack, selectedOption, shownOption, tweens = {}, {}, {}, {}
  bang('[!CommandMeasure MeasureAnim "Stop 1"][!CommandMeasure MeasureAnim "Stop 2"]'
    .. '[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Stop 4"]'
    .. '[!HideMeterGroup Menus][!HideMeterGroup Panels][!HideMeter MeterPulse]'
    .. '[!DisableMeasureGroup NowPlayingMeasures][!DisableMeasureGroup StatusMeasures]'
    .. '[!HideMeter MeterIconGlow][!HideMeter MeterCursor][!HideMeter MeterChevron]'
    .. '[!SetOptionGroup Icons ImageTint "#IconTintNormal#"][!SetOption MeterTitle Text ""]'
    .. '[!UpdateMeter *][!Redraw]')
  log('reset')
end

function HoverIcon(section)
  local menu = parse(section)
  if not menu then return end
  if openMenu then
    -- a menu is open: just a light hover highlight, the selection stays put
    if menu ~= openMenu then tintIcon(menu, 'IconTintHover') end
  elseif menu ~= selectedIcon then
    if selectedIcon then tintIcon(selectedIcon, 'IconTintNormal') end
    tintIcon(menu, 'IconTintHover')
    setTitle(SKIN:GetMeter(section):GetOption('MenuTitle'))
    placeGlow(menu)
    selectedIcon = menu
    log('selected icon ' .. menu)
  end
  bang('!Redraw')
end

function LeaveIcon(section)
  local menu = parse(section)
  if not menu then return end
  -- with no menu open the selection stays on the icon, like the game
  if openMenu and menu ~= openMenu then
    tintIcon(menu, 'IconTintNormal')
    bang('!Redraw')
  end
end

function ClickIcon(section)
  local menu = parse(section)
  if not menu then return end
  if openMenu == menu then CloseMenu() else OpenMenu(menu) end
end

function OpenMenu(menu)
  closeOpenMenu()
  if selectedIcon and selectedIcon ~= menu then tintIcon(selectedIcon, 'IconTintNormal') end
  tintIcon(menu, 'IconTintSelected')
  placeGlow(menu)
  selectedIcon, openMenu, listStack = menu, menu, { menu }
  showList(menu)
  -- the dot starts on the icon and glides down to the first option
  local cx, cy = iconCentre(menu)
  local r = num('CursorHaloRadius')
  place('MeterCursor', cx - r, cy - r)
  bang('[!ShowMeter MeterCursor]')
  selectedOption[menu] = 1
  highlight(menu, 1)
  bang('!Redraw')
  log('opened ' .. menu)
end

function CloseMenu()
  if not openMenu then return end
  local menu = openMenu
  closeOpenMenu()
  tintIcon(menu, 'IconTintHover')   -- back to "selected but not open"
  bang('!Redraw')
  log('closed ' .. menu)
end

-- replace the current list with a sub-menu (a MenuAction: OpenSubmenu('Pouch'))
function OpenSubmenu(list)
  local parent = currentList()
  if not parent or list == parent then return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hoveredOption = nil
  hideList(parent)
  listStack[#listStack + 1] = list
  showList(list)
  selectedOption[list] = 1
  highlight(list, 1)   -- the dot glides from the clicked option to the first sub-option
  bang('!Redraw')
  log('opened sub-menu ' .. list)
end

-- one level up; at the top level this closes the menu (right-click does this too)
function BackMenu()
  if not openMenu then return end
  if #listStack <= 1 then CloseMenu() return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hoveredOption = nil
  hideList(currentList())
  listStack[#listStack] = nil
  local parent = currentList()
  showList(parent)
  highlight(parent, selectedOption[parent] or 1)
  bang('!Redraw')
  log('back to ' .. parent)
end

-- the mouse is over an option: preview it
function HoverOption(section)
  local list, idx = parse(section)
  if not idx or list ~= currentList() then return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hoveredOption = idx
  if shownOption[list] ~= idx then
    highlight(list, idx)
    bang('!Redraw')
  end
end

-- the mouse left an option: after a short delay the highlight falls back to the
-- clicked option (the delay lets the mouse cross the gap between two bars)
function LeaveOption(section)
  local list, idx = parse(section)
  if not idx or list ~= currentList() then return end
  if hoveredOption == idx then hoveredOption = nil end
  bang('[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Execute 3"]')
end

-- called by MeasureAnim list 3 once the delay has passed
function RevertHover()
  local list = currentList()
  if not list or hoveredOption then return end
  local sel = selectedOption[list] or 1
  if shownOption[list] ~= sel then
    highlight(list, sel)
    bang('!Redraw')
    log('highlight back to option ' .. sel)
  end
end

-- click: this option becomes the real selection, then its action runs
function ClickOption(section)
  local list, idx = parse(section)
  if not idx or list ~= currentList() then return end
  selectedOption[list] = idx
  highlight(list, idx)
  pulse(idx)
  local action = SKIN:GetMeter('Opt_' .. list .. '_' .. idx):GetOption('MenuAction')
  log('click ' .. list .. ' option ' .. idx .. ' -> ' .. action)
  if action and action ~= '' then bang(action) end
end
