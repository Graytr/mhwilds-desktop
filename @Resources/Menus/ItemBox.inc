; ==============================================================================
; ItemBox menu: your storage, mapped to the places files live on this PC.
;
; Every option is a bar (Opt_ItemBox_<N>) plus its label (Opt_ItemBox_<N>_Text).
; MenuAction on the bar is what runs when the option is clicked: any bang(s), a
; program or path in ["quotes"], or a Menu.lua call such as
;   [!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games')"]
; To add an option, copy a pair, bump <N> and use the next OptionY variable.
; ==============================================================================

[StyleItemBox]
Group=Menus | Menu_ItemBox

[Opt_ItemBox_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY1#
MenuAction=["shell:Desktop"]

[Opt_ItemBox_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY1# + #OptionTextDY#)
Text=Item Pouch

[Opt_ItemBox_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY2#
MenuAction=["shell:MyComputerFolder"]

[Opt_ItemBox_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY2# + #OptionTextDY#)
Text=Item Box

[Opt_ItemBox_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY3#
MenuAction=["shell:Personal"]

[Opt_ItemBox_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY3# + #OptionTextDY#)
Text=Documents

[Opt_ItemBox_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY4#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mDownloadsPath', 'Date', 'Downloads')"]

[Opt_ItemBox_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY4# + #OptionTextDY#)
Text=Downloads

[Opt_ItemBox_5]
Meter=Image
MeterStyle=StyleOptionBar | StyleItemBox
Y=#OptionY5#
MenuAction=["shell:RecycleBinFolder"]

[Opt_ItemBox_5_Text]
Meter=String
MeterStyle=StyleOptionText | StyleItemBox
Y=(#OptionY5# + #OptionTextDY#)
Text=Sell Items
