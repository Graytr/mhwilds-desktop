; ==============================================================================
; Appearance menu: the hunter icon.
;
; Every option is a bar (Opt_Appearance_<N>) plus its label (Opt_Appearance_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleAppearance]
Group=Menus | Menu_Appearance

[Opt_Appearance_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleAppearance
Y=#OptionY1#
MenuAction=

[Opt_Appearance_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAppearance
Y=(#OptionY1# + #OptionTextDY#)
Text=Change Appearance
