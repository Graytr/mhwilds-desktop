; ==============================================================================
; Appearance menu: how things look. Your Palico's gear is this skin; Change Appearance is Windows itself.
;
; Every list is a block (Bg_<List>, the translucent panel behind the options) followed by
; its options: a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an arrow
; (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the bar runs
; when the option is clicked: bangs, a program or path in ["quotes"], or a Menu.lua call
; such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N>, use the next OptionY variable, and point the
; block at the next block_<N>.png with H=(<N>*#OptionPitch#).
; ==============================================================================

; --- Appearance: the list shown when the hunter icon is clicked
[StyleAppearance]
Group=Menus | Menu_Appearance

; the block behind the whole list, drawn first so the bars sit on it
[Bg_Appearance]
Meter=Image
MeterStyle=StyleListBlock | StyleAppearance
ImageName=#@#Images\block_4.png
H=(4*#OptionPitch#)

[Opt_Appearance_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY1#
MenuAction=["ms-settings:personalization-background"]

[Opt_Appearance_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY1# + #OptionTextDY#)
Text=Equipment Appearance

[Opt_Appearance_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Skin')"]

[Opt_Appearance_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY2# + #OptionTextDY#)
Text=Palico Equipment Appearance

[Opt_Appearance_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleAppearance
Y=#OptionY2#

[Opt_Appearance_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY3#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Look')"]

[Opt_Appearance_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY3# + #OptionTextDY#)
Text=Change Appearance

[Opt_Appearance_3_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleAppearance
Y=#OptionY3#

[Opt_Appearance_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY4#
MenuAction=["ms-settings:mousetouchpad"]

[Opt_Appearance_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY4# + #OptionTextDY#)
Text=Seikret Customization

; --- Skin: this skin and Rainmeter, in the second column
[StyleSkin]
Group=Menus | Menu_Skin

; the block behind the whole list, drawn first so the bars sit on it
[Bg_Skin]
Meter=Image
MeterStyle=StyleListBlock | StyleSubBlockColumn | StyleSkin
ImageName=#@#Images\block_3.png
H=(3*#OptionPitch#)

[Opt_Skin_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleSkin
Y=#OptionY1#
MenuAction=[!Manage]

[Opt_Skin_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleSkin
Y=(#OptionY1# + #OptionTextDY#)
Text=Manage Rainmeter

[Opt_Skin_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleSkin
Y=#OptionY2#
MenuAction=[!RefreshApp]

[Opt_Skin_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleSkin
Y=(#OptionY2# + #OptionTextDY#)
Text=Refresh Skins

[Opt_Skin_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleSkin
Y=#OptionY3#
MenuAction=["#CURRENTPATH#"]

[Opt_Skin_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleSkin
Y=(#OptionY3# + #OptionTextDY#)
Text=Edit This Skin

; --- Look: Windows personalisation, in the second column
[StyleLook]
Group=Menus | Menu_Look

; the block behind the whole list, drawn first so the bars sit on it
[Bg_Look]
Meter=Image
MeterStyle=StyleListBlock | StyleSubBlockColumn | StyleLook
ImageName=#@#Images\block_5.png
H=(5*#OptionPitch#)

[Opt_Look_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleLook
Y=#OptionY1#
MenuAction=["ms-settings:colors"]

[Opt_Look_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleLook
Y=(#OptionY1# + #OptionTextDY#)
Text=Colors

[Opt_Look_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleLook
Y=#OptionY2#
MenuAction=["ms-settings:themes"]

[Opt_Look_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleLook
Y=(#OptionY2# + #OptionTextDY#)
Text=Themes

[Opt_Look_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleLook
Y=#OptionY3#
MenuAction=["ms-settings:lockscreen"]

[Opt_Look_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleLook
Y=(#OptionY3# + #OptionTextDY#)
Text=Lock Screen

[Opt_Look_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleLook
Y=#OptionY4#
MenuAction=["ms-settings:taskbar"]

[Opt_Look_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleLook
Y=(#OptionY4# + #OptionTextDY#)
Text=Taskbar

[Opt_Look_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleLook
Y=#OptionY5#
MenuAction=["ms-settings:display"]

[Opt_Look_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleLook
Y=(#OptionY5# + #OptionTextDY#)
Text=Display
