; ==============================================================================
; Equipment menu: your loadout is your programs, named after the game's own options.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text).
; MenuAction on the bar runs when the option is clicked: bangs, a program or path in
; ["quotes"], or a Menu.lua call such as ShowFolder, ShowPanel, OpenSubmenu or BackMenu.
; A sub-menu is just another list (Style<List> / Opt_<List>_<N>) that replaces the
; parent list when opened; its title comes from the Menu_<List>_Title variable.
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Equipment: the list shown when the armour icon is clicked
[StyleEquipment]
Group=Menus | Menu_Equipment

[Opt_Equipment_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('ProgramsPath', 'Name', 'Programs', 'lnk;url')"]

[Opt_Equipment_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY1# + #OptionTextDY#)
Text=Change Equipment

[Opt_Equipment_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY2#
MenuAction=["ms-settings:"]

[Opt_Equipment_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY2# + #OptionTextDY#)
Text=Customize Bowgun

[Opt_Equipment_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY3#
MenuAction=["taskmgr.exe"]

[Opt_Equipment_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY3# + #OptionTextDY#)
Text=View Loadout
