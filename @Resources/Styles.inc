; ==============================================================================
; MeterStyles: shared looks and behaviour.
; A meter lists the styles it uses with  MeterStyle=StyleA | StyleB  and anything
; it sets itself wins over the style. #CURRENTSECTION# inside a style resolves to
; the meter using it, so one line of mouse actions serves every icon and option.
; ==============================================================================

[StyleTitle]
FontFace=#FontFamily#
FontColor=#FontColor#
FontSize=#TitleFontSize#
StringEffect=Border
FontEffectColor=0,0,0,255
AntiAlias=1

[StyleIcon]
Group=Icons
Y=#IconRowY#
W=#IconSize#
H=#IconSize#
ImageTint=#IconTintNormal#
MouseOverAction=[!CommandMeasure MenuScript "HoverIcon('#CURRENTSECTION#')"]
MouseLeaveAction=[!CommandMeasure MenuScript "LeaveIcon('#CURRENTSECTION#')"]
LeftMouseUpAction=[!CommandMeasure MenuScript "ClickIcon('#CURRENTSECTION#')"]

[StyleOptionBar]
ImageName=#BarImageNormal#
X=#OptionsX#
W=#OptionW#
H=#OptionH#
Hidden=1
MouseOverAction=[!CommandMeasure MenuScript "HoverOption('#CURRENTSECTION#')"]
MouseLeaveAction=[!CommandMeasure MenuScript "LeaveOption('#CURRENTSECTION#')"]
LeftMouseUpAction=[!CommandMeasure MenuScript "ClickOption('#CURRENTSECTION#')"]
RightMouseUpAction=[!CommandMeasure MenuScript "BackMenu()"]

[StyleOptionText]
FontFace=#FontFamily#
FontColor=#OptionTextColor#
FontSize=#OptionFontSize#
StringEffect=Border
FontEffectColor=0,0,0,255
AntiAlias=1
X=(#OptionsX# + #OptionTextDX#)
Hidden=1
; the label sits on top of its bar, so it needs the same actions
MouseOverAction=[!CommandMeasure MenuScript "HoverOption('#CURRENTSECTION#')"]
MouseLeaveAction=[!CommandMeasure MenuScript "LeaveOption('#CURRENTSECTION#')"]
LeftMouseUpAction=[!CommandMeasure MenuScript "ClickOption('#CURRENTSECTION#')"]
RightMouseUpAction=[!CommandMeasure MenuScript "BackMenu()"]

; --- Panels -------------------------------------------------------------------

[StylePanelText]
FontFace=#FontFamily#
FontColor=#FontColor#
FontSize=#PanelFontSize#
StringEffect=Border
FontEffectColor=0,0,0,200
AntiAlias=1
ClipString=1
Hidden=1

[StylePanelTitle]
FontFace=#FontFamily#
FontColor=#FontColor#
FontSize=#PanelTitleFontSize#
StringEffect=Border
FontEffectColor=0,0,0,200
AntiAlias=1
ClipString=1
Hidden=1

; small text buttons in panel headers: turn green under the mouse
[StylePanelButton]
FontFace=#FontFamily#
FontColor=#OptionTextColor#
FontSize=#PanelFontSize#
StringEffect=Border
FontEffectColor=0,0,0,200
AntiAlias=1
Hidden=1
MouseOverAction=[!SetOption #CURRENTSECTION# FontColor "#AccentGreen#"][!UpdateMeter #CURRENTSECTION#][!Redraw]
MouseLeaveAction=[!SetOption #CURRENTSECTION# FontColor "#OptionTextColor#"][!UpdateMeter #CURRENTSECTION#][!Redraw]

; one row of the file list: an all-but-invisible hit area that Menu.lua tints on hover
[StyleFileRow]
Shape=Rectangle 0,0,#PanelInnerW#,#FileRowH#,3 | Fill Color 0,0,0,1 | StrokeWidth 0
X=#PanelInnerX#
Hidden=1
MouseOverAction=[!CommandMeasure MenuScript "FileRowHover('#CURRENTSECTION#')"]
MouseLeaveAction=[!CommandMeasure MenuScript "FileRowLeave('#CURRENTSECTION#')"]
LeftMouseUpAction=[!CommandMeasure MenuScript "FileRowClick('#CURRENTSECTION#')"]
MouseScrollUpAction=[!CommandMeasure MenuScript "FileListScroll(-1)"]
MouseScrollDownAction=[!CommandMeasure MenuScript "FileListScroll(1)"]

; the icon and name drawn on a row forward the same events (their names end in the row number)
[StyleFileRowChild]
Hidden=1
MouseOverAction=[!CommandMeasure MenuScript "FileRowHover('#CURRENTSECTION#')"]
MouseLeaveAction=[!CommandMeasure MenuScript "FileRowLeave('#CURRENTSECTION#')"]
LeftMouseUpAction=[!CommandMeasure MenuScript "FileRowClick('#CURRENTSECTION#')"]
MouseScrollUpAction=[!CommandMeasure MenuScript "FileListScroll(-1)"]
MouseScrollDownAction=[!CommandMeasure MenuScript "FileListScroll(1)"]

[StyleStatusLabel]
FontFace=#FontFamily#
FontColor=#OptionTextColor#
FontSize=#PanelFontSize#
StringEffect=Border
FontEffectColor=0,0,0,200
AntiAlias=1
X=#PanelInnerX#
Hidden=1

[StyleStatusValue]
FontFace=#FontFamily#
FontColor=#FontColor#
FontSize=#PanelFontSize#
StringEffect=Border
FontEffectColor=0,0,0,200
AntiAlias=1
StringAlign=Right
X=(#PanelX# + #PanelW# - #PanelPad#)
Hidden=1

[StyleStatusBar]
BarOrientation=Horizontal
BarColor=#AccentGreen#,220
SolidColor=255,255,255,25
X=#PanelInnerX#
W=#PanelInnerW#
H=(0.6*#SizeMultiplier#)
Hidden=1
