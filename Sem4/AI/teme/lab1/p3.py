'''
Să se determine produsul scalar a doi vectori rari care conțin numere reale.
Un vector este rar atunci când conține multe elemente nule. Vectorii pot avea oricâte dimensiuni.
De ex. produsul scalar a 2 vectori unisimensionali [1,0,2,0,3] și [1,2,0,3,1] este 4.
'''

def my_function(array1, array2):
    """
        Calculeaza produsul scalar al doua vectori rari, suportand si structuri de date imbricate (liste in liste).

        Parametri:
        array1 (list): primul vector rar (sau lista de vectori)
        array2 (list): al doilea vector rar (sau lista de vectori)

        Returneaza:
        int: produsul scalar al celor doi vectori rari

        Arunca:
        ValueError: daca cei doi vectori nu au aceeasi dimensiune

        Complexitate:
        O(n + k) - unde n este numarul de elemente non-zero, iar k este numarul elementelor din liste imbricate
    """
    len1 = len(array1)
    len2 = len(array2)
    result = 0
    i = 0

    if len1 != len2:
        raise ValueError("Vectorii trebuie sa aiba aceeasi dimensiune.")

    while i < len1:
        if isinstance(array1[i],list) and isinstance(array2[i],list):
            result += my_function(array1[i], array2[i])
        elif isinstance(array1[i],list):
            for item in array1[i]:
                result += item * array2[i]
        elif isinstance(array2[i],list):
            for item in array2[i]:
                result += item * array1[i]
        elif array1[i] != 0 and array2[i] != 0:
            result += array1[i] * array2[i]
        i += 1
    return result

def ai_function(array1, array2):
    """
            Calculeaza produsul scalar al doi vectori rari, folosind recursivitate.

            Parametri:
            array1 (list): primul vector rar (sau lista de vectori)
            array2 (list): al doilea vector rar (sau lista de vectori)

            Returneaza:
            int: produsul scalar al celor doi vectori rari

            Complexitate:
            O(n + k) - unde n este numarul de elemente non-zero, iar k este numarul elementelor din liste imbricate
    """
    if isinstance(array1, list) and isinstance(array2, list):
        return sum(ai_function(x, y) for x, y in zip(array1, array2))

    if isinstance(array1, list):
        return sum(ai_function(x, array2) for x in array1)
    if isinstance(array2, list):
        return sum(ai_function(array1, y) for y in array2)

    return array1 * array2 if array1 and array2 else 0


array1 = [1,0,2,0,3]
array2 = [1,2,0,3,1]

array3 = [[1, 0, 2],[0, 3, 0],3]
array4 = [2,[1, 2, 0],[3, 1, 0]]

assert my_function(array1,array2) == 4
assert my_function(array3,array4) == 24

assert ai_function(array1,array2) == 4
assert ai_function(array3,array4) == 24
