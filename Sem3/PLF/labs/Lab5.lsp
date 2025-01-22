;Se da un arbore de tipul (1). Sa se afiseze calea de la radacina pana la un nod x dat.

(defun parcurg_st (l nrNoduri nrMuchii)
  (cond
    ((null l) nil)
    ((= nrNoduri ( + 1 nrMuchii)) nil)
    (t (cons (car l) (cons (cadr l) (parcurg_st (cddr l) (+ 1 nrNoduri) (+ (cadr l) nrMuchii)))))
  )
)

(defun parcurg_dr (l nrNoduri nrMuchii)
  (cond
    ((null l) nil)
    ((= nrNoduri (+ 1 nrMuchii)) l)
    (t (parcurg_dr (cddr l) (+ 1 nrNoduri) (+ (cadr l) nrMuchii)))
  )
)

(defun stang(l)
  (parcurg_st (cddr l) 0 0)
)

(defun drept(l)
  (parcurg_dr (cddr l) 0 0)
)

(defun checkExistence(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) t)
    (t (checkExistence (cdr l) elem))
  )
)

(defun checkExistenceLeft(l elem)
  (checkExistence (stang l) elem)
)

(defun checkExistenceRight(l elem)
  (checkExistence (drept l) elem)
)

(defun path(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) (list elem))
    ((checkExistenceRight l elem) (cons (car l) (path (drept l) elem)))
    ((checkExistenceLeft l elem) (cons (car l) (path (stang l) elem)))
  )
)