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
LeftMouseUpAction=[!CommandMeasure MenuScript "ClickOption('#CURRENTSECTION#')"]

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
LeftMouseUpAction=[!CommandMeasure MenuScript "ClickOption('#CURRENTSECTION#')"]
