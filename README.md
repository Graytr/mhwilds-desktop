# mhwilds-desktop

A Rainmeter skin that turns your desktop into the Monster Hunter Wilds tent menu, with every option wired to something useful on your PC.

Hover an icon to select it (the glow follows), click it to open its menu, hover an option to move the dot, click to run it. Click the open icon again to close.

## What the menus do

| Menu | Options |
|---|---|
| Item Box | Item Pouch (Desktop), Item Box (This PC), Documents, Downloads (browsed inside the skin, newest first), Sell Items (Recycle Bin) |
| Equipment | Change Equipment (your program shortcuts, inside the skin), Manage Equipment (opens that folder), Task Manager, Windows Settings |
| Palico | Palico Status (CPU, memory, disk, network, uptime), Call Discord, Devices, Sound |
| Quest | Quest Board (your game shortcuts, inside the skin), Post a Quest (Steam library), Manage Quests (opens that folder) |
| BBQ | Now Playing (media panel with transport buttons), Rest (sleep immediately), Restart and Shut Down (15 second countdown), Cancel Shutdown |
| Appearance | Manage Rainmeter, Refresh Skins, Wallpaper, Edit This Skin, Run Command |

- Put shortcuts (`.lnk` or `.url`) in `@Resources\Customize\Programs` and `@Resources\Customize\Games`. Git ignores their contents.
- Set `MediaPlayer` (and `MediaPlayerPath`) in `Variables.inc` to the player you use.
- Downloads is found through Windows, so it works even when the folder lives on another drive.

## Layout

| Path | What it is |
|---|---|
| `MHWildsMenu.ini` | Root skin: `[Rainmeter]`, `[Metadata]`, the includes and the Lua measure. |
| `@Resources/Variables.inc` | Every size, colour and path. Sizes are multiples of `SizeMultiplier`, so the whole skin scales together. |
| `@Resources/Styles.inc` | MeterStyles shared by the icons, option bars, labels and panels, including their mouse actions. |
| `@Resources/Menus/MainMenu.inc` | Background, title, the glow behind the selected icon, the six icons, and the includes for the sub-menus. |
| `@Resources/Menus/<Menu>.inc` | One file per menu: its option bars, labels and actions. |
| `@Resources/Panels/*.inc` | The panels that open to the right: file list, Now Playing, Palico status, run box. |
| `@Resources/Cursor.inc` | The chevron, the green dot and the animation timer, included last so they draw on top. |
| `@Resources/Scripts/Menu.lua` | All state: which icon is selected, which menu and panel are open, which option is highlighted, plus the glides. |
| `@Resources/Images/` | Artwork, kept at about twice its on-screen size. |

## Adding or changing an option

Every option is a bar plus a label in its menu's file:

```ini
[Opt_Quest_2]
Meter=Image
MeterStyle=StyleOptionBar | StyleQuest
Y=#OptionY2#
MenuAction=["steam://open/games"]

[Opt_Quest_2_Text]
Meter=String
MeterStyle=StyleOptionText | StyleQuest
Y=(#OptionY2# + #OptionTextDY#)
Text=Post a Quest
```

`MenuAction` is anything Rainmeter can run: a program or path in `["quotes"]`, bangs such as `[!Manage]`, or a call into the script:

- `[!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]` shows a folder in the file list. The first argument is the name of a variable (or of a measure) that holds the path, the sort is `Name`, `Size`, `Type` or `Date`, then the header text and an optional extension filter.
- `[!CommandMeasure MenuScript "ShowPanel('Status')"]` shows a panel: `FileList`, `NowPlaying`, `Status` or `Run`.

To add a sixth option, copy a pair, use the next number and `OptionY6`.

## Conventions

- Icons are `Icon_<Menu>`, option bars `Opt_<Menu>_<N>` with labels `Opt_<Menu>_<N>_Text`. `MenuTitle` on an icon is the header text.
- Every sub-menu meter is in groups `Menus` and `Menu_<Menu>`; every panel meter in `Panels` and `Panel_<Name>`. One bang shows or hides a whole menu or panel.
- Panel measures live in `<Name>Measures` groups and only run while their panel is showing.
- Include paths are anchored with `#@#` (the `@Resources` folder). That is what lets an included file include other files: a relative path would be resolved from the including file's own folder.

## Tips

- Set `DebugLog=1` in `Variables.inc` and the script narrates what it does in the Rainmeter log (`%APPDATA%\Rainmeter\Rainmeter.log`). Refresh the skin after a change and read the log for errors.
- Notepad++ highlights `.inc` files as INI if you add `inc` under Settings, Style Configurator, ini, User ext.
- Rainmeter counts hidden meters' positions when sizing the skin window, so the transparent window is wider than the drawn menu. Transparent areas are click-through, so nothing underneath is blocked.
