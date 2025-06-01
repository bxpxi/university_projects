'''
Să se determine ultimul (din punct de vedere alfabetic) cuvânt care poate apărea într-un text care conține mai multe cuvinte separate prin ” ” (spațiu).
De ex. ultimul (dpdv alfabetic) cuvânt din ”Ana are mere rosii si galbene” este cuvântul "si".
'''

def my_function(text):
    """
        Gaseste cuvantul care este cel mai mare (alfabetic) dintr-un text.

        Parametri:
        text (str): un sir de caractere care reprezinta textul de procesat

        Returneaza:
        str: cuvantul cel mai mare (alfabetic) din text

        Complexitate:
        O(n) - unde n este numarul de cuvinte din text, deoarece functia max parcurge lista o singura data.
    """
    words = text.split()
    last_word = max(words)
    return last_word

def ai_function(text):
    """
        Gaseste cuvantul care este cel mai mare (alfabetic) dintr-un text, folosind sortare.

        Parametri:
        text (str): un sir de caractere care reprezinta textul de procesat

        Returneaza:
        str: cuvantul cel mai mare (alfabetic) din text

        Complexitate:
        O(n log n) - deoarece functia sorted sorteaza intreaga lista, ceea ce este mai costisitor decat max.
    """
    return sorted(text.split())[-1]


text = "Ana are mere rosii si galbene"
assert my_function(text) == "si"
assert ai_function(text) == "si"
