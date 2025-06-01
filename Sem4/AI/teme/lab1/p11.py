'''
Considerându-se o matrice cu n x m elemente binare (0 sau 1), să se înlocuiască cu 1 toate aparițiile elementelor egale cu 0 care sunt complet înconjurate de 1.

De ex. matricea
[[1,1,1,1,0,0,1,1,0,1],
[1,0,0,1,1,0,1,1,1,1],
[1,0,0,1,1,1,1,1,1,1],
[1,1,1,1,0,0,1,1,0,1],
[1,0,0,1,1,0,1,1,0,0],
[1,1,0,1,1,0,0,1,0,1],
[1,1,1,0,1,0,1,0,0,1],
[1,1,1,0,1,1,1,1,1,1]]
*devine *
[[1,1,1,1,0,0,1,1,0,1],
[1,1,1,1,1,0,1,1,1,1],
[1,1,1,1,1,1,1,1,1,1],
[1,1,1,1,1,1,1,1,0,1],
[1,1,1,1,1,1,1,1,0,0],
[1,1,1,1,1,1,1,1,0,1],
[1,1,1,0,1,1,1,0,0,1],
[1,1,1,0,1,1,1,1,1,1]]
'''

from collections import deque


def my_function(matrix):
    """
    Modifica matricea astfel incat toate valorile 0, care nu sunt pe margine, sa devina 1,
    iar valorile 0 de pe margine sa ramana neschimbate.

    Parametri:
    matrix (list of list of int): o matrice cu valori 0 si 1

    Returneaza:
    list of list of int: Matricea modificata

    Complexiate:
    O(m * n), unde m este numărul de linii din matrice, n este numărul de coloane din matrice.
    """


    rows, cols = len(matrix), len(matrix[0])


    def mark_border_zeros(x, y):
        if 0 <= x < rows and 0 <= y < cols and matrix[x][y] == 0:
            matrix[x][y] = -1
            mark_border_zeros(x + 1, y)
            mark_border_zeros(x - 1, y)
            mark_border_zeros(x, y + 1)
            mark_border_zeros(x, y - 1)


    for i in range(rows):
        mark_border_zeros(i, 0)
        mark_border_zeros(i, cols - 1)
    for j in range(cols):
        mark_border_zeros(0, j)
        mark_border_zeros(rows - 1, j)

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 0:
                matrix[i][j] = 1

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == -1:
                matrix[i][j] = 0

    return matrix

def ai_function(matrix):
    """
        Modifica matricea astfel incat toate valorile 0, care nu sunt pe margine, sa devina 1,
        iar valorile 0 de pe margine sa ramana neschimbate.

        Parametri:
        matrix (list of list of int): o matrice cu valori 0 si 1

        Returneaza:
        list of list of int: Matricea modificata

        Complexiate:
        O(m * n), unde m este numărul de linii din matrice, n este numărul de coloane din matrice.
    """
    rows, cols = len(matrix), len(matrix[0])
    queue = deque()

    for i in range(rows):
        for j in [0, cols - 1]:
            if matrix[i][j] == 0:
                queue.append((i, j))

    for j in range(cols):
        for i in [0, rows - 1]:
            if matrix[i][j] == 0:
                queue.append((i, j))

    while queue:
        x, y = queue.popleft()
        if matrix[x][y] == 0:
            matrix[x][y] = -1
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < rows and 0 <= ny < cols and matrix[nx][ny] == 0:
                    queue.append((nx, ny))

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 0:
                matrix[i][j] = 1

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == -1:
                matrix[i][j] = 0

    return matrix


matrix = [[1,1,1,1,0,0,1,1,0,1],
[1,0,0,1,1,0,1,1,1,1],
[1,0,0,1,1,1,1,1,1,1],
[1,1,1,1,0,0,1,1,0,1],
[1,0,0,1,1,0,1,1,0,0],
[1,1,0,1,1,0,0,1,0,1],
[1,1,1,0,1,0,1,0,0,1],
[1,1,1,0,1,1,1,1,1,1]]

assert my_function(matrix) == [[1, 1, 1, 1, 0, 0, 1, 1, 0, 1], [1, 1, 1, 1, 1, 0, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 0, 1], [1, 1, 1, 1, 1, 1, 1, 1, 0, 0], [1, 1, 1, 1, 1, 1, 1, 1, 0, 1], [1, 1, 1, 0, 1, 1, 1, 0, 0, 1], [1, 1, 1, 0, 1, 1, 1, 1, 1, 1]]
assert ai_function(matrix) == [[1, 1, 1, 1, 0, 0, 1, 1, 0, 1], [1, 1, 1, 1, 1, 0, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 0, 1], [1, 1, 1, 1, 1, 1, 1, 1, 0, 0], [1, 1, 1, 1, 1, 1, 1, 1, 0, 1], [1, 1, 1, 0, 1, 1, 1, 0, 0, 1], [1, 1, 1, 0, 1, 1, 1, 1, 1, 1]]