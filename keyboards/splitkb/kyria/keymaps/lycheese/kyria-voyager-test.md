# Kyria gaming layer: Voyager simulation test

## Goal
Change the **gaming layer** (`_GAME` in `keymap.c`) so it only uses keys a ZSA Voyager has, especially just **two thumb keys** per side, to find out whether FFXIV-style key-heavy play works with that restriction before buying a Voyager.

Don't change the base layer (Bone with home row mods, implemented in firmware), the Miryoku layers (`_NUM`, `_SYM`, `_FUN`, `_NAV`, `_MEDIA`, `_SYMR`), or the gaming toggle `TG(_GAME)` on the **left** inner extra key above the thumb row.

Keycodes are plain QWERTY keycodes (Bone is done in firmware), so no OS-layout translation is needed.

## Current state (from the repo)

Gaming layer, left hand. Main block shifted one column right so W is on the middle-finger column; the former rightmost column wraps to the outer column:

```
T   Esc    Q   W   E   R
G   Shift  A   S   D   F
B   Tab    Z   X   C   V
```

Thumb keys, outer → inner: `LM(_NUM, MOD_LCTL|MOD_LALT)`, `LM(_NUM, MOD_LALT)`, `LM(_NUM, MOD_LCTL)`, `MO(_NUM)`, `KC_SPC`.

The hotbar layer is the shared Miryoku `_NUM` layer (left hand):

```
'   [   7   8   9   ]
/   ;   4   5   6   =
.   `   1   2   3   \
thumbs: .  0  -  .     (keys 2–4)
```

Consequences:
- 0 and - sit on thumb keys 3 and 4, unreachable while the thumb holds HB on key 4.
- `_NUM` covers the pinky column (`[ ; ``), so pinky Shift + HB doesn't work.

Bug found: in `_GAME`, right half home row, the L position sends `KC_I` instead of `KC_L` (the comment block also shows `o` twice in the top row).

## Changes for the test

### New `_HB` layer (gaming only)
Don't reuse `_NUM`; add a dedicated `_HB` layer so the Miryoku number layer stays untouched.

```
MENU      Alt*   7   8   9   -
Ctrl+Alt* Shift  4   5   6   0
.         Ctrl*  1   2   3   =
```

`*` = latch modifier (see below). `MENU` = `OSL(_MENU)`. Right half and unlisted keys `KC_NO` (or transparent where harmless).

### Latch modifiers
On `_HB`, the pinky keys Alt / Ctrl and the outer-column Ctrl+Alt are custom keycodes that **latch** a modifier while `_HB` is active:
- Tap → the modifier is registered and stays active for all following hotbar presses.
- Tapping a different latch key replaces the current one; tapping the same one again clears it (back to the plain bar).
- Releasing HB (layer `_HB` turns off) clears all latched modifiers. Implement via `layer_state_set_user()`.
- Shift on the home row stays a normal held `KC_LSFT` (it is the common one, used for targeting allies as a healer); optionally also latchable.

### Thumb keys: only 2
- 4th thumb key (counted from outside): `MO(_HB)`
- 5th (innermost): `KC_SPC`
- Outer three: `KC_NO` on `_GAME`

Esc and Tab stay where they are on `_GAME`.

### `_MENU` layer (one-shot)
Sends the right-hand letters from the left hand, finger by finger, so FFXIV menus are reachable without leaving the mouse:

```
Esc  P   O   I   U   Y
.    ;   L   K   J   H
.    /   .   ,   M   N
```

### Fix
`KC_I` → `KC_L` at the right-hand L position in `_GAME`; fix the `_GAME` comment block.

## Constraints
- `_GAME` within the 3×6 main grid + 2 thumb keys per side (the Voyager additionally has a number row, so the test is slightly stricter than reality).
- Don't change base or Miryoku layers.
- Compile (`qmk compile -kb splitkb/kyria/rev1 -km lycheese`, check the actual revision) and say how to flash; don't flash automatically.
