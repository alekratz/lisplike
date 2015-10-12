(fun factorial (x) (
    if (== x 0) '(
      1
      (factorial (- x 1))
    )
  )
)

