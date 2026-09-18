; ==============================================================================
; Quest menu: the quest board is your game library; Return to Camp holds the power options.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text).
; MenuAction on the bar runs when the option is clicked: bangs, a program or path in
; ["quotes"], or a Menu.lua call such as ShowFolder, ShowPanel, OpenSubmenu or BackMenu.
; A sub-menu is just another list (Style<List> / Opt_<List>_<N>) that replaces the
; parent list when opened; its title comes from the Menu_<List>_Title variable.
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[Variables]
Menu_Camp_Title=Return to Camp

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

; --- Camp: sleep, restart and shut down. Restart and Shut Down give you 15 seconds; Cancel aborts them.
[StyleCamp]
Group=Menus | Menu_Camp

[Opt_Camp_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY1#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]

[Opt_Camp_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleCamp
Y=(#OptionY1# + #OptionTextDY#)
Text=Sleep

[Opt_Camp_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY2#
MenuAction=[shutdown.exe /r /t 15]

[Opt_Camp_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleCamp
Y=(#OptionY2# + #OptionTextDY#)
Text=Restart

[Opt_Camp_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY3#
MenuAction=[shutdown.exe /s /t 15]

[Opt_Camp_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleCamp
Y=(#OptionY3# + #OptionTextDY#)
Text=Shut Down

[Opt_Camp_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY4#
MenuAction=[shutdown.exe /a]

[Opt_Camp_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleCamp
Y=(#OptionY4# + #OptionTextDY#)
Text=Cancel Shutdown

[Opt_Camp_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY5#
MenuAction=[!CommandMeasure MenuScript "BackMenu()"]

[Opt_Camp_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleCamp
Y=(#OptionY5# + #OptionTextDY#)
Text=Back
