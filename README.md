# Janet wrapper around [`hsluv.c`](https://github.com/hsluv/hsluv-c)

This tiny Janet library is a simple wrapper around the official HSLuv (revision
4) C implementation. It's 100% faithful to the original and doesn't attempt to
e.g., validate that inputs are within the required range (just like the C
code).

The library has 4 functions:

- `hsluv2rgb`
- `rgb2hsluv`
- `hpluv2rgb`
- `rgb2hpluv`

Please see the doc strings for details.

## Quickstart

```shell
$ jpm install --local
$ jpm test
```
