; ==============================================================================
; Palico menu: your companion is the machine itself.
;
; Every option is a bar (Opt_Palico_<N>) plus its label (Opt_Palico_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

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

[Opt_Palico_4]
Meter=Image
MeterStyle=StyleOptionBar | StylePalico
Y=#OptionY4#
MenuAction=["ms-settings:sound"]

[Opt_Palico_4_Text]
Meter=String
MeterStyle=StyleOptionText | StylePalico
Y=(#OptionY4# + #OptionTextDY#)
Text=Sound
