'''
Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n.
De ex. dacă n = 4, numerele sunt: 1, 10, 11, 100.
'''

def my_function(n):
    """
        Genereaza o lista de numere in sistem binar de la 1 la n.

        Parametri:
        n (int): un numar intreg care reprezinta limita superioara a intervalului

        Returneaza:
        list of str: o lista de siruri de caractere care reprezinta numerele de la 1 la n in sistem binar

        Complexitate:
        O(n log n), unde n este numărul de elemente generate
    """
    result = []
    for i in range(1, n+1):
        result.append(bin(i).replace("0b", ""))
    return result

def ai_function(n):
    """
            Genereaza o lista de numere in sistem binar de la 1 la n.

            Parametri:
            n (int): un numar intreg care reprezinta limita superioara a intervalului

            Returneaza:
            list of str: o lista de siruri de caractere care reprezinta numerele de la 1 la n in sistem binar

            Complexitate:
            O(n log n), unde n este numărul de elemente generate
    """
    return [format(i, 'b') for i in range(1, n + 1)]

n = 4
assert my_function(n) == ['1', '10', '11', '100']
assert ai_function(n) == ['1', '10', '11', '100']