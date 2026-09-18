# mhwilds-desktop

A Rainmeter skin that turns your desktop into the Monster Hunter Wilds tent menu, with every option wired to something useful on your PC.

Hover an icon to select it (the glow follows), click it to open its menu. Hover an option to preview it, click it to select it and run it; when you move away the highlight falls back to the option you clicked. Some options open a sub-menu in place; pick Back, or right-click any option, to go up a level. Click the open icon again to close everything.

## What the menus do

| Menu | Options |
|---|---|
| Item Box | Item Pouch opens a sub-menu of quick places (Desktop, Downloads newest first). Item Box opens a sub-menu of permanent ones (This PC as a drive list, Documents). Sell Items opens the Recycle Bin. |
| Equipment | Change Equipment (your program shortcuts), Customize Bowgun (Windows Settings), View Loadout (Task Manager) |
| Palico | Palico Status (CPU, memory, disk, network, uptime), Call Discord, Devices |
| Quest | Quest Board (your game shortcuts), Post a Quest (Steam library), Return to Camp opens a sub-menu with Sleep (immediate), Restart and Shut Down (15 second countdown) and Cancel Shutdown |
| Audio | Now Playing (media panel with transport buttons), Sound Settings, Volume Mixer |
| Appearance | Manage Rainmeter, Refresh Skins, Wallpaper, Edit This Skin, Run Command |

Folders open in the skin's own file list; its Open Folder button opens the real Explorer window, Back goes up one folder, and the mouse wheel scrolls.

- Put shortcuts (`.lnk` or `.url`) in `@Resources\Customize\Programs` and `@Resources\Customize\Games`. Git ignores their contents.
- Set `MediaPlayer` (and `MediaPlayerPath`) in `Variables.inc` to the player you use.
- Desktop, Documents and Downloads are found through Windows, so they work even when those folders live on another drive.

## Layout

| Path | What it is |
|---|---|
| `MHWildsMenu.ini` | Root skin: `[Rainmeter]`, `[Metadata]`, the includes and the Lua measure. |
| `@Resources/Variables.inc` | Every size, colour and path. Sizes are multiples of `SizeMultiplier`, so the whole skin scales together. |
| `@Resources/Styles.inc` | MeterStyles shared by the icons, option bars, labels and panels, including their mouse actions. |
| `@Resources/Menus/MainMenu.inc` | Background, title, the glow behind the selected icon, the six icons, and the includes for the menus. |
| `@Resources/Menus/<Menu>.inc` | One file per icon: its list of options plus any sub-menu lists. |
| `@Resources/Panels/*.inc` | The panels that open to the right: file list, Now Playing, Palico status, run box. |
| `@Resources/Cursor.inc` | The chevron, the green dot and the animation timer, included last so they draw on top. |
| `@Resources/Scripts/Menu.lua` | All state: which icon is selected, which lists and panel are open, which option is highlighted, plus the glides. |
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

- `[!CommandMeasure MenuScript "ShowFolder('GamesPath', 'Name', 'Games', 'lnk;url')"]` shows a folder in the file list. The first argument is the name of a variable (or of a measure) that holds the path, the sort is `Name`, `Size`, `Type` or `Date`, then the header text and an optional extension filter. An empty path lists the drives.
- `[!CommandMeasure MenuScript "ShowPanel('Status')"]` shows a panel: `FileList`, `NowPlaying`, `Status` or `Run`.
- `[!CommandMeasure MenuScript "OpenSubmenu('Camp')"]` replaces the list with the sub-menu `Camp`; `BackMenu()` goes up again.

To add a sixth option, copy a pair, use the next number and `OptionY6`.

## Adding a sub-menu

A sub-menu is just another list in the same file. Give it a title variable, a style that puts it in the `Menus` group, its own `Opt_<List>_<N>` pairs, and a Back option; then point a parent option at it with `OpenSubmenu`:

```ini
[Variables]
Menu_Camp_Title=Return to Camp

[StyleCamp]
Group=Menus | Menu_Camp

[Opt_Camp_1]
Meter=Image
MeterStyle=StyleOptionBar | StyleCamp
Y=#OptionY1#
MenuAction=[rundll32.exe powrprof.dll,SetSuspendState 0,1,0]
...
```

## Conventions

- Icons are `Icon_<Menu>`; option bars `Opt_<List>_<N>` with labels `Opt_<List>_<N>_Text`, where a list is a menu (same name as its icon) or a sub-menu. `MenuTitle` on an icon and `Menu_<List>_Title` variables hold the header texts.
- Every list meter is in groups `Menus` and `Menu_<List>`; every panel meter in `Panels` and `Panel_<Name>`. One bang shows or hides a whole list or panel.
- Panel measures live in `<Name>Measures` groups and only run while their panel is showing.
- Include paths are anchored with `#@#` (the `@Resources` folder). That is what lets an included file include other files: a relative path would be resolved from the including file's own folder.

## Tips

- Set `DebugLog=1` in `Variables.inc` and the script narrates what it does in the Rainmeter log (`%APPDATA%\Rainmeter\Rainmeter.log`). Refresh the skin after a change and read the log for errors.
- Notepad++ highlights `.inc` files as INI if you add `inc` under Settings, Style Configurator, ini, User ext.
- Rainmeter counts hidden meters' positions when sizing the skin window, so the transparent window is wider than the drawn menu. Transparent areas are click-through, so nothing underneath is blocked.
