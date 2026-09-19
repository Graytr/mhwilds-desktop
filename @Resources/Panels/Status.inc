; ==============================================================================
; Palico status panel: how the machine is doing. The measures sleep until
; Menu.lua shows the panel.
; ==============================================================================

[StyleStatus]
Group=Panels | Panel_Status

; --- measures -----------------------------------------------------------------

[mCPU]
Measure=CPU
Group=StatusMeasures
Disabled=1

[mRAM]
Measure=PhysicalMemory
Group=StatusMeasures
Disabled=1

[mDiskUsed]
Measure=FreeDiskSpace
Drive=C:
InvertMeasure=1
Group=StatusMeasures
Disabled=1

[mDiskFree]
Measure=FreeDiskSpace
Drive=C:
Group=StatusMeasures
Disabled=1

[mNetIn]
Measure=NetIn
Group=StatusMeasures
Disabled=1

[mNetOut]
Measure=NetOut
Group=StatusMeasures
Disabled=1

[mUptime]
Measure=Uptime
Format=%4!i!d %3!i!h %2!i!m
Group=StatusMeasures
Disabled=1

; --- meters -------------------------------------------------------------------

[PanelStatusBg]
Meter=Shape
DynamicVariables=1
MeterStyle=StyleStatus
X=#PanelX#
Y=#PanelY#
Shape=Rectangle 0,0,#PanelW#,#StatusH#,6 | Fill Color #PanelBgColor# | StrokeWidth 1 | Stroke Color #PanelBorderColor#
Hidden=1

[PanelStatusHeader]
Meter=String
MeterStyle=StylePanelTitle | StyleStatus
X=(#PanelX# + #PanelPad#)
Y=(#PanelY# + #PanelPad#)
W=#PanelInnerW#
Text=Palico Deployment Status

[StatusCPULabel]
Meter=String
MeterStyle=StyleStatusLabel | StyleStatus
Y=(#PanelBodyY# + (0*#StatusRowH#))
Text=CPU

[StatusCPUValue]
Meter=String
MeterStyle=StyleStatusValue | StyleStatus
MeasureName=mCPU
Y=(#PanelBodyY# + (0*#StatusRowH#))
Text=%1%

[StatusCPUBar]
Meter=Bar
MeterStyle=StyleStatusBar | StyleStatus
MeasureName=mCPU
Y=(#PanelBodyY# + (0*#StatusRowH#) + (3*#SizeMultiplier#))

[StatusRAMLabel]
Meter=String
MeterStyle=StyleStatusLabel | StyleStatus
Y=(#PanelBodyY# + (1*#StatusRowH#))
Text=Memory

[StatusRAMValue]
Meter=String
MeterStyle=StyleStatusValue | StyleStatus
MeasureName=mRAM
Percentual=1
Y=(#PanelBodyY# + (1*#StatusRowH#))
Text=%1% used

[StatusRAMBar]
Meter=Bar
MeterStyle=StyleStatusBar | StyleStatus
MeasureName=mRAM
Y=(#PanelBodyY# + (1*#StatusRowH#) + (3*#SizeMultiplier#))

[StatusDiskLabel]
Meter=String
MeterStyle=StyleStatusLabel | StyleStatus
Y=(#PanelBodyY# + (2*#StatusRowH#))
Text=Drive C:

[StatusDiskValue]
Meter=String
MeterStyle=StyleStatusValue | StyleStatus
MeasureName=mDiskFree
AutoScale=1
Y=(#PanelBodyY# + (2*#StatusRowH#))
Text=%1B free

[StatusDiskBar]
Meter=Bar
MeterStyle=StyleStatusBar | StyleStatus
MeasureName=mDiskUsed
Y=(#PanelBodyY# + (2*#StatusRowH#) + (3*#SizeMultiplier#))

[StatusNetLabel]
Meter=String
MeterStyle=StyleStatusLabel | StyleStatus
Y=(#PanelBodyY# + (3*#StatusRowH#))
Text=Network

[StatusNetValue]
Meter=String
MeterStyle=StyleStatusValue | StyleStatus
MeasureName=mNetIn
MeasureName2=mNetOut
AutoScale=1
Y=(#PanelBodyY# + (3*#StatusRowH#))
Text=down %1B/s   up %2B/s

[StatusUptimeLabel]
Meter=String
MeterStyle=StyleStatusLabel | StyleStatus
Y=(#PanelBodyY# + (4*#StatusRowH#))
Text=Uptime

[StatusUptimeValue]
Meter=String
MeterStyle=StyleStatusValue | StyleStatus
MeasureName=mUptime
Y=(#PanelBodyY# + (4*#StatusRowH#))
Text=%1
