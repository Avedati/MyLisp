(set lst_1 (cons 1 2))
(assert (equal (car lst_1) 1))
(assert (equal (cdr lst_1) 2))

(set lst_2 (cons (cons 1 2) 3))
(assert (equal (car (car lst_2)) 1))
(assert (equal (cdr (car lst_2)) 2))
(assert (equal (cdr lst_2) 3))

(assert (not (equal lst_1 lst_2)))
