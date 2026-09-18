; ==============================================================================
; Item Box menu: your storage. Item Pouch and Item Box open sub-menus of places on this PC.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

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

[Opt_ItemBox_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleItemBox
Y=#OptionY1#

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

[Opt_ItemBox_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleItemBox
Y=#OptionY2#

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
MeterStyle=StyleOptionBar | StyleSubBarColumn | StylePouch
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDesktopPath', 'Name', 'Desktop')"]

[Opt_Pouch_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StylePouch
Y=(#OptionY1# + #OptionTextDY#)
Text=Desktop

[Opt_Pouch_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StylePouch
Y=#OptionY1#

[Opt_Pouch_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StylePouch
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDownloadsPath', 'Date', 'Downloads')"]

[Opt_Pouch_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StylePouch
Y=(#OptionY2# + #OptionTextDY#)
Text=Downloads

[Opt_Pouch_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StylePouch
Y=#OptionY2#

; --- Chest: the permanent stuff
[StyleChest]
Group=Menus | Menu_Chest

[Opt_Chest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleChest
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('ThisPCPath', 'Name', 'This PC')"]

[Opt_Chest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleChest
Y=(#OptionY1# + #OptionTextDY#)
Text=This PC

[Opt_Chest_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleChest
Y=#OptionY1#

[Opt_Chest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleChest
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDocumentsPath', 'Name', 'Documents')"]

[Opt_Chest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleChest
Y=(#OptionY2# + #OptionTextDY#)
Text=Documents

[Opt_Chest_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleChest
Y=#OptionY2#
