'''
Să se determine al k-lea cel mai mare element al unui șir de numere cu n elemente (k < n).
De ex. al 2-lea cel mai mare element din șirul [7,4,6,3,9,1] este 7.
'''


def my_function(array, k):
    """
    Gaseste al k-lea cel mai mare element dintr-o lista.

    Parametri:
    array (list of int): o lista de numere intregi
    k (int): pozitia elementului cautat, numar intreg pozitiv

    Returneaza:
    int: al k-lea cel mai mare element din lista.

    Complexitate:
    O(n log n), unde n este numărul de elemente din lista
    """
    return sorted(array)[-k]

def ai_function(array, k):
    """
        Gaseste al k-lea cel mai mare element dintr-o lista.

        Parametri:
        array (list of int): o lista de numere intregi
        k (int): pozitia elementului cautat, numar intreg pozitiv

        Returneaza:
        int: al k-lea cel mai mare element din lista.

        Complexitate:
        O(n log n), unde n este numărul de elemente din lista
    """
    unique_elements = set(array)
    sorted_elements = sorted(unique_elements, reverse=True)
    return sorted_elements[k - 1]

k = 2
array = [7,4,6,3,9,1]

assert my_function(array, k) == 7
assert ai_function(array, k) == 7