; ==============================================================================
; Run panel (Appearance menu): a one-line command box. Menu.lua shows the panel
; first so the skin window is big enough, then the InputText box opens on top.
; Type a program, path or URL and press Enter; Escape cancels.
; ==============================================================================

[StyleRun]
Group=Panels | Panel_Run

[mRun]
Measure=Plugin
Plugin=InputText
DynamicVariables=1
X=(#PanelX# + #PanelPad#)
Y=(#PanelBodyY# + (0.5*#SizeMultiplier#))
W=#PanelInnerW#
H=(3.5*#SizeMultiplier#)
FontFace=#FontFamily#
FontSize=#PanelFontSize#
FontColor=#FontColor#
SolidColor=40,40,32
FocusDismiss=1
DefaultValue=
Command1=["$UserInput$"]

[PanelRunBg]
Meter=Shape
DynamicVariables=1
MeterStyle=StyleRun
X=#PanelX#
Y=#PanelY#
Shape=Rectangle 0,0,#PanelW#,#RunH#,6 | Fill Color #PanelBgColor# | StrokeWidth 1 | Stroke Color #PanelBorderColor#
Hidden=1

[PanelRunHeader]
Meter=String
MeterStyle=StylePanelTitle | StyleRun
X=(#PanelX# + #PanelPad#)
Y=(#PanelY# + #PanelPad#)
W=#PanelInnerW#
Text=Run a command, then press Enter (click here to reopen the box)
LeftMouseUpAction=[!CommandMeasure mRun "ExecuteBatch 1"]
