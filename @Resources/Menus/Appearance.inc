; ==============================================================================
; Appearance menu: how things look, plus a command box.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Appearance: the list shown when the hunter icon is clicked
[StyleAppearance]
Group=Menus | Menu_Appearance

[Opt_Appearance_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY1#
MenuAction=[!Manage]

[Opt_Appearance_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY1# + #OptionTextDY#)
Text=Manage Rainmeter

[Opt_Appearance_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY2#
MenuAction=[!RefreshApp]

[Opt_Appearance_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY2# + #OptionTextDY#)
Text=Refresh Skins

[Opt_Appearance_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY3#
MenuAction=["ms-settings:personalization-background"]

[Opt_Appearance_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY3# + #OptionTextDY#)
Text=Wallpaper

[Opt_Appearance_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY4#
MenuAction=["#CURRENTPATH#"]

[Opt_Appearance_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY4# + #OptionTextDY#)
Text=Edit This Skin

[Opt_Appearance_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY5#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('Run')"][!CommandMeasure MenuScript mRun "ExecuteBatch 1"]

[Opt_Appearance_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY5# + #OptionTextDY#)
Text=Run Command

[Opt_Appearance_5_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleAppearance
Y=#OptionY5#
