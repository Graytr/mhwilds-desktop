; ==============================================================================
; Meal menu: rest and music. Restart and Shut Down give you 15 seconds; Cancel aborts them.
;
; Every option is a bar (Opt_Meal_<N>) plus its label (Opt_Meal_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleMeal]
Group=Menus | Menu_Meal

[Opt_Meal_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('NowPlaying')"]

[Opt_Meal_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY1# + #OptionTextDY#)
Text=Now Playing

[Opt_Meal_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY2#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]

[Opt_Meal_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY2# + #OptionTextDY#)
Text=Rest (Sleep)

[Opt_Meal_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY3#
MenuAction=[shutdown.exe /r /t 15]

[Opt_Meal_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY3# + #OptionTextDY#)
Text=Restart

[Opt_Meal_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY4#
MenuAction=[shutdown.exe /s /t 15]

[Opt_Meal_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY4# + #OptionTextDY#)
Text=Shut Down

[Opt_Meal_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY5#
MenuAction=[shutdown.exe /a]

[Opt_Meal_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY5# + #OptionTextDY#)
Text=Cancel Shutdown
