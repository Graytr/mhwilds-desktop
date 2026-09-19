; ==============================================================================
; Tent Settings menu: music and sound.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- TentSettings: the list shown when the speaker icon is clicked
[StyleTentSettings]
Group=Menus | Menu_TentSettings

[Opt_TentSettings_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleTentSettings
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('NowPlaying')"]

[Opt_TentSettings_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleTentSettings
Y=(#OptionY1# + #OptionTextDY#)
Text=Change BGM

[Opt_TentSettings_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleTentSettings
Y=#OptionY1#

[Opt_TentSettings_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleTentSettings
Y=#OptionY2#
MenuAction=["ms-settings:sound"]

[Opt_TentSettings_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleTentSettings
Y=(#OptionY2# + #OptionTextDY#)
Text=Sound Settings

[Opt_TentSettings_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleTentSettings
Y=#OptionY3#
MenuAction=["sndvol.exe"]

[Opt_TentSettings_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleTentSettings
Y=(#OptionY3# + #OptionTextDY#)
Text=Volume Mixer
