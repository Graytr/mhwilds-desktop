; ==============================================================================
; Main menu: background, title, the glow behind the selected icon and the eight icons.
; The menus themselves are Menus\<Name>.inc, included from MHWildsMenu.ini right after
; this file so that their option bars draw above the icons and below the dot.
;
; Each icon is named Icon_<Menu>. Menu.lua uses that name to find the matching
; menu group (Menu_<Menu>) and option bars (Opt_<Menu>_<N>). The custom
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

[Icon_Item]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_item.png
X=#IconX1#
MenuTitle=Item Menu

[Icon_Equipment]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_equipment.png
X=#IconX2#
MenuTitle=Equipment Menu

[Icon_Palico]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_palico.png
X=#IconX3#
MenuTitle=Palico Menu

[Icon_BBQ]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_bbq.png
X=#IconX4#
MenuTitle=BBQ Menu

[Icon_Quest]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_quest.png
X=#IconX5#
MenuTitle=Quest Menu

[Icon_Lobby]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_lobby.png
X=#IconX6#
MenuTitle=Change Lobby Menu

[Icon_TentSettings]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_tent_settings.png
X=#IconX7#
MenuTitle=Tent Settings Menu

[Icon_Appearance]
Meter=Image
MeterStyle=StyleIcon
ImageName=#@#Images\icon_appearance.png
X=#IconX8#
MenuTitle=Appearance Menu
