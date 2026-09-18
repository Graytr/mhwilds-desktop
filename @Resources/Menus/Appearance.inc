; ==============================================================================
; Appearance menu: how things look, plus a command box.
;
; Every option is a bar (Opt_Appearance_<N>) plus its label (Opt_Appearance_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

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
MenuAction=[!CommandMeasure MenuScript "ShowPanel('Run')"][!CommandMeasure mRun "ExecuteBatch 1"]

[Opt_Appearance_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY5# + #OptionTextDY#)
Text=Run Command
