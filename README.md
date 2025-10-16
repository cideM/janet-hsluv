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

- RGB triplets are always ranges from 0.0 to 1.0
- HSL triplets are `h` (hue: 0-360°), `s` (saturation: 0-100), `l` (lightness: 0-100)
- LUV triplets are `l` (lightness: 0-100) and then a `u` (red-green)/`v` (yellow-blue) pair, which are both unbounded and can be negative and positive but are typically between -100 and +100

- `hsluv2rgb`: HSLuv -> RGB
- `rgb2hsluv`: RGB -> HSLuv
- `hpluv2rgb`: HPLuv -> RGB (HPLuv is a variant with more uniform chroma)
- `rgb2hpluv`: RGB -> HPLuv (returns a tuple with `[h,s,l,status]`, where status indicates whether the saturation is outside the HPLuv gamut)
- `hsluv2luv`: HSLuv -> Luv
- `luv2hsluv`: Luv -> HSLuv

## Quirks, Caveats, and Gotchas

It's normal for small floating point precision errors to accumulate when chaining function calls. For example:

```janet
(hsluv/hsluv2rgb ;(hsluv/rgb2hsluv 1.0 1.0 1.0))
# Returns something like [0.9999999999999998 1.0000000000000002 0.9999999999999997]
# NOT exactly [1.0 1.0 1.0]
```

## What is HSLuv?

HSLuv is a human-friendly alternative to HSL color space. It provides perceptually uniform lightness and saturation, making it easier to create consistent color palettes. HPLuv is a variant with an even more uniform chroma distribution but a smaller gamut.
