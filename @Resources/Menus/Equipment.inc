; ==============================================================================
; Equipment menu: your programs are your loadout.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
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

[Opt_Equipment_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleEquipment
Y=#OptionY1#

[Opt_Equipment_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY2#
MenuAction=["ms-settings:appsfeatures"]

[Opt_Equipment_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY2# + #OptionTextDY#)
Text=View/Sell Equipment

[Opt_Equipment_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY3#
MenuAction=["ms-settings:startupapps"]

[Opt_Equipment_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY3# + #OptionTextDY#)
Text=View/Sell Decorations

[Opt_Equipment_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY4#
MenuAction=["ms-settings:"]

[Opt_Equipment_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY4# + #OptionTextDY#)
Text=Customize Bowgun

[Opt_Equipment_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleEquipment
Y=#OptionY5#
MenuAction=["taskmgr.exe"]

[Opt_Equipment_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleEquipment
Y=(#OptionY5# + #OptionTextDY#)
Text=View Loadouts
