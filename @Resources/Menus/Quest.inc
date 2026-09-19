; ==============================================================================
; Quest menu: the quest board is your game library; the field guide is where to look things up.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Quest: the list shown when the quest icon is clicked
[StyleQuest]
Group=Menus | Menu_Quest

[Opt_Quest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]

[Opt_Quest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY1# + #OptionTextDY#)
Text=Post/Join Quest

[Opt_Quest_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY1#

[Opt_Quest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY2#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('mVideosPath', 'Date', 'Videos')"]

[Opt_Quest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY2# + #OptionTextDY#)
Text=Quest Completion Animations

[Opt_Quest_2_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY2#

[Opt_Quest_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY3#
MenuAction=["steam://open/friends"]

[Opt_Quest_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY3# + #OptionTextDY#)
Text=Conversation Log

[Opt_Quest_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY4#
MenuAction=[!CommandMeasure MenuScript "OpenSubmenu('FieldGuide')"]

[Opt_Quest_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY4# + #OptionTextDY#)
Text=Monster Field Guide

[Opt_Quest_4_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY4#

; --- FieldGuide: reference, in the second column
[StyleFieldGuide]
Group=Menus | Menu_FieldGuide

[Opt_FieldGuide_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleFieldGuide
Y=#OptionY1#
MenuAction=["steam://open/games"]

[Opt_FieldGuide_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleFieldGuide
Y=(#OptionY1# + #OptionTextDY#)
Text=Steam Library

[Opt_FieldGuide_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleFieldGuide
Y=#OptionY2#
MenuAction=["steam://store/"]

[Opt_FieldGuide_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleFieldGuide
Y=(#OptionY2# + #OptionTextDY#)
Text=Steam Store

[Opt_FieldGuide_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleFieldGuide
Y=#OptionY3#
MenuAction=["https://mhwilds.kiranico.com/"]

[Opt_FieldGuide_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleFieldGuide
Y=(#OptionY3# + #OptionTextDY#)
Text=Kiranico Database

[Opt_FieldGuide_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleFieldGuide
Y=#OptionY4#
MenuAction=["https://monsterhunterwilds.wiki.fextralife.com/"]

[Opt_FieldGuide_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleFieldGuide
Y=(#OptionY4# + #OptionTextDY#)
Text=Wilds Wiki
