# mhwilds-desktop

A Rainmeter skin that turns your desktop into the Monster Hunter Wilds tent menu, with every option wired to something useful on your PC. A fan project; not affiliated with Capcom.

## Install

1. Clone or copy this folder into your Rainmeter `Skins` folder as `mhwilds-desktop`.
2. In Rainmeter's Manage window, load `mhwilds-desktop\MHWildsMenu.ini`.
3. Drop shortcuts (`.lnk` or `.url`) to your programs into `@Resources\Customize\Programs` and to your games into `@Resources\Customize\Games`. Git ignores their contents, so they stay yours.
4. Set `MediaPlayer` (and `MediaPlayerPath`) in `@Resources\Variables.inc` if you use something other than Spotify.

Needs Rainmeter 4.4 or newer. Everything else it uses (Lua, FileView, ActionTimer, InputText) ships with Rainmeter.

## Using it

- Hover an icon to select it; the glow follows. Click it to open its menu, click it again to close everything.
- Hover an option to preview it, click it to select it and run it. When you move away, the highlight falls back to what you clicked.
- Options with an arrow open something to the right: a sub-menu in a second column, or a panel. Right-click any option to close the sub-menu, or the menu if none is open.
- Folders open in the skin's own file list. Click a row to open it, scroll with the wheel, Back goes up a folder, Open Folder opens the real Explorer window. Clicking any other option closes the panel.

| Menu | Options |
|---|---|
| Item Box | Item Pouch: Desktop, Downloads (newest first). Item Box: This PC (drive list), Documents. Sell Items: the Recycle Bin. |
| Equipment | Change Equipment (your program shortcuts), Customize Bowgun (Windows Settings), View Loadout (Task Manager) |
| Palico | Palico Status (CPU, memory, disk, network, uptime), Call Discord, Devices |
| Quest | Quest Board (your game shortcuts), Post a Quest (Steam library), Return to Camp: Sleep (immediate), Restart and Shut Down (15 second countdown), Cancel Shutdown |
| Audio | Now Playing (media panel with transport buttons), Sound Settings, Volume Mixer |
| Appearance | Manage Rainmeter, Refresh Skins, Wallpaper, Edit This Skin, Run Command |

Desktop, Documents and Downloads are found through Windows, so they work even when those folders live on another drive.

## How it is built

| Path | What it is |
|---|---|
| `MHWildsMenu.ini` | Root skin: `[Rainmeter]`, `[Metadata]`, the includes and the Lua measure. |
| `@Resources/Variables.inc` | Every size, colour and path. Sizes are multiples of `SizeMultiplier`, so the whole skin scales together. |
| `@Resources/Styles.inc` | MeterStyles shared by the icons, option bars, labels, arrows and panels, including their mouse actions. |
| `@Resources/Menus/MainMenu.inc` | Background, title, the glow behind the selected icon, the six icons, and the includes for the menus. |
| `@Resources/Menus/<Menu>.inc` | One file per icon: its list of options plus any sub-menu lists. |
| `@Resources/Panels/*.inc` | The panels that open to the right: file list, Now Playing, Palico status, run box. |
| `@Resources/Cursor.inc` | The click flash, the green dot and the animation timer, included last so they draw on top. |
| `@Resources/Scripts/Menu.lua` | All behaviour: which icon is selected, which columns and panel are open, which options are highlighted, and the glides. |
| `@Resources/Images/` | Artwork, kept at about twice its on-screen size. |

The INI files only describe how things look. Every mouse action calls a function in `Menu.lua`, which is heavily commented and is the place to read if you want to change behaviour.

## Adding or changing an option

Every option is a bar plus a label in its menu's file, and an arrow if it opens something to the right:

```ini
[Opt_Quest_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY1#
MenuAction=[!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]

[Opt_Quest_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY1# + #OptionTextDY#)
Text=Quest Board

[Opt_Quest_1_Arrow]
Meter=Image
MeterStyle=StyleOptionArrow | StyleQuest
Y=#OptionY1#
```

`MenuAction` is anything Rainmeter can run: a program or path in `["quotes"]`, bangs such as `[!Manage]`, or a call into the script:

- `ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')` shows a folder in the file list. The first argument is the name of a variable (or a measure) holding the path, the sort is `Name`, `Size`, `Type` or `Date`, then the header text and an optional extension filter. An empty path lists the drives.
- `ShowPanel('Status')` shows a panel: `FileList`, `NowPlaying`, `Status` or `Run`.
- `OpenSubmenu('Camp')` opens the list `Camp` in the second column; `BackMenu()` closes it.

To add a sixth option, copy a group, use the next number and `OptionY6`.

## Adding a sub-menu

A sub-menu is another list in the same file whose meters add the second-column styles. Give it a style that puts it in the `Menus` group, its own `Opt_<List>_<N>` groups, and point a parent option at it with `OpenSubmenu`:

```ini
[StyleCamp]
Group=Menus | Menu_Camp

[Opt_Camp_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleSubBarColumn | StyleCamp
Y=#OptionY1#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]

[Opt_Camp_1_Text]
Meter=String
MeterStyle=StyleOptionText | StyleSubTextColumn | StyleCamp
Y=(#OptionY1# + #OptionTextDY#)
Text=Sleep
```

An arrow in the second column uses `StyleOptionArrow | StyleSubArrowColumn`.

## Conventions

- Icons are `Icon_<Menu>`; option bars `Opt_<List>_<N>` with labels `Opt_<List>_<N>_Text` and optional arrows `Opt_<List>_<N>_Arrow`. A list is a menu (same name as its icon) or a sub-menu. `MenuTitle` on an icon is the header text.
- Every list meter is in groups `Menus` and `Menu_<List>`; every panel meter in `Panels` and `Panel_<Name>`. One bang shows or hides a whole list or panel.
- Panel measures live in `<Name>Measures` groups and only run while their panel is showing. Panel meters use `DynamicVariables=1` and position themselves from `PanelX`, which the script sets to `PanelXNear` or `PanelXFar` depending on whether a second column is open.
- Include paths are anchored with `#@#` (the `@Resources` folder). That is what lets an included file include other files: a relative path would be resolved from the including file's own folder.

## Tips and gotchas

- Set `DebugLog=1` in `Variables.inc` and the script narrates what it does in the Rainmeter log (`%APPDATA%\Rainmeter\Rainmeter.log`). Refresh the skin after a change and read the log for errors.
- Notepad++ highlights `.inc` files as INI if you add `inc` under Settings, Style Configurator, ini, User ext.
- Rainmeter bakes a variable's references to other variables when the skin loads, so a variable derived from one the script changes at runtime (such as `PanelX`) will not follow it. Write the expression in the meter instead.
- Rainmeter counts hidden meters' positions when sizing the skin window, so the transparent window is wider than the drawn menu. Transparent areas are click-through, so nothing underneath is blocked.
