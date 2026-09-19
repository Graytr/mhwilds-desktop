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
  Opt_<List>_<N>_Arrow   the arrow shown next to options that open something to the right.
  group Menus            every list meter (hidden together).
  group Menu_<List>      the meters of one list (shown together).
  group Icons            the six icons.
  group Panels           every panel meter; group Panel_<Name> one panel.
  group <Name>Measures   a panel's measures, enabled only while it is showing.
  MeterTitle, MeterIconGlow, MeterCursor, MeterPulse   the shared indicator meters.
  MeasureAnim            ActionTimer: list 1 glides the glow, list 2 the dot (AnimStep /
                         AnimDone per meter), list 3 is the hover fall-back delay (RevertHover),
                         list 4 fades the click flash (PulseStep / PulseDone).
  mFileList, mFile<N>Name, FileRow<N>, FileIcon<N>, FileName<N>   the file list panel.

Layout (mirrors the in-game tent menu)
  * A menu's list sits in the first column. An option whose MenuAction is
    OpenSubmenu('<List>') opens that list in a second column to the right, and the
    first column stays open. Panels (file list, Now Playing, ...) open right of the
    deepest open column; the script moves them by setting the PanelX variable.
  * Hovering an icon selects it: the glow glides behind it, it tints and the title
    changes. The selection stays when the mouse leaves; it does not follow the mouse.
  * Clicking an icon opens its menu: the icon stays lit, option 1 is selected and
    the dot glides from the icon down to the left end of the selected bar.
    Clicking the same icon again closes everything, panels included.
  * Hovering an option previews it: its bar lights up and the dot moves there. When the
    mouse leaves, the highlight falls back to the options that were actually clicked.
  * Clicking an option selects it for good, closes any panel (and, from the first
    column, any sub-menu) and runs its MenuAction.
  * BackMenu() (right-click on any option) closes the sub-menu; with none open it
    closes the menu.

Set DebugLog=1 in Variables.inc to have the script narrate in the Rainmeter log.
]]

local openMenu       = nil   -- root list (the icon's) that is open, or nil
local subMenu        = nil   -- sub-menu list open in the second column, or nil
local selectedIcon   = nil   -- icon the glow rests on, or nil
local selectedOption = {}    -- [list] = option the user clicked (1 when the list opens)
local shownOption    = {}    -- [list] = option currently highlighted (hover preview or selection)
local hovered        = nil   -- { list = ..., idx = ... } for the option under the mouse, or nil
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

local function isOpen(list) return list ~= nil and (list == openMenu or list == subMenu) end

-- the list whose selection the dot rests on when nothing is hovered
local function deepest() return subMenu or openMenu end

-- x of a list's bars: the root list sits in the first column, a sub-menu in the second
local function listX(list)
  if subMenu and list == subMenu then return num('SubOptionsX') end
  return num('OptionsX')
end

local function setTitle(text)
  bang('[!SetOption MeterTitle Text "' .. text .. '"][!UpdateMeter MeterTitle]')
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
-- the glow (behind icons), the dot and the click flash (on option bars)
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

-- top-left corner of the dot when it sits on the left end of option bar idx of a list
-- (bars may be hidden, so their geometry comes from the variables, not the meters)
local function dotHome(list, idx)
  local r = num('CursorHaloRadius')
  return listX(list) + num('CursorInsetX') - r,
         num('OptionY' .. idx) + num('OptionH') / 2 - r
end

local function moveDot(list, idx) glide('MeterCursor', dotHome(list, idx)) end

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

-- light up option idx of a list (bar artwork and label); the dot moves separately
local function showBar(list, idx)
  local prev = shownOption[list]
  if prev == idx then return end
  if prev then styleBar(list, prev, false) end
  shownOption[list] = idx
  styleBar(list, idx, true)
end

-- click feedback: a white flash over the clicked bar that fades out (MeasureAnim list 4)
local pulseFrame, pulseFrames = 0, 10

local function pulseShape(alpha)
  return '[!SetOption MeterPulse Shape "Rectangle 0,0,#OptionSelectedW#,#OptionH#,3 | Fill Color 255,255,255,' .. alpha .. ' | StrokeWidth 0"]'
end

local function pulse(list, idx)
  pulseFrame, pulseFrames = 0, math.max(1, num('PulseFrames'))
  bang('[!SetOption MeterPulse X ' .. listX(list) .. '][!SetOption MeterPulse Y "#OptionY' .. idx .. '#"]'
    .. pulseShape(num('PulsePeakAlpha'))
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
-- panels: the area to the right of the open columns
-- -----------------------------------------------------------------------------

-- panels whose measures should only run while they are showing
local panelMeasures = { NowPlaying = 'NowPlayingMeasures', Status = 'StatusMeasures' }
-- measures that must re-read their position before the panel is used
local panelUpdate = { Run = 'mRun' }

function HidePanels()
  if openPanel and panelMeasures[openPanel] then
    bang('[!DisableMeasureGroup ' .. panelMeasures[openPanel] .. ']')
  end
  openPanel = nil
  bang('[!HideMeterGroup Panels][!Redraw]')
end

-- name is the part after Panel_ in the group name: FileList, NowPlaying, Status, Run
function ShowPanel(name)
  -- the panel sits right of the deepest open column; the panel meters read PanelX dynamically
  bang('[!SetVariable PanelX ' .. (subMenu and num('PanelXFar') or num('PanelXNear')) .. ']')
  if openPanel ~= name then
    if openPanel and panelMeasures[openPanel] then
      bang('[!DisableMeasureGroup ' .. panelMeasures[openPanel] .. ']')
    end
    bang('[!HideMeterGroup Panels]')
    openPanel = name
    if panelMeasures[name] then
      bang('[!EnableMeasureGroup ' .. panelMeasures[name] .. '][!UpdateMeasureGroup ' .. panelMeasures[name] .. ']')
    end
    bang('[!ShowMeterGroup Panel_' .. name .. ']')
    log('panel ' .. name)
  end
  if panelUpdate[name] then bang('[!UpdateMeasure ' .. panelUpdate[name] .. ']') end
  bang('[!UpdateMeterGroup Panel_' .. name .. '][!Redraw]')
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
-- lists: a menu in the first column, at most one sub-menu in the second
-- -----------------------------------------------------------------------------

local function showList(list)
  bang('[!ShowMeterGroup Menu_' .. list .. '][!UpdateMeterGroup Menu_' .. list .. ']')
end

local function hideList(list)
  if shownOption[list] then styleBar(list, shownOption[list], false) end
  shownOption[list], selectedOption[list] = nil, nil
  bang('[!HideMeterGroup Menu_' .. list .. ']')
end

local function closeSubmenu()
  if not subMenu then return end
  hideList(subMenu)
  subMenu = nil
  HidePanels()
end

local function closeOpenMenu()
  if not openMenu then return end
  closeSubmenu()
  hideList(openMenu)
  hovered = nil
  stopGlide('MeterCursor')
  HidePanels()
  bang('[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Stop 4"]'
    .. '[!HideMeter MeterCursor][!HideMeter MeterPulse]')
  openMenu = nil
end

-- -----------------------------------------------------------------------------
-- entry points called from the INI
-- -----------------------------------------------------------------------------

-- OnRefreshAction: everything closed, nothing selected.
function Reset()
  debugLog = num('DebugLog') == 1
  frames = math.max(1, num('AnimFrames'))
  openMenu, subMenu, selectedIcon, openPanel, hovered = nil, nil, nil, nil, nil
  selectedOption, shownOption, tweens = {}, {}, {}
  bang('[!CommandMeasure MeasureAnim "Stop 1"][!CommandMeasure MeasureAnim "Stop 2"]'
    .. '[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Stop 4"]'
    .. '[!HideMeterGroup Menus][!HideMeterGroup Panels][!HideMeter MeterPulse]'
    .. '[!DisableMeasureGroup NowPlayingMeasures][!DisableMeasureGroup StatusMeasures]'
    .. '[!HideMeter MeterIconGlow][!HideMeter MeterCursor]'
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
  selectedIcon, openMenu = menu, menu
  setTitle(SKIN:GetMeter('Icon_' .. menu):GetOption('MenuTitle'))
  showList(menu)
  -- the dot starts on the icon and glides down to the first option
  local cx, cy = iconCentre(menu)
  local r = num('CursorHaloRadius')
  place('MeterCursor', cx - r, cy - r)
  bang('[!ShowMeter MeterCursor]')
  selectedOption[menu] = 1
  showBar(menu, 1)
  moveDot(menu, 1)
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

-- open a sub-menu in the second column (a MenuAction: OpenSubmenu('Pouch'))
function OpenSubmenu(list)
  if not openMenu or list == openMenu or list == subMenu then return end
  closeSubmenu()
  subMenu = list
  showList(list)
  selectedOption[list] = 1
  showBar(list, 1)
  moveDot(list, 1)   -- the dot glides from the clicked option across to the first sub-option
  bang('!Redraw')
  log('opened sub-menu ' .. list)
end

-- close the sub-menu; with none open, close the menu (right-click does this too)
function BackMenu()
  if not openMenu then return end
  if not subMenu then CloseMenu() return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hovered = nil
  closeSubmenu()
  moveDot(openMenu, selectedOption[openMenu] or 1)
  bang('!Redraw')
  log('closed sub-menu')
end

-- the mouse is over an option: preview it
function HoverOption(section)
  local list, idx = parse(section)
  if not idx or not isOpen(list) then return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hovered = { list = list, idx = idx }
  showBar(list, idx)
  moveDot(list, idx)
  bang('!Redraw')
end

-- the mouse left an option: after a short delay the highlight falls back to the
-- clicked options (the delay lets the mouse cross the gap between two bars)
function LeaveOption(section)
  local list, idx = parse(section)
  if not idx or not isOpen(list) then return end
  if hovered and hovered.list == list and hovered.idx == idx then hovered = nil end
  bang('[!CommandMeasure MeasureAnim "Stop 3"][!CommandMeasure MeasureAnim "Execute 3"]')
end

-- called by MeasureAnim list 3 once the delay has passed
function RevertHover()
  if hovered or not openMenu then return end
  for _, list in ipairs({ openMenu, subMenu }) do
    showBar(list, selectedOption[list] or 1)
  end
  local list = deepest()
  moveDot(list, selectedOption[list] or 1)
  bang('!Redraw')
  log('highlight back to the clicked options')
end

-- click: this option becomes the real selection, any panel closes (and, from the
-- first column, any sub-menu too), then its action runs
function ClickOption(section)
  local list, idx = parse(section)
  if not idx or not isOpen(list) then return end
  bang('[!CommandMeasure MeasureAnim "Stop 3"]')
  hovered = { list = list, idx = idx }
  selectedOption[list] = idx
  showBar(list, idx)
  moveDot(list, idx)
  pulse(list, idx)
  if list == openMenu then closeSubmenu() end   -- a first-column click also drops the sub-menu
  HidePanels()                                   -- and any panel, whichever column was clicked
  local action = SKIN:GetMeter('Opt_' .. list .. '_' .. idx):GetOption('MenuAction')
  log('click ' .. list .. ' option ' .. idx .. ' -> ' .. action)
  if action and action ~= '' then bang(action) end
end
