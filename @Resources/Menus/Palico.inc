; ==============================================================================
; Palico menu: the paw icon.
;
; Every option is a bar (Opt_Palico_<N>) plus its label (Opt_Palico_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StylePalico]
Group=Menus | Menu_Palico

[Opt_Palico_1]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY1#
MenuAction=

[Opt_Palico_1_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY1# + #OptionTextDY#)
Text=Palico Deployment Status

[Opt_Palico_2]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY2#
MenuAction=

[Opt_Palico_2_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY2# + #OptionTextDY#)
Text=Change Palico Equipment
