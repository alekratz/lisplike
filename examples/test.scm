=inc
"ll"
"factorial"
=

(fun do_factorials '(n) 
    (if (> n 0) 
        (
            (print "%: %\n" n (factorial n))
            (do_factorials (- n 1))
        )
        none
    )
)

;(print "%\n" (factorial 5))
(print "testing factorials\n")
(do_factorials 5)
(print "testing fizzbuzz\n")
(fizzbuzz 20)