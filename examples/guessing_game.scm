="ll"


(fun ask_q '(tree) (
        (println "does your animal have %? y/n" tree.trait)
        (let ans (readln "> "))
        (if (== ans "y")
            ; check if right side is none; if so, guess that as the animal
            (if (isnone tree.right)
                (println "I guess that your animal is the %" tree.animal)
                (ask_q tree.right)
            )
        ; else if
        (if (== ans "n")
            (if (isnone tree.left)
                (println "I guess that your animal is the %" tree.animal)
                (ask_q tree.left)
            )
        ; else
        (
            (println "Please enter 'y' or 'n'")
            (ask_q tree)
        )))
    )
)

(fun start_game
)