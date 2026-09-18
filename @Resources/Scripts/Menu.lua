--[[
Menu.lua - all menu state for the Monster Hunter Wilds camp menu.

The INI files only describe how things look. Every mouse action calls one of the
functions in this file, for example:
    MouseOverAction=[!CommandMeasure MenuScript "HoverIcon('#CURRENTSECTION#')"]

Naming conventions the script depends on
  Icon_<Menu>            a main-menu icon. Custom option MenuTitle = the header text.
  Opt_<Menu>_<N>         option bar N of that menu. Custom option MenuAction = the
                         bang(s) to run when it is clicked, e.g. MenuAction=["shell:Downloads"]
  Opt_<Menu>_<N>_Text    the label drawn on top of that bar.
  group Menus            every sub-menu meter (hidden together).
  group Menu_<Menu>      the meters of one sub-menu (shown together).
  group Icons            the six icons.
  group Panels           every panel meter; group Panel_<Name> one panel.
  group <Name>Measures   a panel's measures, enabled only while it is showing.
  MeterTitle, MeterIconGlow, MeterCursor, MeterChevron   the shared indicator meters.
  MeasureAnim            ActionTimer whose list 1 glides the glow and list 2 the dot,
                         calling AnimStep(meter) per frame and AnimDone(meter) at the end.
  mFileList, mFile<N>Name, FileRow<N>, FileIcon<N>, FileName<N>   the file list panel.

Behaviour (mirrors the in-game tent menu)
  * Hovering an icon selects it: the glow glides behind it, it tints and the title
    changes. The selection stays when the mouse leaves; it does not follow the mouse.
  * Clicking an icon opens its menu: the icon stays lit, option 1 is selected and
    the dot glides from the icon down to the left end of the selected bar.
    Clicking the same icon again closes the menu (and any panel).
  * Hovering an option selects it: bar highlight and chevron jump, the dot glides.
  * Clicking an option runs its MenuAction. Panels open to the right of the options.

Set DebugLog=1 in Variables.inc to have the script narrate in the Rainmeter log.
]]

local openMenu       = nil   -- menu whose options are showing, or nil
local selectedIcon   = nil   -- icon the glow rests on, or nil
local selectedOption = {}    -- [menu] = index of the highlighted option bar
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

-- 'Icon_ItemBox' -> 'ItemBox'      'Opt_ItemBox_2_Text' -> 'ItemBox', 2
local function parse(section)
  local menu = section:match('^Icon_(%w+)$')
  if menu then return menu end
  local m, idx = section:match('^Opt_(%w+)_(%d+)')
  return m, tonumber(idx)
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
  if m:GetX() == x and m:GetY() == y then return end   -- already there
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
local function styleBar(menu, idx, selected)
  local bar = 'Opt_' .. menu .. '_' .. idx
  local img = selected and '#BarImageSelected#' or '#BarImageNormal#'
  local w   = selected and '#OptionSelectedW#' or '#OptionW#'
  local col = selected and '#OptionTextColorSelected#' or '#OptionTextColor#'
  bang('[!SetOption ' .. bar .. ' ImageName "' .. img .. '"][!SetOption ' .. bar .. ' W "' .. w .. '"]'
    .. '[!SetOption ' .. bar .. '_Text FontColor "' .. col .. '"]'
    .. '[!UpdateMeter ' .. bar .. '][!UpdateMeter ' .. bar .. '_Text]')
end

local function selectOption(menu, idx)
  local prev = selectedOption[menu]
  if prev and prev ~= idx then styleBar(menu, prev, false) end
  selectedOption[menu] = idx
  styleBar(menu, idx, true)
  bang('[!SetOption MeterChevron Y "#OptionY' .. idx .. '#"][!ShowMeter MeterChevron][!UpdateMeter MeterChevron]')
  glide('MeterCursor', dotHome(idx))
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
--            so backslashes never have to survive a Lua string)
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
-- menus
-- -----------------------------------------------------------------------------

local function closeOpenMenu()
  if not openMenu then return end
  local menu = openMenu
  if selectedOption[menu] then styleBar(menu, selectedOption[menu], false) end
  selectedOption[menu] = nil
  stopGlide('MeterCursor')
  HidePanels()
  bang('[!HideMeterGroup Menu_' .. menu .. '][!HideMeter MeterCursor][!HideMeter MeterChevron]')
  openMenu = nil
end

-- -----------------------------------------------------------------------------
-- entry points called from the INI
-- -----------------------------------------------------------------------------

-- OnRefreshAction: everything closed, nothing selected.
function Reset()
  debugLog = num('DebugLog') == 1
  frames = math.max(1, num('AnimFrames'))
  openMenu, selectedIcon, selectedOption, tweens, openPanel = nil, nil, {}, {}, nil
  bang('[!CommandMeasure MeasureAnim "Stop 1"][!CommandMeasure MeasureAnim "Stop 2"]'
    .. '[!HideMeterGroup Menus][!HideMeterGroup Panels]'
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
  setTitle(SKIN:GetMeter('Icon_' .. menu):GetOption('MenuTitle'))
  placeGlow(menu)
  selectedIcon, openMenu = menu, menu
  bang('[!ShowMeterGroup Menu_' .. menu .. '][!UpdateMeterGroup Menu_' .. menu .. ']')
  -- the dot starts on the icon and glides down to the first option
  local cx, cy = iconCentre(menu)
  local r = num('CursorHaloRadius')
  place('MeterCursor', cx - r, cy - r)
  bang('[!ShowMeter MeterCursor]')
  selectOption(menu, 1)
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

function HoverOption(section)
  local menu, idx = parse(section)
  if not idx or menu ~= openMenu then return end
  if selectedOption[menu] ~= idx then
    selectOption(menu, idx)
    bang('!Redraw')
  end
end

function ClickOption(section)
  local menu, idx = parse(section)
  if not idx or menu ~= openMenu then return end
  local action = SKIN:GetMeter('Opt_' .. menu .. '_' .. idx):GetOption('MenuAction')
  log('click ' .. menu .. ' option ' .. idx .. ' -> ' .. action)
  if action and action ~= '' then bang(action) end
end

