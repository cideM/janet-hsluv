(import hsluv/native :prefix "" :export true)

(defn blend-hsluv
  ```
  Blend two HSLuv colors in LUV color space through linear interpolation.
  
  Takes two HSLuv colors as [h s l] tuples and a blend factor t (0.0 to 1.0).
  When t=0, returns color1; when t=1, returns color2.
  
  Example:
    (blend-hsluv [0 100 50] [120 100 50] 0.5)  # Blend red and green
  ```
  [color1 color2 t]
  (let [[h1 s1 l1] color1
        [h2 s2 l2] color2
        # Convert both colors to LUV
        [L1 U1 V1] (hsluv2luv h1 s1 l1)
        [L2 U2 V2] (hsluv2luv h2 s2 l2)
        # Linear interpolation in LUV space
        L (+ (* L1 (- 1 t)) (* L2 t))
        U (+ (* U1 (- 1 t)) (* U2 t))
        V (+ (* V1 (- 1 t)) (* V2 t))]
    # Convert back to HSLuv
    (luv2hsluv L U V)))
