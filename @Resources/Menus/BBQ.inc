; ==============================================================================
; BBQ menu: a meal before the hunt (the Windows toggles worth setting before a session) and Rest (the power options).
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

; --- BBQ: the list shown when the grill icon is clicked
[StyleBBQ]
Group=Menus | Menu_BBQ

; the block behind the whole list, drawn first so the bars sit on it
[Bg_BBQ]
Meter=Image
MeterStyle=StyleListBlock | StyleBBQ
ImageName=#@#Images\block_2.png
H=(2*#OptionPitch#)

[Opt_BBQ_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleBBQ
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Meal')"]

[Opt_BBQ_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleBBQ
Y=(#OptionY1# + #OptionTextDY#)
Text=Grill a Meal

[Opt_BBQ_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleBBQ
Y=#OptionY1#

[Opt_BBQ_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleBBQ
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Rest')"]

[Opt_BBQ_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleBBQ
Y=(#OptionY2# + #OptionTextDY#)
Text=Rest

[Opt_BBQ_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleBBQ
Y=#OptionY2#

; --- Meal: buffs for the session ahead
[StyleMeal]
Group=Menus | Menu_Meal

; the block behind the whole list, drawn first so the bars sit on it
[Bg_Meal]
Meter=Image
MeterStyle=StyleListBlock | StyleSubBlockColumn | StyleMeal
ImageName=#@#Images\block_4.png
H=(4*#OptionPitch#)

[Opt_Meal_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleMeal
Y=#OptionY1#
MenuAction=["ms-settings:gaming-gamemode"]

[Opt_Meal_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleMeal
Y=(#OptionY1# + #OptionTextDY#)
Text=Game Mode

[Opt_Meal_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleMeal
Y=#OptionY2#
MenuAction=["ms-settings:nightlight"]

[Opt_Meal_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleMeal
Y=(#OptionY2# + #OptionTextDY#)
Text=Night Light

[Opt_Meal_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleMeal
Y=#OptionY3#
MenuAction=["ms-settings:powersleep"]

[Opt_Meal_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleMeal
Y=(#OptionY3# + #OptionTextDY#)
Text=Power Mode

[Opt_Meal_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleMeal
Y=#OptionY4#
MenuAction=["ms-clock:"]

[Opt_Meal_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleMeal
Y=(#OptionY4# + #OptionTextDY#)
Text=Set a Timer

; --- Rest: lock, sleep, restart and shut down. Restart and Shut Down give you 15 seconds; Cancel aborts them.
[StyleRest]
Group=Menus | Menu_Rest

; the block behind the whole list, drawn first so the bars sit on it
[Bg_Rest]
Meter=Image
MeterStyle=StyleListBlock | StyleSubBlockColumn | StyleRest
ImageName=#@#Images\block_5.png
H=(5*#OptionPitch#)

[Opt_Rest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleRest
Y=#OptionY1#
MenuAction=[rundll32.exe user32.dll,LockWorkStation]

[Opt_Rest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleRest
Y=(#OptionY1# + #OptionTextDY#)
Text=Lock

[Opt_Rest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleRest
Y=#OptionY2#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]

[Opt_Rest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleRest
Y=(#OptionY2# + #OptionTextDY#)
Text=Sleep

[Opt_Rest_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleRest
Y=#OptionY3#
MenuAction=[shutdown.exe /r /t 15]

[Opt_Rest_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleRest
Y=(#OptionY3# + #OptionTextDY#)
Text=Restart

[Opt_Rest_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleRest
Y=#OptionY4#
MenuAction=[shutdown.exe /s /t 15]

[Opt_Rest_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleRest
Y=(#OptionY4# + #OptionTextDY#)
Text=Shut Down

[Opt_Rest_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleRest
Y=#OptionY5#
MenuAction=[shutdown.exe /a]

[Opt_Rest_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleRest
Y=(#OptionY5# + #OptionTextDY#)
Text=Cancel Shutdown
