#include <janet.h>
#include <hsluv.h>

static Janet cfun_hsluv2rgb(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);

    double h = janet_getnumber(argv, 0);
    double s = janet_getnumber(argv, 1);
    double l = janet_getnumber(argv, 2);
    
    double r, g, b;
    hsluv2rgb(h, s, l, &r, &g, &b);
    
    Janet *rgb = janet_tuple_begin(3);
    rgb[0] = janet_wrap_number(r);
    rgb[1] = janet_wrap_number(g);
    rgb[2] = janet_wrap_number(b);
    
    return janet_wrap_tuple(janet_tuple_end(rgb));
}

static Janet cfun_rgb2hsluv(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    
    double r = janet_getnumber(argv, 0);
    double g = janet_getnumber(argv, 1);
    double b = janet_getnumber(argv, 2);
    
    double h, s, l;
    rgb2hsluv(r, g, b, &h, &s, &l);
    
    Janet *hsl = janet_tuple_begin(3);
    hsl[0] = janet_wrap_number(h);
    hsl[1] = janet_wrap_number(s);
    hsl[2] = janet_wrap_number(l);
    
    return janet_wrap_tuple(janet_tuple_end(hsl));
}

static Janet cfun_hpluv2rgb(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    
    double h = janet_getnumber(argv, 0);
    double s = janet_getnumber(argv, 1);
    double l = janet_getnumber(argv, 2);
    
    double r, g, b;
    hpluv2rgb(h, s, l, &r, &g, &b);
    
    Janet *rgb = janet_tuple_begin(3);
    rgb[0] = janet_wrap_number(r);
    rgb[1] = janet_wrap_number(g);
    rgb[2] = janet_wrap_number(b);
    
    return janet_wrap_tuple(janet_tuple_end(rgb));
}

static Janet cfun_rgb2hpluv(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    
    double r = janet_getnumber(argv, 0);
    double g = janet_getnumber(argv, 1);
    double b = janet_getnumber(argv, 2);
    
    double h, s, l;
    rgb2hpluv(r, g, b, &h, &s, &l);
    
    Janet *hsl = janet_tuple_begin(3);
    hsl[0] = janet_wrap_number(h);
    hsl[1] = janet_wrap_number(s);
    hsl[2] = janet_wrap_number(l);
    
    return janet_wrap_tuple(janet_tuple_end(hsl));
}


static Janet cfun_max_chroma(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    
    double l = janet_getnumber(argv, 0);
    double h = janet_getnumber(argv, 1);
    
    return janet_wrap_number(hsluv_max_chroma_for_lh(l, h));
}

static Janet cfun_hsluv2luv(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    
    double h = janet_getnumber(argv, 0);
    double s = janet_getnumber(argv, 1);
    double l = janet_getnumber(argv, 2);
    
    double L, U, V;
    hsluv2luv(h, s, l, &L, &U, &V);
    
    Janet *luv = janet_tuple_begin(3);
    luv[0] = janet_wrap_number(L);
    luv[1] = janet_wrap_number(U);
    luv[2] = janet_wrap_number(V);
    
    return janet_wrap_tuple(janet_tuple_end(luv));
}

static Janet cfun_luv2hsluv(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    
    double L = janet_getnumber(argv, 0);
    double U = janet_getnumber(argv, 1);
    double V = janet_getnumber(argv, 2);
    
    double h, s, l;
    luv2hsluv(L, U, V, &h, &s, &l);
    
    Janet *hsl = janet_tuple_begin(3);
    hsl[0] = janet_wrap_number(h);
    hsl[1] = janet_wrap_number(s);
    hsl[2] = janet_wrap_number(l);
    
    return janet_wrap_tuple(janet_tuple_end(hsl));
}

static const JanetReg cfuns[] = {
    {"hsluv2rgb", cfun_hsluv2rgb, 
     "(hsluv/hsluv2rgb h s l)\n\nConvert HSLuv to RGB. "
     "Takes h s l (hue, saturation, lightness) components, "
     "with h between 0.0 and 360.0 and s, l between 0.0 and 100.0. "
     "Returns [r g b] tuple (red, green, blue), with values between 0.0 and 1.0"},
    {"rgb2hsluv", cfun_rgb2hsluv,
     "(hsluv/rgb2hsluv r g b)\n\nConvert RGB to HSLuv. "
     "Takes r, g, b (red, green, blue) components between 0.0 and 1.0. "
     "Returns [h s l] tuple (hue, saturation, lightness), "
     "with h between 0.0 and 360.0 and s, l between 0.0 and 100.0."},
    {"hpluv2rgb", cfun_hpluv2rgb,
     "(hsluv/hpluv2rgb h s l)\n\nConvert HPLuv to RGB. "
     "Takes h s l (hue, saturation, lightness) components, "
     "Returns [r g b] tuple (red, green, blue), with values between 0.0 and 1.0"},
    {"rgb2hpluv", cfun_rgb2hpluv,
     "(hsluv/rgb2hpluv r g b)\n\nConvert RGB to HPLuv. "
     "Note that HPLuv color space does not cover all the colors of RGB color "
     "space. More specifically, some valid RGB triplets may correspond to colors "
     "whose saturation is not representable in the HPLuv color space and falls "
     "outside the valid range between 0.0 and 100.0.\n\n"
     "Application can still get closest color correctly representable in the HPLuv "
     "color space by clamping the saturation into the valid range:\n\n"
     "(cond (< s 0.0) 0.0 (> s 100.0) 100.0 s)\n\n"
     "Takes r, g, b (red, green, blue) components between 0.0 and 1.0. "
     "Returns [h s l] tuple (hue, saturation, lightness). "
     "h is between 0.0 and 360.0. s is between 0.0 and 100.0 if the input is "
     "representable in HPLuv color space; and outside the range if it's not. "
     "l is between 0.0 and 100.0."},
    {"max-chroma", cfun_max_chroma,
     "(hsluv/max-chroma l h)\n\nGet the maximum chroma for a given lightness and hue."},
    {"hsluv2luv", cfun_hsluv2luv,
     "(hsluv/hsluv2luv h s l)\n\nConvert HSLuv to CIE LUV color space."},
    {"luv2hsluv", cfun_luv2hsluv,
     "(hsluv/luv2hsluv L U V)\n\nConvert CIE LUV to HSLuv color space."},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "hsluv", cfuns);
}
