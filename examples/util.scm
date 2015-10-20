="ll"

(fun get_yn '(prompt)
    (
        (let ans (readln (fmt "% [y/n] " prompt)))
        (if (== ans "y")
            1
        (if (== ans "yes")
            1
        (if (== ans "n")
            0
        (if (== ans "no")
            0
        (
            (println "please enter yes or no")
            (get_yn prompt)
        )))))
    )
)