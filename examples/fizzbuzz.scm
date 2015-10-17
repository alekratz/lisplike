="ll"

(fun fizzbuzz '(n)
    (if (> n 0)
        (
            (print "%: " n)
            (if (== 0 (% n 3))
                (print "fizz")
                none
            )
            (if (== 0 (% n 5))
                (print "buzz")
                none
            )
            (print "\n")
            (fizzbuzz (- n 1))
        )
        none
    )
)