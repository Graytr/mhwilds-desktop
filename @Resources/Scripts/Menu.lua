--[[
Menu.lua - all menu state for the Monster Hunter Wilds camp menu.

The INI files only describe how things look. Every mouse action calls one of the
functions at the bottom of this file, for example:
    MouseOverAction=[!CommandMeasure MenuScript "HoverIcon('#CURRENTSECTION#')"]

Naming conventions the script depends on
  Icon_<Menu>            a main-menu icon. Custom option MenuTitle = the header text.
  Opt_<Menu>_<N>         option bar N of that menu. Custom option MenuAction = the
                         bang(s) to run when it is clicked, e.g. MenuAction=["shell:Downloads"]
  Opt_<Menu>_<N>_Text    the label drawn on top of that bar.
  group Menus            every sub-menu meter (hidden together).
  group Menu_<Menu>      the meters of one sub-menu (shown together).
  group Icons            the six icons.
  MeterTitle, MeterIconGlow, MeterCursor, MeterChevron   the shared indicator meters.

Behaviour (mirrors the in-game tent menu)
  * Hovering an icon selects it: the glow moves behind it, it tints and the title
    changes. The selection stays when the mouse leaves; it does not follow the mouse.
  * Clicking an icon opens its menu: the icon stays lit, option 1 is selected and
    the dot sits on the left end of the selected bar. Clicking it again closes.
  * Hovering an option selects it: bar highlight, chevron and dot move to it.
  * Clicking an option runs its MenuAction.
]]

local openMenu       = nil   -- menu whose options are showing, or nil
local selectedIcon   = nil   -- icon the glow rests on, or nil
local selectedOption = {}    -- [menu] = index of the highlighted option bar

-- -----------------------------------------------------------------------------
-- helpers
-- -----------------------------------------------------------------------------

local function bang(s) SKIN:Bang(s) end

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

-- centre the glow behind an icon
local function placeGlow(menu)
  local m = SKIN:GetMeter('Icon_' .. menu)
  local r = num('IconGlowRadius')
  local x = m:GetX() + m:GetW() / 2 - r
  local y = m:GetY() + m:GetH() / 2 - r
  bang('[!SetOption MeterIconGlow X ' .. x .. '][!SetOption MeterIconGlow Y ' .. y .. ']'
    .. '[!ShowMeter MeterIconGlow][!UpdateMeter MeterIconGlow]')
end

-- put the dot on the left end of option bar idx (bars may be hidden, so their
-- geometry comes from the variables rather than the meters)
local function placeDot(idx)
  local r = num('CursorHaloRadius')
  local x = num('OptionsX') + num('CursorInsetX') - r
  local y = num('OptionY' .. idx) + num('OptionH') / 2 - r
  bang('[!SetOption MeterCursor X ' .. x .. '][!SetOption MeterCursor Y ' .. y .. ']'
    .. '[!ShowMeter MeterCursor][!UpdateMeter MeterCursor]')
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
  placeDot(idx)
end

local function closeOpenMenu()
  if not openMenu then return end
  local menu = openMenu
  if selectedOption[menu] then styleBar(menu, selectedOption[menu], false) end
  selectedOption[menu] = nil
  bang('[!HideMeterGroup Menu_' .. menu .. '][!HideMeter MeterCursor][!HideMeter MeterChevron]')
  openMenu = nil
end

-- -----------------------------------------------------------------------------
-- entry points called from the INI
-- -----------------------------------------------------------------------------

-- OnRefreshAction: everything closed, nothing selected.
function Reset()
  openMenu, selectedIcon, selectedOption = nil, nil, {}
  bang('[!HideMeterGroup Menus][!HideMeter MeterIconGlow][!HideMeter MeterCursor][!HideMeter MeterChevron]'
    .. '[!SetOptionGroup Icons ImageTint "#IconTintNormal#"][!SetOption MeterTitle Text ""]'
    .. '[!UpdateMeter *][!Redraw]')
end

function HoverIcon(section)
  local menu = parse(section)
  if not menu then return end
  if openMenu then
    -- a menu is open: just a light hover highlight, the selection stays put
    if menu ~= openMenu then tintIcon(menu, 'IconTintHover') end
  else
    if selectedIcon and selectedIcon ~= menu then tintIcon(selectedIcon, 'IconTintNormal') end
    selectedIcon = menu
    tintIcon(menu, 'IconTintHover')
    setTitle(SKIN:GetMeter(section):GetOption('MenuTitle'))
    placeGlow(menu)
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
  openMenu, selectedIcon = menu, menu
  tintIcon(menu, 'IconTintSelected')
  setTitle(SKIN:GetMeter('Icon_' .. menu):GetOption('MenuTitle'))
  placeGlow(menu)
  bang('[!ShowMeterGroup Menu_' .. menu .. '][!UpdateMeterGroup Menu_' .. menu .. ']')
  selectOption(menu, 1)
  bang('!Redraw')
end

function CloseMenu()
  if not openMenu then return end
  local menu = openMenu
  closeOpenMenu()
  tintIcon(menu, 'IconTintHover')   -- back to "selected but not open"
  bang('!Redraw')
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
  if action and action ~= '' then bang(action) end
end
