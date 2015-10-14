(let foo 5)
(let bar "foobar")
(let baz yep)
(fun factorial '(x) 
  (if 
      (== x 0)
      1
      (* x (factorial (- x 1)))
  )
)

