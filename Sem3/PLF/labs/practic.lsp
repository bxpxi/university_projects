(defun vale (l flag)
    (cond
        ((and (null (cadr l))(eq flag 1)) t)
        ((and (null (cadr l))(eq flag 0)) nil)
        ((and (> (car l) (cadr l)) (eq flag 0)) (vale (cdr l) 0))
        ((< (car l) (cadr l))(vale (cdr l) 1))
        ;((and (< (car l) (cadr l)) (eq flag 1)) (vale (cdr l) 1))
        (t nil)
    )
)

(defun liniarizare (l)
    (cond
        ((null l) nil)
        ((numberp (car l)) (cons (car l) (liniarizare (cdr l))))
        (t (liniarizare (cdr l)))
    )
)

(defun vale_main (l)
    (cond
        ((null l) nil)
        ((null (cadr l)) nil)
        ((null (caddr l)) nil)
        ((> (car l)(cadr l)) (vale (cdr l) 0))
        (t nil)
    )
)

(defun main (l)
    (vale_main (liniarizare l))
)

;;(main '(A B C 10 D 8 E 6 17 19 20)) => T
;;(main '(A B C 10 D 8 E 6 17 19 7))  => NIL
;;(main '(A B C 10 D 8 E 6 17 19 5 10)) => NIL

;;(vale_main '(10 8 6 17 19 20)) => T
;;(vale_main '(10 8 6 17 19 20 7)) => NIL
;;(vale_main '(10 8 6 17 19 20 5 10)) => NIL

;;(liniarizare '(A B C 10 D 8 E 6 17 19 20)) => (10 8 6 17 19 20)
;;(liniarizare '(A B B B B C 10 D 8 E 6 17 19 20)) => (10 8 6 17 19 20)
;;(liniarizare '(A B C 10 D 8 E 6 17 19 P P P 20)) => (10 8 6 17 19 20)

;;(vale '(10 8 6 17 19 20) 0) => T
;;(vale '(10 8 6 17 19 20 7) 0) => NIL
;;(vale '(10 8 6 17 19 20 7 10) 0) => NIL




