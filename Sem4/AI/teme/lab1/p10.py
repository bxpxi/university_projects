'''
Considerându-se o matrice cu n x m elemente binare (0 sau 1) sortate crescător pe linii, să se identifice indexul liniei care conține cele mai multe elemente de 1.

De ex. în matricea
[[0,0,0,1,1],
[0,1,1,1,1],
[0,0,1,1,1]]
a doua linie conține cele mai multe elemente 1.
'''

'''
matrix - matrice de dimensiune n x m
'''

def my_function(matrix):
    """
        Gaseste linia cu suma maxima dintr-o matrice.

        Parametri:
        matrix (list of list of int): o matrice bidimensionala cu valori 1 sau 0

        Returneaza:
        int: indexul liniei cu suma maxima

        Complexitate:
        Timp: O(m * n), unde m este numărul de linii din matrice, n este numărul de coloane din matrice
    """
    sums = {}
    count = 1
    for item in matrix:
        sums[count] = sum(item)
        count+=1
    max_value = 0
    max_line = 0
    for line, count in sums.items():
        if count > max_value:
            max_value = count
            max_line = line
    return max_line

def ai_function(matrix):
    """
            Gaseste linia cu suma maxima dintr-o matrice.

            Parametri:
            matrix (list of list of int): o matrice bidimensionala cu valori 1 sau 0

            Returneaza:
            int: indexul liniei cu suma maxima

            Complexitate:
            Timp: O(m * n), unde m este numărul de linii din matrice, n este numărul de coloane din matrice
    """
    return max(range(len(matrix)), key=lambda i: sum(matrix[i])) + 1

matrix = [[0,0,0,1,1],
          [0,1,1,1,1],
          [0,0,1,1,1]]

assert my_function(matrix) == 2
assert ai_function(matrix) == 2

