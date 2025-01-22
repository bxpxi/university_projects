;; 14.a) Dandu-se o lista liniara se cere sa se elimine elementele din N in N.
(defun elimina_aux (lista n poz)
    (cond
        ((null lista) nil)
        ((= (mod poz n) 0) (elimina_aux (cdr lista) n (+ poz 1)))
        (t (cons (car lista) (elimina_aux (cdr lista) n (+ poz 1))))
    )
)

(defun elimina2 (lista n)
    (elimina_aux lista n 1)
)

;; 14.b)  Sa se scrie o functie care sa testeze daca o lista liniara formata din numere intregi are aspect de "vale"(o secvență se spune ; are aspect de "vale" daca elementele descresc pana la un moment dat, apoi cresc. De ex. 10 8 6 17 19 20). 

(defun are_minim_3_el (l)
	(if (or (null l) 
			(null (cdr l))
			(null (cddr l))
        )
	nil
	T)
)
    
(defun cresc(l)
	(cond 
		((null (cdr l)) T)
		((null l) nil)
		((< (car l) (cadr l)) (cresc (cdr l)))
		(T nil)
	)
)

(defun desc(l)
	(cond 
		((null (cdr l)) nil)
		((> (car l) (cadr l)) (desc (cdr l)))
		((< (car l) (cadr l)) (cresc l))
		(T nil)
	)
)

(defun vale (l) 
	(if ( and (are_minim_3_el l)
			  (> (car l) (cadr l)))
	(desc (cdr l)) ; 
	nil)
)

;; 14.c) Sa se construiasca o functie care intoarce minimul atomilor numerici dintr-o lista, de la orice nivel. 
(defun minim(l m)
	(cond 
		((null l) m)
		((and(numberp (car l)) (>= (car l) m)) (minim (cdr l) m))
		((and( numberp (car l)) (< (car l) m)) (minim (cdr l) (car l)))
		((listp (car l)) (minim (cdr l) (minim (car l) m)))
		(T (minim (cdr l) m))
))	

(defun main(l)
	(minim l 12345)
)

;; 14.d) Sa se scrie o functie care sterge dintr-o lista liniara toate aparitiile elementului maxim numeric.
(defun maxim(l m)
	(cond 
		((null l) m)
		((and(numberp (car l)) (<= (car l) m)) (maxim (cdr l) m))
		((and( numberp (car l)) (> (car l) m)) (maxim (cdr l) (car l)))
        ((listp (car l)) (maxim (cdr l) (maxim (car l) m)))
		(T (maxim (cdr l) m))
))

(defun elimina(l e)
	(cond
		((null l) nil)
		((and (numberp (car l)) (eq (car l) e)) (elimina (cdr l) e))
        ((and (numberp (car l)) (not(eq (car l) e))) (cons (car l) (elimina (cdr l) e)))
        ((listp (car l)) (cons (elimina (car l) e) (elimina (cdr l) e)))
		(T (elimina (cdr l) e))
	
    )
)

(defun main2(l)
	( elimina l ( maxim l -10000))
)