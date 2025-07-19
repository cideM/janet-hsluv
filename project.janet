(declare-project :name "hsluv")

(declare-source :source "source.janet"
                :prefix "hsluv/")

(declare-native :name "hsluv/native"
                :source @["cfuns.c" "hsluv.c"]
                :cflags ["-I."])
