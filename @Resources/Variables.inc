; ==============================================================================
; Variables for the camp menu.
; Every size is a multiple of SizeMultiplier so the whole skin scales together.
; Formulas are written fully parenthesised, which lets Menu.lua evaluate them too.
; ==============================================================================
[Variables]
SizeMultiplier=10

; --- Colours ------------------------------------------------------------------
FontFamily=Trebuchet MS
FontColor=223,215,194
; option labels: dim until selected, like the game
OptionTextColor=190,184,168
OptionTextColorSelected=#FontColor#
; icons: plain, hovered / selected-but-closed, and open menu
IconTintNormal=255,255,255,255
IconTintHover=113,195,68,180
IconTintSelected=176,214,64,255
; the green used by the glow and the dot
AccentGreen=176,214,64
CursorCoreColor=232,255,150,255

; --- Images -------------------------------------------------------------------
BarImageNormal=#@#Images\bar_normal.png
BarImageSelected=#@#Images\bar_selected.png

; --- Main menu bar ------------------------------------------------------------
MainMenuX=0
MainMenuY=100
BackgroundW=(70*#SizeMultiplier#)
BackgroundH=(45*#SizeMultiplier#)

TitleX=(#MainMenuX# + (6*#SizeMultiplier#))
TitleY=(#MainMenuY# + (3*#SizeMultiplier#))
TitleFontSize=(2.5*#SizeMultiplier#)

; Icon row: six icons on a fixed pitch. Slot N is centred 2 units right of
; MainMenuX + N*IconPitch, on the IconRowCenterY line. Neither depends on IconSize,
; so the icons can be resized without moving their slots.
IconSize=(4.8*#SizeMultiplier#)
IconPitch=(10*#SizeMultiplier#)
IconRowCenterY=(#MainMenuY# + (11.5*#SizeMultiplier#))
IconRowY=(#IconRowCenterY# - (#IconSize# / 2))
IconX1=(#MainMenuX# + (1*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX2=(#MainMenuX# + (2*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX3=(#MainMenuX# + (3*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX4=(#MainMenuX# + (4*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX5=(#MainMenuX# + (5*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
IconX6=(#MainMenuX# + (6*#IconPitch#) + (2*#SizeMultiplier#) - (#IconSize# / 2))
; soft glow drawn behind the selected icon
IconGlowRadius=(3.6*#SizeMultiplier#)

; --- Option bars (the rows of a sub-menu) -------------------------------------
OptionsX=(#MainMenuX# + (9*#SizeMultiplier#))
OptionsY=(#MainMenuY# + (18*#SizeMultiplier#))
OptionPitch=(5*#SizeMultiplier#)
OptionH=(5*#SizeMultiplier#)
OptionW=(100*#SizeMultiplier#)
OptionSelectedW=(50*#SizeMultiplier#)
OptionTextDX=(3*#SizeMultiplier#)
OptionTextDY=(1.1*#SizeMultiplier#)
OptionFontSize=(1.8*#SizeMultiplier#)
OptionY1=(#OptionsY# + (0*#OptionPitch#))
OptionY2=(#OptionsY# + (1*#OptionPitch#))
OptionY3=(#OptionsY# + (2*#OptionPitch#))
OptionY4=(#OptionsY# + (3*#OptionPitch#))
OptionY5=(#OptionsY# + (4*#OptionPitch#))
OptionY6=(#OptionsY# + (5*#OptionPitch#))

; chevron at the right end of the selected bar
ChevronX=(#OptionsX# + #OptionSelectedW#)
ChevronW=(4*#SizeMultiplier#)
ChevronH=#OptionH#

; --- Animation ------------------------------------------------------------------
; the glow and the dot glide to their targets: AnimFrames steps of AnimFrameMs each
AnimFrames=12
AnimFrameMs=16
; set to 1 to have Menu.lua narrate what it does in the Rainmeter log
DebugLog=0

; --- The dot ------------------------------------------------------------------
CursorHaloRadius=(1.4*#SizeMultiplier#)
CursorCoreRadius=(0.5*#SizeMultiplier#)
; how far the centre of the dot sits inside the left edge of the selected bar
CursorInsetX=(0.6*#SizeMultiplier#)
