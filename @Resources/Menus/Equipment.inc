; ==============================================================================
; Equipment menu: your loadout is your programs.
;
; Every option is a bar (Opt_Equipment_<N>) plus its label (Opt_Equipment_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleEquipment]
Group=Menus | Menu_Equipment

[Opt_Equipment_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('ProgramsPath', 'Name', 'Programs', 'lnk;url')"]

[Opt_Equipment_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY1# + #OptionTextDY#)
Text=Change Equipment

[Opt_Equipment_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY2#
MenuAction=["#ProgramsPath#"]

[Opt_Equipment_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY2# + #OptionTextDY#)
Text=Manage Equipment

[Opt_Equipment_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY3#
MenuAction=["taskmgr.exe"]

[Opt_Equipment_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY3# + #OptionTextDY#)
Text=Task Manager

[Opt_Equipment_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY4#
MenuAction=["ms-settings:"]

[Opt_Equipment_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY4# + #OptionTextDY#)
Text=Windows Settings
