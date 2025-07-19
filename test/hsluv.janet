(import hsluv/native :as hsluv)

(defn approx= 
  "Compares two numbers approximately by checking if their absolute difference
  is less than epsilon"
  [a b &opt epsilon]
  (default epsilon 1e-10)
  (<= (math/abs (- a b)) epsilon))

(defn approx-vec= 
  "Compares two number vectors approximately by approximately comparing number
  pairs"
  [vec1 vec2 &opt epsilon]
  (default epsilon 1e-10)
  (and (= (length vec1) (length vec2))
       (all |(approx= $0 $1 epsilon) vec1 vec2)))

(assert (approx-vec= (hsluv/rgb2hsluv 1.0 1.0 1.0) [0.0 0.0 100.0]))

(assert (approx-vec= (hsluv/rgb2hpluv 1.0 1.0 1.0) [0.0 0.0 100.0]))

(assert (approx-vec= (hsluv/hsluv2rgb ;(hsluv/rgb2hsluv 1.0 1.0 1.0)) [1 1 1]))

(assert (approx-vec= (hsluv/hpluv2rgb ;(hsluv/rgb2hpluv 1.0 1.0 1.0)) [1 1 1]))
