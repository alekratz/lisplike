="lib/ll"

(let foo 5)
(let bar "foobar")
(let baz (* 2 foo))
(fun factorial '(x) 
  (if 
      (== x 0)
      1
      (* x (factorial (- x 1)))
  )
)

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
(do_factorials 5)