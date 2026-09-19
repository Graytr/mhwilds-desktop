"""Paints the skin's generated artwork into @Resources/Images, modelled on the game's tent menu.

block_1.png .. block_6.png   the translucent brown block behind a list of 1 to 6 options: soft
                             edges, fading out towards the right like the game's
bar_selected.png             the solid green bar over the selected option, a little brighter at
                             the left with a faint diagonal weave (Menu.lua draws this same image
                             through BarTintDim for the highlight of a column without focus)
menu_bar.png                 the icon bar: tools/src/menu_bar.png widened, thinning gently from the
                             Equipment icon to the Appearance icon and then fading out, like the game's

Everything is painted at twice its on-screen size (OptionW x OptionH = 500 x 50 with
SizeMultiplier=10). Needs Pillow:  python -m pip install pillow
Change the numbers below, run  python tools/make_images.py  and refresh the skin.
"""
import math
import os
import random

from PIL import Image

W, ROW = 1000, 100
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "@Resources", "Images")

# the block behind a list: warm dark brown, 62% opaque at the left, gone by the right edge
BLOCK_RGB = (70, 56, 40)
BLOCK_ALPHA = 0.62
BLOCK_FADE_START = 0.55         # where (0..1 across the bar) the fade to transparent begins
BLOCK_FEATHER = 6               # soft left, top and bottom edges, in painted pixels

# the selected bar: the game's yellow-green, solid all the way across
GREEN = (140, 188, 58)
GREEN_ALPHA = 0.95
GREEN_FEATHER = 3               # soft edges all round, in painted pixels
LEFT_BRIGHT, RIGHT_BRIGHT = 1.08, 0.90   # brightness at the left edge and at the right edge
WEAVE_PERIOD, WEAVE_DEPTH = 14, 0.05     # diagonal texture: pixels per stripe, +/- brightness
GRAIN = 0.02                             # random per-pixel brightness jitter

# the icon bar: the source art, how wide to make it (BackgroundW = 80 units, drawn at half
# size), which interior column of the source is copied to widen it, and where the source's
# right frame starts (it is dropped)
MENU_BAR_SRC = os.path.join(os.path.dirname(os.path.abspath(__file__)), "src", "menu_bar.png")
MENU_BAR_W = 1600
MENU_BAR_TEMPLATE_X = 1200
MENU_BAR_RIGHT_FRAME_X = 1392
# its opacity along the bar, in painted pixels (2 per screen pixel): solid up to the Equipment
# icon, a gentle slide down to MENU_BAR_ALPHA_AT_APPEARANCE under the Appearance icon, then a
# steeper fade to nothing at the end. Icon N is centred at 2 * (N * 80 + 15).
MENU_BAR_GENTLE_FROM = 350          # under the Equipment icon (icon 2)
MENU_BAR_GENTLE_TO = 1310           # under the Appearance icon (icon 8)
MENU_BAR_ALPHA_AT_APPEARANCE = 0.6


def smoothstep(t):
    t = min(max(t, 0.0), 1.0)
    return t * t * (3 - 2 * t)


def clamp(v):
    return max(0, min(255, int(round(v))))


def feather(distance, width):
    """0 at the very edge, 1 once `width` pixels inside it."""
    return smoothstep((distance + 0.5) / width) if width > 0 else 1.0


def block(rows):
    h = rows * ROW
    im = Image.new("RGBA", (W, h))
    px = im.load()
    for x in range(W):
        u = x / (W - 1)
        a = BLOCK_ALPHA * feather(x, BLOCK_FEATHER)
        if u > BLOCK_FADE_START:
            a *= 1 - smoothstep((u - BLOCK_FADE_START) / (1 - BLOCK_FADE_START))
        for y in range(h):
            ay = a * feather(y, BLOCK_FEATHER) * feather(h - 1 - y, BLOCK_FEATHER)
            px[x, y] = BLOCK_RGB + (clamp(255 * ay),)
    return im


def selected():
    random.seed(7)
    im = Image.new("RGBA", (W, ROW))
    px = im.load()
    for x in range(W):
        u = x / (W - 1)
        a = GREEN_ALPHA * feather(x, GREEN_FEATHER) * feather(W - 1 - x, GREEN_FEATHER)
        bright = LEFT_BRIGHT + (RIGHT_BRIGHT - LEFT_BRIGHT) * u
        for y in range(ROW):
            ay = a * feather(y, GREEN_FEATHER) * feather(ROW - 1 - y, GREEN_FEATHER)
            weave = math.sin(2 * math.pi * (x + y) / WEAVE_PERIOD) * WEAVE_DEPTH
            b = bright * (1 + weave + random.uniform(-GRAIN, GRAIN))
            px[x, y] = (clamp(GREEN[0] * b), clamp(GREEN[1] * b), clamp(GREEN[2] * b), clamp(255 * ay))
    return im


def menu_bar_alpha(x):
    if x <= MENU_BAR_GENTLE_FROM:
        return 1.0
    if x <= MENU_BAR_GENTLE_TO:
        t = (x - MENU_BAR_GENTLE_FROM) / (MENU_BAR_GENTLE_TO - MENU_BAR_GENTLE_FROM)
        return 1.0 + (MENU_BAR_ALPHA_AT_APPEARANCE - 1.0) * t
    t = (x - MENU_BAR_GENTLE_TO) / (MENU_BAR_W - 1 - MENU_BAR_GENTLE_TO)
    return MENU_BAR_ALPHA_AT_APPEARANCE * (1 - smoothstep(t))


def menu_bar():
    src = Image.open(MENU_BAR_SRC).convert("RGBA")
    w, h = src.size
    im = Image.new("RGBA", (MENU_BAR_W, h))
    im.paste(src, (0, 0))
    px, sp = im.load(), src.load()
    band = [y for y in range(h) if sp[MENU_BAR_TEMPLATE_X, y][3] > 0]   # rows the bar occupies
    y0, y1 = band[0], band[-1]
    for x in range(MENU_BAR_RIGHT_FRAME_X, MENU_BAR_W):                # widen with the template column
        for y in range(y0, y1 + 1):
            px[x, y] = sp[MENU_BAR_TEMPLATE_X, y]
    for x in range(MENU_BAR_W):                                        # thin it out along its length
        k = menu_bar_alpha(x)
        if k < 1.0:
            for y in range(y0, y1 + 1):
                r, g, b, a = px[x, y]
                px[x, y] = (r, g, b, clamp(a * k))
    return im


if __name__ == "__main__":
    for rows in range(1, 7):
        block(rows).save(os.path.join(OUT, "block_%d.png" % rows))
    selected().save(os.path.join(OUT, "bar_selected.png"))
    menu_bar().save(os.path.join(OUT, "menu_bar.png"))
    print("painted block_1.png to block_6.png, bar_selected.png and menu_bar.png in", os.path.normpath(OUT))
