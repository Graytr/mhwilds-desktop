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
BarImageNormal=#@#Images\not_selected_field_background_bar.png
BarImageSelected=#@#Images\selected_field_background_bar.png

; --- Main menu bar ------------------------------------------------------------
MainMenuX=0
MainMenuY=100
BackgroundW=(70*#SizeMultiplier#)
BackgroundH=(45*#SizeMultiplier#)

TitleX=(#MainMenuX# + (6*#SizeMultiplier#))
TitleY=(#MainMenuY# + (3*#SizeMultiplier#))
TitleFontSize=(2.5*#SizeMultiplier#)

; Icon row: six icons on a fixed pitch. IconX1..IconX6 are the slot positions.
IconSize=(4*#SizeMultiplier#)
IconPitch=(10*#SizeMultiplier#)
IconRowY=(#MainMenuY# + (9.5*#SizeMultiplier#))
IconX1=(#MainMenuX# + (1*#IconPitch#))
IconX2=(#MainMenuX# + (2*#IconPitch#))
IconX3=(#MainMenuX# + (3*#IconPitch#))
IconX4=(#MainMenuX# + (4*#IconPitch#))
IconX5=(#MainMenuX# + (5*#IconPitch#))
IconX6=(#MainMenuX# + (6*#IconPitch#))
; soft glow drawn behind the selected icon
IconGlowRadius=(3.2*#SizeMultiplier#)

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

; --- The dot ------------------------------------------------------------------
CursorHaloRadius=(1.4*#SizeMultiplier#)
CursorCoreRadius=(0.5*#SizeMultiplier#)
; how far the centre of the dot sits inside the left edge of the selected bar
CursorInsetX=(0.6*#SizeMultiplier#)
