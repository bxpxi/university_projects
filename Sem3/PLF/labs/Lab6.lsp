;5.  Definiti o functie care testeaza apartenenta unui nod intr-un arbore n-ar reprezentat sub forma ;(radacinalista_noduri_subarb1...lista_noduri__subarbn) Ex: arborelele este (a (b (c)) (d) (e (f))) si nodul este 'b => adevarat

(defun verifica(l elem)
    (cond
        ((and (atom l) (equal l elem)) t)
        ((atom l) nil)
        (t (verifica2 (mapcar #'(lambda (a) (verifica a elem)) l)))
    )
)

(defun verifica2 (l)
    (cond
        ((null l) nil)
        ((car l) t)
        (t (verifica2 (cdr l)))
    )
)