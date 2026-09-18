; ==============================================================================
; Audio menu: music and sound.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text).
; MenuAction on the bar runs when the option is clicked: bangs, a program or path in
; ["quotes"], or a Menu.lua call such as ShowFolder, ShowPanel, OpenSubmenu or BackMenu.
; A sub-menu is just another list (Style<List> / Opt_<List>_<N>) that replaces the
; parent list when opened; its title comes from the Menu_<List>_Title variable.
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Audio: the list shown when the speaker icon is clicked
[StyleAudio]
Group=Menus | Menu_Audio

[Opt_Audio_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleAudio
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('NowPlaying')"]

[Opt_Audio_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAudio
Y=(#OptionY1# + #OptionTextDY#)
Text=Now Playing

[Opt_Audio_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleAudio
Y=#OptionY2#
MenuAction=["ms-settings:sound"]

[Opt_Audio_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAudio
Y=(#OptionY2# + #OptionTextDY#)
Text=Sound Settings

[Opt_Audio_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleAudio
Y=#OptionY3#
MenuAction=["sndvol.exe"]

[Opt_Audio_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleAudio
Y=(#OptionY3# + #OptionTextDY#)
Text=Volume Mixer
