(import hsluv/native :as hsluv)

(defn approx-vec=
  "Compares two number vectors approximately by approximately comparing number
  pairs"
  [vec1 vec2 &opt epsilon]
  (default epsilon 1e-10)
  (and (= (length vec1) (length vec2))
       (all |(<= (math/abs (- $0 $1)) epsilon) vec1 vec2)))

(assert (approx-vec= (hsluv/rgb2hsluv 1.0 1.0 1.0) [0.0 0.0 100.0]))

(def hpluv-white (hsluv/rgb2hpluv 1.0 1.0 1.0))
(assert (approx-vec= (slice hpluv-white 0 3) [0.0 0.0 100.0]))
(assert (= (hpluv-white 3) 0) "white should be representable in HPLuv")

(assert (approx-vec= (hsluv/hsluv2rgb ;(hsluv/rgb2hsluv 1.0 1.0 1.0)) [1 1 1]))

(assert (approx-vec= (hsluv/hpluv2rgb ;(slice hpluv-white 0 3)) [1 1 1]))

# Test a highly saturated color that's not representable in HPLuv
# Pure green (0, 1, 0) is a highly saturated color that should produce status=-1
(def hpluv-green (hsluv/rgb2hpluv 0.0 1.0 0.0))
(assert (= (hpluv-green 3) -1) "pure green should not be fully representable in HPLuv")
(assert (or (< (hpluv-green 1) 0.0) (> (hpluv-green 1) 100.0)) "saturation should be outside valid range")
