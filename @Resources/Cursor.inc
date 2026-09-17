; ==============================================================================
; Indicators drawn on top of everything: the chevron at the right end of the
; selected option bar, and the green dot. Menu.lua moves them; both start hidden.
; ==============================================================================

[MeterChevron]
Meter=Image
ImageName=#@#Images\glowing_chevrons.png
X=#ChevronX#
Y=#OptionY1#
W=#ChevronW#
H=#ChevronH#
Hidden=1

[MeterCursor]
Meter=Shape
X=0
Y=0
; Shape is the soft halo, Shape2 the bright core. Both are centred on the same point.
Shape=Ellipse #CursorHaloRadius#,#CursorHaloRadius#,#CursorHaloRadius# | Fill RadialGradient CursorHalo | StrokeWidth 0
Shape2=Ellipse #CursorHaloRadius#,#CursorHaloRadius#,#CursorCoreRadius# | Fill Color #CursorCoreColor# | StrokeWidth 0
CursorHalo=0,0 | #AccentGreen#,200 ; 0.0 | #AccentGreen#,90 ; 0.45 | #AccentGreen#,0 ; 1.0
Hidden=1
