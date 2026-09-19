; ==============================================================================
; Variables for the camp menu.
; Every size is a multiple of SizeMultiplier so the whole skin scales together.
; Formulas are written fully parenthesised, which lets Menu.lua evaluate them too.
; ==============================================================================
[Variables]
SizeMultiplier=10

; --- Colours ------------------------------------------------------------------
FontFamily=Trebuchet MS
FontColor=223,215,194
; option labels: dim until selected, like the game
OptionTextColor=190,184,168
OptionTextColorSelected=#FontColor#
; icons: plain, hovered / selected-but-closed, and open menu
IconTintNormal=255,255,255,255
IconTintHover=113,195,68,180
IconTintSelected=176,214,64,255
; the green used by the glow and the dot
AccentGreen=176,214,64
CursorCoreColor=232,255,150,255

; --- Images -------------------------------------------------------------------
BarImageNormal=#@#Images\bar_normal.png
BarImageSelected=#@#Images\bar_selected.png
; the highlight of a list that does not have focus (the first column while a sub-menu
; is open) is the green bar seen through this tint, which turns it olive like the game
BarTintDim=170,160,140,255

; --- Main menu bar ------------------------------------------------------------
MainMenuX=0
MainMenuY=100
BackgroundW=(70*#SizeMultiplier#)
BackgroundH=(45*#SizeMultiplier#)

TitleX=(#MainMenuX# + (6*#SizeMultiplier#))
TitleY=(#MainMenuY# + (3*#SizeMultiplier#))
TitleFontSize=(2.5*#SizeMultiplier#)

; Icon row: six icons on a fixed pitch. Slot N is centred 2 units right of
; MainMenuX + N*IconPitch, on the IconRowCenterY line. Neither depends on IconSize,
; so the icons can be resized without moving their slots.
IconSize=(4.8*#SizeMultiplier#)
IconPitch=(10*#SizeMultiplier#)
IconRowCenterY=(#MainMenuY# + (11.5*#SizeMultiplier#))
IconRowY=(#IconRowCenterY# - (#IconSize# / 2))
IconX1=(#MainMenuX# + (1*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX2=(#MainMenuX# + (2*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX3=(#MainMenuX# + (3*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX4=(#MainMenuX# + (4*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX5=(#MainMenuX# + (5*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX6=(#MainMenuX# + (6*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
; soft glow drawn behind the selected icon
IconGlowRadius=(3.6*#SizeMultiplier#)

; --- Option bars (the rows of a sub-menu) -------------------------------------
OptionsX=(#MainMenuX# + (9*#SizeMultiplier#))
OptionsY=(#MainMenuY# + (18*#SizeMultiplier#))
OptionPitch=(5*#SizeMultiplier#)
OptionH=(5*#SizeMultiplier#)
; both bar images are painted the full width (tools\make_bars.py): a dark translucent
; block behind an unselected option, a green bar that fades out to the right over the
; selected one
OptionW=(50*#SizeMultiplier#)
OptionTextDX=(3*#SizeMultiplier#)
OptionTextDY=(1.1*#SizeMultiplier#)
OptionFontSize=(1.8*#SizeMultiplier#)
OptionY1=(#OptionsY# + (0*#OptionPitch#))
OptionY2=(#OptionsY# + (1*#OptionPitch#))
OptionY3=(#OptionsY# + (2*#OptionPitch#))
OptionY4=(#OptionsY# + (3*#OptionPitch#))
OptionY5=(#OptionsY# + (4*#OptionPitch#))
OptionY6=(#OptionsY# + (5*#OptionPitch#))

; second column: a sub-menu opens to the right of the list that owns it, leaving a
; small gap for the dot (panels keep the same gap)
ColumnGap=(4*#SizeMultiplier#)
SubOptionsX=(#OptionsX# + #OptionW# + #ColumnGap#)
; arrows mark options that open a sub-menu or a panel; they sit inside the faded right
; end of the bar and stay visible whether or not the option is selected
ArrowW=(4*#SizeMultiplier#)
ArrowH=#OptionH#
ArrowX=(#OptionsX# + #OptionW# - #ArrowW# - (0.5*#SizeMultiplier#))
SubArrowX=(#SubOptionsX# + #OptionW# - #ArrowW# - (0.5*#SizeMultiplier#))

; --- Animation ------------------------------------------------------------------
; the glow and the dot glide to their targets: AnimFrames steps of AnimFrameMs each
AnimFrames=12
AnimFrameMs=16
; when the mouse leaves an option, wait this long before the highlight returns to the
; clicked option (long enough to cross the gap between two bars without flicker)
HoverRevertMs=80
; click feedback: a white flash over the clicked bar that fades out over PulseFrames frames
PulseFrames=10
PulsePeakAlpha=150
; the selected bar's artwork is drawn at this opacity (255 = exactly as painted)
BarSelectedAlpha=255
; set to 1 to have Menu.lua narrate what it does in the Rainmeter log
DebugLog=0

; --- The dot ------------------------------------------------------------------
CursorHaloRadius=(1.4*#SizeMultiplier#)
CursorCoreRadius=(0.5*#SizeMultiplier#)
; how far the centre of the dot sits inside the left edge of the selected bar
CursorInsetX=(0.6*#SizeMultiplier#)

; --- Folders and programs the menus point at ----------------------------------
; Drop shortcuts (.lnk / .url) into the two Customize folders; git ignores them.
; (Desktop, Documents and Downloads are not here: the file list reads their locations
; from Windows, see the m...Path measures in Panels\FileList.inc.)
; an empty path makes the file list show the drives, like This PC
ThisPCPath=
ProgramsPath=#@#Customize\Programs
GamesPath=#@#Customize\Games
DiscordShortcut=%APPDATA%\Microsoft\Windows\Start Menu\Programs\Discord.lnk
; player for the BBQ menu's Now Playing panel, one of:
; AIMP, CAD, foobar2000, iTunes, MediaMonkey, Spotify, WinAmp, WLM, WMP
MediaPlayer=Spotify
; where that player lives, used by the Open button (leave empty if unsure)
MediaPlayerPath=%APPDATA%\Spotify\Spotify.exe

; --- Panels: the area to the right of the option bars -------------------------
; panels sit right of the list they were opened from. Menu.lua switches PanelX between
; these two as a sub-menu opens or closes (panel meters use DynamicVariables=1 for that)
PanelXNear=(#OptionsX# + #OptionW# + #ColumnGap#)
PanelXFar=(#SubOptionsX# + #OptionW# + #ColumnGap#)
PanelX=#PanelXNear#
PanelY=#OptionsY#
PanelW=(80*#SizeMultiplier#)
PanelPad=(1.5*#SizeMultiplier#)
PanelHeaderH=(5*#SizeMultiplier#)
PanelFontSize=(1.6*#SizeMultiplier#)
PanelTitleFontSize=(2*#SizeMultiplier#)
PanelBgColor=18,18,14,205
PanelBorderColor=150,140,110,140
; (there is deliberately no PanelInnerX: Rainmeter bakes a variable's references at load,
; so a variable derived from PanelX would not follow it when Menu.lua moves the panels;
; panel meters write (#PanelX# + #PanelPad#) instead)
PanelInnerW=(#PanelW# - (2*#PanelPad#))
PanelBodyY=(#PanelY# + #PanelHeaderH# + #PanelPad#)
RowHoverColor=176,214,64,60

; file list panel
FileListRows=8
FileRowH=(4.5*#SizeMultiplier#)
FileIconSize=(3.2*#SizeMultiplier#)
FileListH=(#PanelHeaderH# + (#FileListRows# * #FileRowH#) + (2*#PanelPad#))
FileRowY1=(#PanelBodyY# + (0*#FileRowH#))
FileRowY2=(#PanelBodyY# + (1*#FileRowH#))
FileRowY3=(#PanelBodyY# + (2*#FileRowH#))
FileRowY4=(#PanelBodyY# + (3*#FileRowH#))
FileRowY5=(#PanelBodyY# + (4*#FileRowH#))
FileRowY6=(#PanelBodyY# + (5*#FileRowH#))
FileRowY7=(#PanelBodyY# + (6*#FileRowH#))
FileRowY8=(#PanelBodyY# + (7*#FileRowH#))

; status and now playing panels
StatusRowH=(5*#SizeMultiplier#)
StatusH=(#PanelHeaderH# + (5*#StatusRowH#) + (2*#PanelPad#))
NowPlayingH=(24*#SizeMultiplier#)
RunH=(#PanelHeaderH# + (6*#SizeMultiplier#))
