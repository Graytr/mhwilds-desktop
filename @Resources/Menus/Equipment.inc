; ==============================================================================
; Equipment menu: the armour icon.
;
; Every option is a bar (Opt_Equipment_<N>) plus its label (Opt_Equipment_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleEquipment]
Group=Menus | Menu_Equipment

[Opt_Equipment_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY1#
MenuAction=

[Opt_Equipment_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY1# + #OptionTextDY#)
Text=Change Equipment
