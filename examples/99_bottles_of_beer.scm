="ll"

(fun bottles '(x)
    (if (<= x 0)
        (println "No more bottles of beer on the wall")
    (
        (println "% bottles of beer on the wall, % bottles of beer, take one down, pass it around, % bottles of beer on the wall" x x (- x 1))
        (bottles (- x 1))
    ))
)