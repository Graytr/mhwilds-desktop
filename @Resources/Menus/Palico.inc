; ==============================================================================
; Palico menu: your companion is the machine itself.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Palico: the list shown when the paw icon is clicked
[StylePalico]
Group=Menus | Menu_Palico

[Opt_Palico_1]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('Status')"]

[Opt_Palico_1_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY1# + #OptionTextDY#)
Text=Palico Status

[Opt_Palico_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StylePalico
Y=#OptionY1#

[Opt_Palico_2]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY2#
MenuAction=["#DiscordShortcut#"]

[Opt_Palico_2_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY2# + #OptionTextDY#)
Text=Call Discord

[Opt_Palico_3]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY3#
MenuAction=["ms-settings:bluetooth"]

[Opt_Palico_3_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY3# + #OptionTextDY#)
Text=Devices
