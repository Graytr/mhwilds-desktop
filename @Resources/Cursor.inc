; ==============================================================================
; Indicators drawn on top of everything: the click flash and the green dot.
; Menu.lua moves them; both start hidden.
; ==============================================================================

; white flash over the clicked option bar; Menu.lua shows it and fades it out
[MeterPulse]
Meter=Shape
X=#OptionsX#
Y=#OptionY1#
Shape=Rectangle 0,0,#OptionW#,#OptionH#,3 | Fill Color 255,255,255,0 | StrokeWidth 0
Hidden=1

[MeterCursor]
Meter=Shape
X=0
Y=0
; Shape is the soft halo, Shape2 the bright core. Both are centred on the same point.
Shape=Ellipse #CursorHaloRadius#,#CursorHaloRadius#,#CursorHaloRadius# | Fill RadialGradient CursorHalo | StrokeWidth 0
Shape2=Ellipse #CursorHaloRadius#,#CursorHaloRadius#,#CursorCoreRadius# | Fill Color #CursorCoreColor# | StrokeWidth 0
CursorHalo=0,0 | #CursorHaloColor#,220 ; 0.0 | #AccentGreen#,120 ; 0.45 | #AccentGreen#,0 ; 1.0
Hidden=1

; Drives the glides. Menu.lua starts a list with "Execute N"; every step asks the
; script for the next frame and the Done action lands exactly on the target.
; List 1 moves the glow and list 2 moves the dot, so they never interrupt each other.
[MeasureAnim]
Measure=Plugin
Plugin=ActionTimer
ActionList1=Repeat GlowStep,#AnimFrameMs#,#AnimFrames# | GlowDone
GlowStep=[!CommandMeasure MenuScript "AnimStep('MeterIconGlow')"]
GlowDone=[!CommandMeasure MenuScript "AnimDone('MeterIconGlow')"]
ActionList2=Repeat DotStep,#AnimFrameMs#,#AnimFrames# | DotDone
DotStep=[!CommandMeasure MenuScript "AnimStep('MeterCursor')"]
DotDone=[!CommandMeasure MenuScript "AnimDone('MeterCursor')"]
; list 3: short delay after the mouse leaves an option, then the highlight falls back
; to the clicked option unless another option was hovered in the meantime
ActionList3=Wait #HoverRevertMs# | HoverRevert
HoverRevert=[!CommandMeasure MenuScript "RevertHover()"]
; list 4: the click flash, one PulseStep per frame
ActionList4=Repeat PulseStep,#AnimFrameMs#,#PulseFrames# | PulseDone
PulseStep=[!CommandMeasure MenuScript "PulseStep()"]
PulseDone=[!CommandMeasure MenuScript "PulseDone()"]
IgnoreWarnings=1
