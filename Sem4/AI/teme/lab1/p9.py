'''
Considerându-se o matrice cu n x m elemente întregi și o listă cu perechi formate din coordonatele a 2 căsuțe din matrice ((p,q) și (r,s)), să se calculeze suma elementelor din sub-matricile identificate de fieare pereche.

De ex, pt matricea
[[0, 2, 5, 4, 1],
[4, 8, 2, 3, 7],
[6, 3, 4, 6, 2],
[7, 3, 1, 8, 3],
[1, 5, 7, 9, 4]]
și lista de perechi ((1, 1) și (3, 3)), ((2, 2) și (4, 4)), suma elementelor din prima sub-matrice este 38, iar suma elementelor din a 2-a sub-matrice este 44.
'''

def my_function(matrix, array):
    """
        Calculeaza suma elementelor din matrice pentru submatrici definite de perechile de colturi.

        Parametri:
        matrix (list of list of int): o matrice bidimensionala cu valori intregi
        array (list of tuple): o lista de tupluri, fiecare tuplu avand doua perechi de coordonate care definesc colturi opuse ale submatricii

        Returneaza:
        list of int: O lista cu sumele elementelor pentru fiecare submatrice definita de coordonatele din 'array'

        Complexitate:
        O(k * m * n), unde k este numărul de perechi de coordonate din array, m și n sunt dimensiunile submatricei (numărul de rânduri și coloane între colțurile corner1 și corner2).
    """
    sums = []
    for item in array:
        corner1 = item[0]
        corner2 = item[1]
        sum = 0
        for i in range(corner1[0], corner2[0]+1):
            for j in range(corner1[1], corner2[1]+1):
                sum += matrix[i][j]
        sums.append(sum)
    return sums

def ai_function(matrix, array):
    """
            Calculeaza suma elementelor din matrice pentru submatrici definite de perechile de colturi.

            Parametri:
            matrix (list of list of int): o matrice bidimensionala cu valori intregi
            array (list of tuple): o lista de tupluri, fiecare tuplu avand doua perechi de coordonate care definesc colturi opuse ale submatricii

            Returneaza:
            list of int: O lista cu sumele elementelor pentru fiecare submatrice definita de coordonatele din 'array'

            Complexitate:
            O(k * m * n), unde k este numărul de perechi de coordonate din array, m și n sunt dimensiunile submatricei (numărul de rânduri și coloane între colțurile corner1 și corner2).
    """
    sums = []
    for (p, q), (r, s) in array:
        total = sum(matrix[i][j] for i in range(p, r + 1) for j in range(q, s + 1))
        sums.append(total)
    return sums

matrix = [[0, 2, 5, 4, 1],
          [4, 8, 2, 3, 7],
          [6, 3, 4, 6, 2],
          [7, 3, 1, 8, 3],
          [1, 5, 7, 9, 4]]
array = ((1, 1),(3, 3)), ((2, 2), (4, 4))

assert my_function(matrix,array) == [38, 44]
assert ai_function(matrix,array) == [38, 44]