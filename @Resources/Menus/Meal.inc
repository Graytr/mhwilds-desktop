; ==============================================================================
; Meal menu: the grill icon.
;
; Every option is a bar (Opt_Meal_<N>) plus its label (Opt_Meal_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleMeal]
Group=Menus | Menu_Meal

[Opt_Meal_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleMeal
Y=#OptionY1#
MenuAction=

[Opt_Meal_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleMeal
Y=(#OptionY1# + #OptionTextDY#)
Text=Grill a Meal
