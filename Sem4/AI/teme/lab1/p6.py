'''
Pentru un șir cu n numere întregi care conține și duplicate, să se determine elementul majoritar (care apare de mai mult de n / 2 ori).
De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].
'''

def my_function(array):
    """
        Gaseste elementul care apare mai mult de jumatate din timp intr-o lista.

        Parametri:
        array (list): o lista de elemente, unde elementele pot fi de orice tip

        Returneaza:
        element: elementul care apare mai mult de jumatate din timp, daca exista
                 daca nu exista un astfel de element, returneaza None

        Complexitate:
        O(n), unde n este numărul de elemente din lista
    """
    counts = {}
    n = len(array)

    for item in array:
        counts[item] = counts.get(item, 0) + 1

    for item, count in counts.items():
        if count > n/2:
            return item

    return None

def ai_function(array):
    """
            Gaseste elementul care apare mai mult de jumatate din timp intr-o lista.

            Parametri:
            array (list): o lista de elemente, unde elementele pot fi de orice tip

            Returneaza:
            element: elementul care apare mai mult de jumatate din timp, daca exista
                     daca nu exista un astfel de element, returneaza None

            Complexitate:
            O(n log n), unde n este numărul de elemente din lista
        """
    array.sort()
    n = len(array)
    count = 1

    for i in range(1, n):
        if array[i] == array[i - 1]:
            count += 1
        else:
            count = 1

        if count > n // 2:
            return array[i]

    return None

array = [2,8,7,2,2,5,2,3,1,2,2]

assert my_function(array) == 2
assert ai_function(array) == 2