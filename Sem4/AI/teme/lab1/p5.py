'''
Pentru un șir cu n elemente care conține valori din mulțimea {1, 2, ..., n - 1} astfel încât o singură valoare se repetă de două ori, să se identifice acea valoare care se repetă.
De ex. în șirul [1,2,3,4,2] valoarea 2 apare de două ori.
'''

def my_function(array):
    """
        Gaseste elementul care se repeta intr-o lista.

        Parametri:
        array (list): o lista de elemente, unde elementele pot fi de orice tip

        Returneaza:
        element: elementul care se repeta in lista

        Complexitate:
        O(n), unde n este numarul de elemente din lista
    """
    counts = {}

    for item in array:
        if counts.get(item):
            return item
        counts[item] = 1

    return array[-1]

def ai_function(array):
    '''
        Gaseste elementul care se repeta intr-o lista.

        Parametri:
        array (list): o lista de elemente, unde elementele pot fi de orice tip

        Returneaza:
        element: elementul care se repeta in lista

        Complexiatate:
        O(n log n), deoarece sortarea listei are complexitatea O(n log n), iar parcurgerea listei sortate are complexitatea O(n)
    '''
    array.sort()

    for i in range(1, len(array)):
        if array[i] == array[i-1]:
            return array[i]


array = [1,2,3,4,2]

assert my_function(array) == 2
assert ai_function(array) == 2
