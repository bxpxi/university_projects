'''
Să se determine cuvintele unui text care apar exact o singură dată în acel text.
De ex. cuvintele care apar o singură dată în ”ana are ana are mere rosii ana" sunt: 'mere' și 'rosii'.
'''

def my_function(text):
    """
        Gaseste si returneaza cuvintele care apar o singura data intr-un text.

        Parametri:
        text (str): un sir de caractere care reprezinta textul de procesat

        Returneaza:
        list of str: o lista cu cuvintele care apar o singura data in text

        Complexitate:
        O(n^2) - deoarece pentru fiecare cuvant din text se calculeaza words.count(item), ceea ce necesita o parcurgere completa a listei
    """
    words = text.split()
    return [item for item in words if words.count(item) == 1]

def ai_function(text):
    """
            Găsește și returnează cuvintele care apar o singură dată într-un text.

            Parametri:
            text (str): Un șir de caractere care reprezintă textul de procesat.

            Returnează:
            list of str: O listă cu cuvintele care apar o singură dată în text.

            Complexitate:
            O(n) - se foloseste un dictionar pentru numararea aparitiilor fiecarui cuvant
    """
    words = text.split()
    words_count = {}

    for word in words:
        words_count[word] = words_count.get(word, 0) + 1

    return [word for word, count in words_count.items() if count == 1]


text = "ana are ana are mere rosii ana"

assert my_function(text) == ['mere', 'rosii']
assert ai_function(text) == ['mere', 'rosii']
