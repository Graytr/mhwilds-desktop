; ==============================================================================
; Item Box menu: your storage. Item Pouch and Item Box open sub-menus of places on this PC.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text).
; MenuAction on the bar runs when the option is clicked: bangs, a program or path in
; ["quotes"], or a Menu.lua call such as ShowFolder, ShowPanel, OpenSubmenu or BackMenu.
; A sub-menu is just another list (Style<List> / Opt_<List>_<N>) that replaces the
; parent list when opened; its title comes from the Menu_<List>_Title variable.
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[Variables]
Menu_Pouch_Title=Item Pouch
Menu_Chest_Title=Item Box

; --- ItemBox: the list shown when the chest icon is clicked
[StyleItemBox]
Group=Menus | Menu_ItemBox

[Opt_ItemBox_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Pouch')"]

[Opt_ItemBox_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY1# + #OptionTextDY#)
Text=Item Pouch

[Opt_ItemBox_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Chest')"]

[Opt_ItemBox_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY2# + #OptionTextDY#)
Text=Item Box

[Opt_ItemBox_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY3#
MenuAction=["shell:RecycleBinFolder"]

[Opt_ItemBox_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY3# + #OptionTextDY#)
Text=Sell Items

; --- Pouch: quick and dirty files
[StylePouch]
Group=Menus | Menu_Pouch

[Opt_Pouch_1]
Meter=Image
MeterStyle=StyleOptionBar | StylePouch
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDesktopPath', 'Name', 'Desktop')"]

[Opt_Pouch_1_Text]
Meter=String
MeterStyle=StyleOptionText | StylePouch
Y=(#OptionY1# + #OptionTextDY#)
Text=Desktop

[Opt_Pouch_2]
Meter=Image
MeterStyle=StyleOptionBar | StylePouch
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDownloadsPath', 'Date', 'Downloads')"]

[Opt_Pouch_2_Text]
Meter=String
MeterStyle=StyleOptionText | StylePouch
Y=(#OptionY2# + #OptionTextDY#)
Text=Downloads

[Opt_Pouch_3]
Meter=Image
MeterStyle=StyleOptionBar | StylePouch
Y=#OptionY3#
MenuAction=[!CommandMeasure MenuScript "BackMenu()"]

[Opt_Pouch_3_Text]
Meter=String
MeterStyle=StyleOptionText | StylePouch
Y=(#OptionY3# + #OptionTextDY#)
Text=Back

; --- Chest: the permanent stuff
[StyleChest]
Group=Menus | Menu_Chest

[Opt_Chest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleChest
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('ThisPCPath', 'Name', 'This PC')"]

[Opt_Chest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleChest
Y=(#OptionY1# + #OptionTextDY#)
Text=This PC

[Opt_Chest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleChest
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDocumentsPath', 'Name', 'Documents')"]

[Opt_Chest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleChest
Y=(#OptionY2# + #OptionTextDY#)
Text=Documents

[Opt_Chest_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleChest
Y=#OptionY3#
MenuAction=[!CommandMeasure MenuScript "BackMenu()"]

[Opt_Chest_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleChest
Y=(#OptionY3# + #OptionTextDY#)
Text=Back
