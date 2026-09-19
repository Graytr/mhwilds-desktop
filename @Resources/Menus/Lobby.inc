; ==============================================================================
; Change Lobby menu: everything online.
;
; Every option is a bar (Opt_<List>_<N>) plus its label (Opt_<List>_<N>_Text), and an
; arrow (Opt_<List>_<N>_Arrow) when it opens something to the right. MenuAction on the
; bar runs when the option is clicked: bangs, a program or path in ["quotes"], or a
; Menu.lua call such as ShowFolder, ShowPanel or OpenSubmenu.
; A sub-menu is a second list (Style<List> / Opt_<List>_<N>) using the SubColumn styles;
; it opens in a column to the right of the list that owns it.
; To add an option, copy a group, bump <N> and use the next OptionY variable.
; ==============================================================================

; --- Lobby: the list shown when the lobby icon is clicked
[StyleLobby]
Group=Menus | Menu_Lobby

[Opt_Lobby_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleLobby
Y=#OptionY1#
MenuAction=["#DiscordShortcut#"]

[Opt_Lobby_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleLobby
Y=(#OptionY1# + #OptionTextDY#)
Text=Recommended Lobby

[Opt_Lobby_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleLobby
Y=#OptionY2#
MenuAction=["ms-settings:network-status"]

[Opt_Lobby_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleLobby
Y=(#OptionY2# + #OptionTextDY#)
Text=Lobby Search

[Opt_Lobby_3]
Meter=Image
MeterStyle=StyleOptionBar | StyleLobby
Y=#OptionY3#
MenuAction=["ms-settings:network-vpn"]

[Opt_Lobby_3_Text]
Meter=String
MeterStyle=StyleOptionText | StyleLobby
Y=(#OptionY3# + #OptionTextDY#)
Text=Private Lobby

[Opt_Lobby_4]
Meter=Image
MeterStyle=StyleOptionBar | StyleLobby
Y=#OptionY4#
MenuAction=["ms-settings:quiethours"]

[Opt_Lobby_4_Text]
Meter=String
MeterStyle=StyleOptionText | StyleLobby
Y=(#OptionY4# + #OptionTextDY#)
Text=Online Single Player
