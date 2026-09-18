; ==============================================================================
; ItemBox menu: the chest icon.
;
; Every option is a bar (Opt_ItemBox_<N>) plus its label (Opt_ItemBox_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked. To add an option,
; copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleItemBox]
Group=Menus | Menu_ItemBox

[Opt_ItemBox_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY1#
MenuAction=

[Opt_ItemBox_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY1# + #OptionTextDY#)
Text=Transfer Items

[Opt_ItemBox_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY2#
MenuAction=

[Opt_ItemBox_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY2# + #OptionTextDY#)
Text=Crafting List

[Opt_ItemBox_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY3#
MenuAction=

[Opt_ItemBox_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY3# + #OptionTextDY#)
Text=Check/Sell Items

[Opt_ItemBox_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY4#
MenuAction=

[Opt_ItemBox_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY4# + #OptionTextDY#)
Text=Customize Radial Menu
