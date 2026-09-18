; ==============================================================================
; Quest menu: the notes icon.
;
; Every option is a bar (Opt_Quest_<N>) plus its label (Opt_Quest_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleQuest]
Group=Menus | Menu_Quest

[Opt_Quest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY1#
MenuAction=

[Opt_Quest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY1# + #OptionTextDY#)
Text=Post/Join Quest
