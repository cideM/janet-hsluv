# Janet wrapper around [`hsluv.c`](https://github.com/hsluv/hsluv-c)

This tiny Janet library is a simple wrapper around the official HSLuv (revision 4) C implementation. It's 100% faithful to the original and doesn't attempt to e.g., validate that inputs are within the required range (just like the C code).

## Quickstart

```shell
$ jpm install --local
$ jpm test
```

## What is HSLuv?

HSLuv is a human-friendly alternative to HSL color space. It provides perceptually uniform lightness and saturation, making it easier to create consistent color palettes. HPLuv is a variant with an even more uniform chroma distribution but a smaller gamut.

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

## Important Notes on Floating-Point Precision

Due to the complex mathematical operations involved in color space conversions (trigonometric functions, cube roots, matrix multiplications), **round-trip conversions will not produce exactly identical values**. Small floating-point errors accumulate through the conversion chain.

For example:
```janet
(hsluv/hsluv2rgb ;(hsluv/rgb2hsluv 1.0 1.0 1.0))
# Returns something like [0.9999999999999998 1.0000000000000002 0.9999999999999997]
# NOT exactly [1.0 1.0 1.0]
```

## Usage

```janet
(import hsluv)

# Convert white from RGB to HSLuv
(hsluv/rgb2hsluv 1.0 1.0 1.0)  # → [0 0 100]

# Create a red color in HSLuv and convert to RGB
(hsluv/hsluv2rgb 12.5 100 50)  # → [1.0 0.0551 0.0]

# Work with HPLuv (smaller gamut, more uniform)
(hsluv/hpluv2rgb 180 50 50)  # → [0.0 0.537 0.520]

# Check if an RGB color is within HPLuv gamut
(let [[h s l] (hsluv/rgb2hpluv 1.0 0.0 0.0)]
  (when (> s 100)
    (print "Color is outside HPLuv gamut")))
```
