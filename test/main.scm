=inc
"test"
=

(fun do_factorials '(n) 
    (if (> n 0) 
        ;(
        ;    (printf "%d: %d\n" n (factorial n))
            (do_factorials (- n 1))
            0
        ;)
    )
)

(print "%\n" (factorial 5))