; ==============================================================================
; Now Playing panel (BBQ menu). Reads the player named by MediaPlayer in
; Variables.inc. The measures sleep until Menu.lua shows the panel.
; ==============================================================================

[StyleNowPlaying]
Group=Panels | Panel_NowPlaying

; --- measures -----------------------------------------------------------------

[mNPTitle]
Measure=NowPlaying
PlayerName=#MediaPlayer#
PlayerPath=#MediaPlayerPath#
PlayerType=Title
Substitute="":"Nothing playing"
Group=NowPlayingMeasures
Disabled=1

[mNPArtist]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=Artist
Group=NowPlayingMeasures
Disabled=1

[mNPAlbum]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=Album
RegExpSubstitute=1
Substitute="^(.+)$":"  -  "
Group=NowPlayingMeasures
Disabled=1

[mNPProgress]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=Progress
Group=NowPlayingMeasures
Disabled=1

[mNPPosition]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=Position
Group=NowPlayingMeasures
Disabled=1

[mNPDuration]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=Duration
Group=NowPlayingMeasures
Disabled=1

; 0 stopped, 1 playing, 2 paused: swaps the play/pause glyph
[mNPState]
Measure=NowPlaying
PlayerName=[mNPTitle]
PlayerType=State
IfCondition=mNPState = 1
IfTrueAction=[!SetOption NPPlayPause Text "[\xE769]"][!UpdateMeter NPPlayPause][!Redraw]
IfFalseAction=[!SetOption NPPlayPause Text "[\xE768]"][!UpdateMeter NPPlayPause][!Redraw]
Group=NowPlayingMeasures
Disabled=1

; --- meters -------------------------------------------------------------------

[PanelNowPlayingBg]
Meter=Shape
DynamicVariables=1
MeterStyle=StyleNowPlaying
X=#PanelX#
Y=#PanelY#
Shape=Rectangle 0,0,#PanelW#,#NowPlayingH#,6 | Fill Color #PanelBgColor# | StrokeWidth 1 | Stroke Color #PanelBorderColor#
Hidden=1

[PanelNowPlayingHeader]
Meter=String
MeterStyle=StylePanelTitle | StyleNowPlaying
X=(#PanelX# + #PanelPad#)
Y=(#PanelY# + #PanelPad#)
W=(#PanelInnerW# - (14*#SizeMultiplier#))
Text=Now Playing

[NPOpenPlayer]
Meter=String
MeterStyle=StylePanelButton | StyleNowPlaying
StringAlign=Right
X=(#PanelX# + #PanelW# - #PanelPad#)
Y=(#PanelY# + #PanelPad# + (0.4*#SizeMultiplier#))
Text=Open #MediaPlayer#
LeftMouseUpAction=[!CommandMeasure mNPTitle OpenPlayer]

[NPTrack]
Meter=String
MeterStyle=StylePanelTitle | StyleNowPlaying
MeasureName=mNPTitle
X=(#PanelX# + #PanelPad#)
Y=(#PanelBodyY# + (1*#SizeMultiplier#))
W=#PanelInnerW#
FontColor=#OptionTextColorSelected#
Text=%1

[NPArtist]
Meter=String
MeterStyle=StylePanelText | StyleNowPlaying
MeasureName=mNPArtist
MeasureName2=mNPAlbum
X=(#PanelX# + #PanelPad#)
Y=(#PanelBodyY# + (4.5*#SizeMultiplier#))
W=#PanelInnerW#
FontColor=#OptionTextColor#
Text=%1%2

[NPProgress]
Meter=Bar
MeterStyle=StyleStatusBar | StyleNowPlaying
MeasureName=mNPProgress
Y=(#PanelBodyY# + (8.5*#SizeMultiplier#))

[NPTime]
Meter=String
MeterStyle=StylePanelText | StyleNowPlaying
MeasureName=mNPPosition
MeasureName2=mNPDuration
X=(#PanelX# + #PanelPad#)
Y=(#PanelBodyY# + (9.6*#SizeMultiplier#))
FontColor=#OptionTextColor#
Text=%1 / %2

; transport buttons use the Segoe MDL2 Assets icon font that ships with Windows 10
[NPPrevious]
Meter=String
MeterStyle=StylePanelButton | StyleNowPlaying
FontFace=Segoe MDL2 Assets
FontSize=(2.4*#SizeMultiplier#)
StringAlign=Center
X=(#PanelX# + (#PanelW# / 2) - (8*#SizeMultiplier#))
Y=(#PanelBodyY# + (12.5*#SizeMultiplier#))
Text=[\xE892]
LeftMouseUpAction=[!CommandMeasure mNPTitle Previous]

[NPPlayPause]
Meter=String
MeterStyle=StylePanelButton | StyleNowPlaying
FontFace=Segoe MDL2 Assets
FontSize=(3*#SizeMultiplier#)
StringAlign=Center
X=(#PanelX# + (#PanelW# / 2))
Y=(#PanelBodyY# + (12*#SizeMultiplier#))
Text=[\xE768]
LeftMouseUpAction=[!CommandMeasure mNPTitle PlayPause]

[NPNext]
Meter=String
MeterStyle=StylePanelButton | StyleNowPlaying
FontFace=Segoe MDL2 Assets
FontSize=(2.4*#SizeMultiplier#)
StringAlign=Center
X=(#PanelX# + (#PanelW# / 2) + (8*#SizeMultiplier#))
Y=(#PanelBodyY# + (12.5*#SizeMultiplier#))
Text=[\xE893]
LeftMouseUpAction=[!CommandMeasure mNPTitle Next]
