# mhwilds-desktop
Rainmeter desktop based on the Monster Hunter Wilds camp interface. Fully customizable in terms of the programs this has the ability to open and add.

## Layout

| Path | What it is |
|---|---|
| `MHWildsMenu.ini` | Root skin: `[Rainmeter]`, `[Metadata]`, the includes and the Lua measure. |
| `@Resources/Variables.inc` | Every size and colour. Sizes are multiples of `SizeMultiplier`, so the whole skin scales together. |
| `@Resources/Styles.inc` | MeterStyles shared by the icons, option bars and labels, including their mouse actions. |
| `@Resources/Menus/MainMenu.inc` | Background, title, the glow behind the selected icon, the six icons, and the includes for the sub-menus. |
| `@Resources/Menus/<Menu>.inc` | One file per menu: its option bars and labels. |
| `@Resources/Cursor.inc` | The chevron and the green dot, included last so they draw on top. |
| `@Resources/Scripts/Menu.lua` | All state: which icon is selected, which menu is open, which option is highlighted. |
| `@Resources/Images/` | Artwork. |

## Conventions

- Icons are named `Icon_<Menu>`; option bars `Opt_<Menu>_<N>` with their label `Opt_<Menu>_<N>_Text`.
- Every sub-menu meter is in groups `Menus` and `Menu_<Menu>`, so one bang shows or hides a whole menu.
- `MenuTitle` on an icon is the header text. `MenuAction` on an option bar is what runs when it is clicked.
- Include paths are anchored with `#@#` (the `@Resources` folder). That is what lets an included file include other files: a relative path would be resolved from the including file's own folder.
- To test a change: refresh the skin, then read `%APPDATA%\Rainmeter\Rainmeter.log`.
