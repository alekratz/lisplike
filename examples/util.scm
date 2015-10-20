="ll"

(fun get_yn '(prompt)
    (
        (let ans (readln (fmt "% [y/n] " prompt)))
        (if (== ans "y")
            "y"
        (if (== ans "yes")
            "y"
        (if (== ans "n")
            "n"
        (if (== ans "no")
            "n"
        (
            (println "please enter yes or no")
            (get_yn prompt)
        )))))
    )
)