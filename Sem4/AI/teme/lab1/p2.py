'''
Să se determine distanța Euclideană între două locații identificate prin perechi de numere.
De ex. distanța între (1,5) și (4,1) este 5.0
'''
import math


def my_function(point1, point2):
    """
        Calculeaza distanta euclidiana intre doua puncte in plan.

        Parametri:
        point1 (tuple): primul punct (x1, y1) reprezentat ca un tuplu de doua valori
        point2 (tuple): al doilea punct (x2, y2) reprezentat ca un tuplu de doua valori

        Returneaza:
        float: distanta euclidiana dintre cele doua puncte

        Complexitate:
        O(1) - deoarece realizeaza un numar fix de operatii matematice
    """
    return math.sqrt((point2[1]-point1[1])**2 + (point2[0]-point1[0])**2)

def ai_function(point1, point2):
    """
            Calculeaza distanta euclidiana intre doua puncte in plan folosind math.dist.

            Parametri:
            point1 (tuple): primul punct (x1, y1)
            point2 (tuple): al doilea punct (x2, y2)

            Returneaza:
            float: distanta euclidiana dintre cele doua puncte

            Complexitate:
            O(1) - functia math.dist efectueaza un numar fix de operatii
    """
    return math.dist(point1, point2)


point1=(1,5)
point2=(4,1)

assert my_function(point1,point2) == 5.0
assert ai_function(point1,point2) == 5.0
