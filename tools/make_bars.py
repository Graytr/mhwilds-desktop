"""Paints the two option-bar images in @Resources/Images, modelled on the game's tent menu.

bar_normal.png    the dark translucent block behind an unselected option
bar_selected.png  the green bar over the selected option: a little brighter at the left,
                  a faint diagonal weave, and fading out over the right part of the bar
                  (Menu.lua draws this same image through BarTintDim for the highlight of a
                  column that does not have focus)

Both are painted at twice their on-screen size (OptionW x OptionH = 500 x 50 with
SizeMultiplier=10). Needs Pillow:  python -m pip install pillow
Change the numbers below, then run:  python tools/make_bars.py
"""
import math
import os
import random

from PIL import Image

W, H = 1000, 100
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "@Resources", "Images")

# unselected: near-black, 59% opaque
NORMAL_RGB = (12, 12, 10)
NORMAL_ALPHA = 150

# selected: the game's yellow-green
GREEN = (140, 188, 58)
PLATEAU_ALPHA = 0.92            # opacity of the solid part
FADE_START = 0.55               # where (0..1 across the bar) the fade to transparent begins
LEFT_BRIGHT, RIGHT_BRIGHT = 1.08, 0.94   # brightness at the left edge and at FADE_START
WEAVE_PERIOD, WEAVE_DEPTH = 14, 0.05     # diagonal texture: pixels per stripe, +/- brightness
GRAIN = 0.02                    # random per-pixel brightness jitter


def smoothstep(t):
    t = min(max(t, 0.0), 1.0)
    return t * t * (3 - 2 * t)


def clamp(v):
    return max(0, min(255, int(round(v))))


def normal():
    return Image.new("RGBA", (W, H), NORMAL_RGB + (NORMAL_ALPHA,))


def selected():
    random.seed(7)
    im = Image.new("RGBA", (W, H))
    px = im.load()
    for x in range(W):
        u = x / (W - 1)
        alpha = PLATEAU_ALPHA * smoothstep(x / 12.0)                  # soft left edge
        if u > FADE_START:
            alpha *= 1 - smoothstep((u - FADE_START) / (1 - FADE_START))
        bright = LEFT_BRIGHT + (RIGHT_BRIGHT - LEFT_BRIGHT) * min(u / FADE_START, 1.0)
        for y in range(H):
            weave = math.sin(2 * math.pi * (x + y) / WEAVE_PERIOD) * WEAVE_DEPTH
            b = bright * (1 + weave + random.uniform(-GRAIN, GRAIN))
            px[x, y] = (clamp(GREEN[0] * b), clamp(GREEN[1] * b), clamp(GREEN[2] * b), clamp(255 * alpha))
    return im


if __name__ == "__main__":
    normal().save(os.path.join(OUT, "bar_normal.png"))
    selected().save(os.path.join(OUT, "bar_selected.png"))
    print("painted bar_normal.png and bar_selected.png in", os.path.normpath(OUT))
