; ==============================================================================
; Main menu: background, title, the glow behind the selected icon, the six icons,
; and (at the bottom) the includes for the six sub-menus.
;
; Each icon is named Icon_<Menu>. Menu.lua uses that name to find the matching
; sub-menu group (Menu_<Menu>) and option bars (Opt_<Menu>_<N>). The custom
; MenuTitle option is the header text shown while that icon is selected.
; ==============================================================================

[MeterBackground]
Meter=Image
ImageName=#@#Images\menu_bar.png
X=#MainMenuX#
Y=#MainMenuY#
W=#BackgroundW#
H=#BackgroundH#

[MeterTitle]
Meter=String
MeterStyle=StyleTitle
X=#TitleX#
Y=#TitleY#
Text=

; Soft green glow behind whichever icon is selected. Drawn before the icons so it
; sits behind them, like the game.
[MeterIconGlow]
Meter=Shape
X=0
Y=0
Shape=Ellipse #IconGlowRadius#,#IconGlowRadius#,#IconGlowRadius# | Fill RadialGradient IconGlow | StrokeWidth 0
IconGlow=0,0 | #AccentGreen#,190 ; 0.0 | #AccentGreen#,70 ; 0.55 | #AccentGreen#,0 ; 1.0
Hidden=1

; --- Icons, in the same order as the in-game tent menu --------------------------

[Icon_ItemBox]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\chest_icon.png
X=#IconX1#
MenuTitle=Item Box

[Icon_Equipment]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\equipment_icon.png
; this drawing is narrower than the others: shrink it and centre it in its slot
W=(3.4*#SizeMultiplier#)
X=(#IconX2# + ((#IconSize# - (3.4*#SizeMultiplier#)) / 2))
MenuTitle=Equipment Menu

[Icon_Palico]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\palico_icon.png
X=#IconX3#
MenuTitle=Palico Menu

[Icon_Quest]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\notes_icon.png
X=#IconX4#
MenuTitle=Quest Menu

[Icon_Meal]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\food_icon.png
X=#IconX5#
MenuTitle=BBQ Menu

[Icon_Appearance]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\personal_icon.png
; narrower drawing, same treatment as the equipment icon
W=(2.5*#SizeMultiplier#)
X=(#IconX6# + ((#IconSize# - (2.5*#SizeMultiplier#)) / 2))
MenuTitle=Appearance Menu

; --- Sub-menus ------------------------------------------------------------------
; Each menu lives in its own file. Rainmeter does allow includes inside included
; files; the catch is that a relative path is resolved from THIS file's folder,
; so the paths must be anchored with #@#. Their meters are inserted right here,
; after the icons, which puts the option bars above the icons in draw order.
[IncludeSubMenus]
@IncludeItemBox=#@#Menus\ItemBox.inc
@IncludeEquipment=#@#Menus\Equipment.inc
@IncludePalico=#@#Menus\Palico.inc
@IncludeQuest=#@#Menus\Quest.inc
@IncludeMeal=#@#Menus\Meal.inc
@IncludeAppearance=#@#Menus\Appearance.inc
