; ==============================================================================
; Quest menu: the quest board is your game library; Return to Camp holds the power options.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Quest: the list shown when the quest icon is clicked
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

[Opt_Quest_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY1#

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
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Camp')"]

[Opt_Quest_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY3# + #OptionTextDY#)
Text=Return to Camp

[Opt_Quest_3_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY3#

; --- Camp: sleep, restart and shut down. Restart and Shut Down give you 15 seconds; Cancel aborts them.
[StyleCamp]
Group=Menus | Menu_Camp

[Opt_Camp_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleCamp
Y=#OptionY1#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]

[Opt_Camp_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleCamp
Y=(#OptionY1# + #OptionTextDY#)
Text=Sleep

[Opt_Camp_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleCamp
Y=#OptionY2#
MenuAction=[shutdown.exe /r /t 15]

[Opt_Camp_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleCamp
Y=(#OptionY2# + #OptionTextDY#)
Text=Restart

[Opt_Camp_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleCamp
Y=#OptionY3#
MenuAction=[shutdown.exe /s /t 15]

[Opt_Camp_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleCamp
Y=(#OptionY3# + #OptionTextDY#)
Text=Shut Down

[Opt_Camp_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleCamp
Y=#OptionY4#
MenuAction=[shutdown.exe /a]

[Opt_Camp_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleCamp
Y=(#OptionY4# + #OptionTextDY#)
Text=Cancel Shutdown
