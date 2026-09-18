; ==============================================================================
; Quest menu: the quest board is your game library.
;
; Every option is a bar (Opt_Quest_<N>) plus its label (Opt_Quest_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleQuest]
Group=Menus | Menu_Quest

[Opt_Quest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]

[Opt_Quest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY1# + #OptionTextDY#)
Text=Quest Board

[Opt_Quest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY2#
MenuAction=["steam://open/games"]

[Opt_Quest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY2# + #OptionTextDY#)
Text=Post a Quest

[Opt_Quest_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY3#
MenuAction=["#GamesPath#"]

[Opt_Quest_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY3# + #OptionTextDY#)
Text=Manage Quests
