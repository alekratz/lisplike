=inc
"ll"
"factorial"
"fizzbuzz"
=

(fun do_factorials '(n) 
    (if (> n 0) 
        (
            (println "%: %" n (factorial n))
            (do_factorials (- n 1))
        )
        none
    )
)

;(print "%\n" (factorial 5))
(println "testing factorials")
(do_factorials 5)
(println "testing fizzbuzz")
(fizzbuzz 20)
(println "testing sequences")
(println "%" (seq 1 2 0.1))
(println "%" (seq 2 1 -0.1))
(let demo_array '("here" "is" "an" "array" "of" "mixed" "types" 1 2 3 4 5))
(println "demo array:")
(println "%" demo_array)
(letm mvar "This is a mutable variable")
(println "%" mvar)
(set mvar "And now it has a different value")
(println "%" mvar)