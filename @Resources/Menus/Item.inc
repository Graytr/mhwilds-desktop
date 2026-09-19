; ==============================================================================
; Item menu: your files. Transfer Items holds the folders on this PC; the Crafting List is whatever you opened last.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Item: the list shown when the item icon is clicked
[StyleItem]
Group=Menus | Menu_Item

[Opt_Item_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleItem
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('Transfer')"]

[Opt_Item_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItem
Y=(#OptionY1# + #OptionTextDY#)
Text=Transfer Items

[Opt_Item_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleItem
Y=#OptionY1#

[Opt_Item_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleItem
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('RecentPath', 'Date', 'Recent Files', 'lnk', 0)"]

[Opt_Item_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItem
Y=(#OptionY2# + #OptionTextDY#)
Text=Crafting List

[Opt_Item_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleItem
Y=#OptionY2#

[Opt_Item_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleItem
Y=#OptionY3#
MenuAction=["shell:RecycleBinFolder"]

[Opt_Item_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItem
Y=(#OptionY3# + #OptionTextDY#)
Text=View/Sell Items

[Opt_Item_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleItem
Y=#OptionY4#
MenuAction=[!CommandMeasure MenuScript "ShowPanel('Run')"][!CommandMeasure mRun "ExecuteBatch 1"]

[Opt_Item_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItem
Y=(#OptionY4# + #OptionTextDY#)
Text=Customize Radial Menu

[Opt_Item_4_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleItem
Y=#OptionY4#

[Opt_Item_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleItem
Y=#OptionY5#
MenuAction=["ms-settings:storagesense"]

[Opt_Item_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItem
Y=(#OptionY5# + #OptionTextDY#)
Text=View/Sell Artian Materials

; --- Transfer: the places on this PC, in the second column
[StyleTransfer]
Group=Menus | Menu_Transfer

[Opt_Transfer_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleTransfer
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDesktopPath', 'Name', 'Desktop')"]

[Opt_Transfer_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleTransfer
Y=(#OptionY1# + #OptionTextDY#)
Text=Desktop

[Opt_Transfer_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleTransfer
Y=#OptionY1#

[Opt_Transfer_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleTransfer
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDownloadsPath', 'Date', 'Downloads')"]

[Opt_Transfer_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleTransfer
Y=(#OptionY2# + #OptionTextDY#)
Text=Downloads

[Opt_Transfer_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleTransfer
Y=#OptionY2#

[Opt_Transfer_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleTransfer
Y=#OptionY3#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDocumentsPath', 'Name', 'Documents')"]

[Opt_Transfer_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleTransfer
Y=(#OptionY3# + #OptionTextDY#)
Text=Documents

[Opt_Transfer_3_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleTransfer
Y=#OptionY3#

[Opt_Transfer_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleTransfer
Y=#OptionY4#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mPicturesPath', 'Date', 'Pictures')"]

[Opt_Transfer_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleTransfer
Y=(#OptionY4# + #OptionTextDY#)
Text=Pictures

[Opt_Transfer_4_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleTransfer
Y=#OptionY4#

[Opt_Transfer_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleTransfer
Y=#OptionY5#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('ThisPCPath', 'Name', 'This PC')"]

[Opt_Transfer_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleTransfer
Y=(#OptionY5# + #OptionTextDY#)
Text=This PC

[Opt_Transfer_5_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleSubArrowColumn | StyleTransfer
Y=#OptionY5#
