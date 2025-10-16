# Janet wrapper around [`hsluv.c`](https://github.com/hsluv/hsluv-c)

This tiny Janet library is a simple wrapper around the official HSLuv (revision 4) C implementation. It tries to be 100% faithful to the original and doesn't attempt to e.g., validate that inputs are within the required range (just like the C code).

## Usage

```shell
$ jpm install https://github.com/cideM/janet-hsluv.git
```

```janet
(import hsluv)

(hsluv/rgb2hsluv 1.0 1.0 1.0)  # → [0 0 100]
```

## Functions

### `hsluv2rgb`
Converts HSLuv color values to RGB.
- **Parameters**: `h` (hue: 0-360°), `s` (saturation: 0-100), `l` (lightness: 0-100)
- **Returns**: Tuple of `[r, g, b]` where each component is 0.0-1.0

### `rgb2hsluv`
Converts RGB color values to HSLuv.
- **Parameters**: `r`, `g`, `b` (each 0.0-1.0)
- **Returns**: Tuple of `[h, s, l]` where h is 0-360°, s and l are 0-100

### `hpluv2rgb`
Converts HPLuv color values to RGB. HPLuv is a variant with more uniform chroma.
- **Parameters**: `h` (hue: 0-360°), `s` (saturation: 0-100), `l` (lightness: 0-100)
- **Returns**: Tuple of `[r, g, b]` where each component is 0.0-1.0

### `rgb2hpluv`
Converts RGB color values to HPLuv.
- **Parameters**: `r`, `g`, `b` (each 0.0-1.0)
- **Returns**: Tuple of `[h, s, l]` where h is 0-360°, s is 0-100 (may exceed if color is outside HPLuv gamut), l is 0-100
- **Note**: Some RGB colors fall outside the HPLuv gamut. The saturation value may exceed 100 in these cases. The C function returns a status code, but this wrapper simply returns the values as-is.

## Quirks, Caveats, and Gotchas

It's normal for small floating point precision errors to accumulate when chaining function calls. For example:

```janet
(hsluv/hsluv2rgb ;(hsluv/rgb2hsluv 1.0 1.0 1.0))
# Returns something like [0.9999999999999998 1.0000000000000002 0.9999999999999997]
# NOT exactly [1.0 1.0 1.0]
```

## What is HSLuv?

HSLuv is a human-friendly alternative to HSL color space. It provides perceptually uniform lightness and saturation, making it easier to create consistent color palettes. HPLuv is a variant with an even more uniform chroma distribution but a smaller gamut.

