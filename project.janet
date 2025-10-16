(declare-project :name "hsluv")

(declare-source :source "source.janet"
                )

(declare-native :name "hsluv/native"
                :source @["cfuns.c" "hsluv.c"]
                :cflags ["-I."])
