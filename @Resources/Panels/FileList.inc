; ==============================================================================
; File list panel: a small folder browser shared by every option that shows a
; folder. Menu.lua points it somewhere with ShowFolder(<path variable>, <sort>, <title>)
; and handles the rows, which are FileRow<N> (hit area), FileIcon<N> and FileName<N>.
; Click a row to open the file or enter the folder; scroll to page; Back goes up.
; ==============================================================================

[StyleFileList]
Group=Panels | Panel_FileList

; --- measures -----------------------------------------------------------------

[mFileList]
Measure=Plugin
Plugin=FileView
Path=#ProgramsPath#
Count=#FileListRows#
ShowDotDot=0
ShowHidden=0
ShowSystem=0
HideExtensions=1
SortType=Name
SortAscending=1
DynamicVariables=1
FinishAction=[!UpdateMeasureGroup FileListChildren][!UpdateMeterGroup Panel_FileList][!Redraw]

; Where Windows keeps this user's Downloads, Desktop and Documents folders (they can
; live on another drive)
[mDownloadsPath]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders
RegValue={374DE290-123F-4565-9164-39C4925E467B}
UpdateDivider=-1

[mDesktopPath]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders
RegValue=Desktop
UpdateDivider=-1

[mDocumentsPath]
Measure=Registry
RegHKey=HKEY_CURRENT_USER
RegKey=Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders
RegValue=Personal
UpdateDivider=-1

[mFileListFolders]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FolderCount
Group=FileListChildren
UpdateDivider=-1

[mFileListFiles]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileCount
Group=FileListChildren
UpdateDivider=-1

[mFileListCount]
Measure=Calc
Formula=mFileListFolders + mFileListFiles
Group=FileListChildren
UpdateDivider=-1

[mFile1Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=1
Group=FileListChildren
UpdateDivider=-1

[mFile1Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon1.ico
Index=1
Group=FileListChildren
UpdateDivider=-1

[mFile2Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=2
Group=FileListChildren
UpdateDivider=-1

[mFile2Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon2.ico
Index=2
Group=FileListChildren
UpdateDivider=-1

[mFile3Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=3
Group=FileListChildren
UpdateDivider=-1

[mFile3Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon3.ico
Index=3
Group=FileListChildren
UpdateDivider=-1

[mFile4Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=4
Group=FileListChildren
UpdateDivider=-1

[mFile4Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon4.ico
Index=4
Group=FileListChildren
UpdateDivider=-1

[mFile5Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=5
Group=FileListChildren
UpdateDivider=-1

[mFile5Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon5.ico
Index=5
Group=FileListChildren
UpdateDivider=-1

[mFile6Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=6
Group=FileListChildren
UpdateDivider=-1

[mFile6Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon6.ico
Index=6
Group=FileListChildren
UpdateDivider=-1

[mFile7Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=7
Group=FileListChildren
UpdateDivider=-1

[mFile7Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon7.ico
Index=7
Group=FileListChildren
UpdateDivider=-1

[mFile8Name]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=FileName
Index=8
Group=FileListChildren
UpdateDivider=-1

[mFile8Icon]
Measure=Plugin
Plugin=FileView
Path=[mFileList]
Type=Icon
IconSize=Medium
IconPath=#@#Cache\icon8.ico
Index=8
Group=FileListChildren
UpdateDivider=-1

; --- meters -------------------------------------------------------------------

[PanelFileListBg]
Meter=Shape
MeterStyle=StyleFileList
X=#PanelX#
Y=#PanelY#
Shape=Rectangle 0,0,#PanelW#,#FileListH#,6 | Fill Color #PanelBgColor# | StrokeWidth 1 | Stroke Color #PanelBorderColor#
Hidden=1
MouseScrollUpAction=[!CommandMeasure MenuScript "FileListScroll(-1)"]
MouseScrollDownAction=[!CommandMeasure MenuScript "FileListScroll(1)"]

[PanelFileListTitle]
Meter=String
MeterStyle=StylePanelTitle | StyleFileList
X=#PanelInnerX#
Y=(#PanelY# + #PanelPad#)
W=(#PanelInnerW# - (38*#SizeMultiplier#))
Text=Files

[PanelFileListCount]
Meter=String
MeterStyle=StylePanelText | StyleFileList
MeasureName=mFileListCount
StringAlign=Right
X=(#PanelX# + #PanelW# - #PanelPad# - (19*#SizeMultiplier#))
Y=(#PanelY# + #PanelPad# + (0.4*#SizeMultiplier#))
Text=%1 items

[PanelFileListBack]
Meter=String
MeterStyle=StylePanelButton | StyleFileList
StringAlign=Right
X=(#PanelX# + #PanelW# - #PanelPad# - (13*#SizeMultiplier#))
Y=(#PanelY# + #PanelPad# + (0.4*#SizeMultiplier#))
Text=Back
LeftMouseUpAction=[!CommandMeasure MenuScript "FileListBack()"]

[PanelFileListOpen]
Meter=String
MeterStyle=StylePanelButton | StyleFileList
StringAlign=Right
X=(#PanelX# + #PanelW# - #PanelPad#)
Y=(#PanelY# + #PanelPad# + (0.4*#SizeMultiplier#))
Text=Open Folder
LeftMouseUpAction=[!CommandMeasure MenuScript "FileListOpen()"]

[FileRow1]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY1#

[FileIcon1]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile1Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY1# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName1]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile1Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY1# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow2]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY2#

[FileIcon2]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile2Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY2# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName2]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile2Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY2# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow3]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY3#

[FileIcon3]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile3Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY3# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName3]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile3Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY3# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow4]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY4#

[FileIcon4]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile4Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY4# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName4]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile4Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY4# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow5]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY5#

[FileIcon5]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile5Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY5# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName5]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile5Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY5# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow6]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY6#

[FileIcon6]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile6Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY6# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName6]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile6Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY6# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow7]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY7#

[FileIcon7]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile7Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY7# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName7]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile7Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY7# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1

[FileRow8]
Meter=Shape
MeterStyle=StyleFileRow | StyleFileList
Y=#FileRowY8#

[FileIcon8]
Meter=Image
MeterStyle=StyleFileRowChild | StyleFileList
MeasureName=mFile8Icon
X=(#PanelInnerX# + #PanelPad#)
Y=(#FileRowY8# + ((#FileRowH# - #FileIconSize#) / 2))
W=#FileIconSize#
H=#FileIconSize#

[FileName8]
Meter=String
MeterStyle=StylePanelText | StyleFileRowChild | StyleFileList
MeasureName=mFile8Name
X=(#PanelInnerX# + (2*#PanelPad#) + #FileIconSize#)
Y=(#FileRowY8# + (1.1*#SizeMultiplier#))
W=(#PanelInnerW# - (3*#PanelPad#) - #FileIconSize#)
Text=%1
