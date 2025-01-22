import random
import math
import matplotlib.pyplot as plt

#1a
def birthday_simulation(n, trials=100):
    successful_trials = 0;
    for _ in range(trials):
        birthdays = [random.randint(1, 365) for _ in range(n)]
        if len(birthdays) != len(set(birthdays)):
            successful_trials += 1
    return successful_trials / trials;

n = 20;
prob = birthday_simulation(n)
print(f"Probabilitatea ca intr-un grup de {n} persoane, cel putin doua sa aiba aceeasi zi de nastere: {prob}")

#1b
def birthday_exact(n):
    if n > 365:
        return 1.0

    prob_opus = 1.0
    for i in range(n):
        prob_opus *= (365-i)/365.0

    return 1 - prob_opus

n = 20
prob2 = birthday_simulation(n)
print(f"Probabilitatea exacta ca intr-un grup de {n} persoane, cel putin doua sa aiba aceeasi zi de nastere: {prob2}")

#1c
n_values = list(range(2, 51))
simulated_probs = [birthday_simulation(n) for n in n_values]
exact_probs = [birthday_exact(n) for n in n_values]

plt.plot(n_values, simulated_probs, "r-", label="Simulare")
plt.plot(n_values, exact_probs, "b--", label="Probabiliatate exacta")

plt.xlabel("Numarul de persoane(n)")
plt.ylabel("Probabilitatea")

plt.title("Probabilitatea ca cel putin 2 persoane sa aiba aceeasi zi de nastere")
plt.legend()
plt.grid(True)
plt.show()


from matplotlib.pyplot import axis, plot, show, scatter, title, xlabel, ylabel, grid
from random import random
from math import dist, sin, cos, pi, acos, degrees


def genereaza_puncte(N):
    return [(random(), random()) for _ in range(N)]


def este_in_cerc(punct):
    centru = (0.5, 0.5)
    raza = 0.5
    return dist(punct, centru) <= raza


def este_mai_aproape_de_centru(punct):
    centru = (0.5, 0.5)
    distante_la_varfuri = [
        dist(punct, (0, 0)),
        dist(punct, (0, 1)),
        dist(punct, (1, 0)),
        dist(punct, (1, 1))
    ]
    return dist(punct, centru) < min(distante_la_varfuri)


def numara_triunghiuri_ascutit_obtuz(punct):
    varfuri = [(0, 0), (0, 1), (1, 0), (1, 1)]
    unghiuri = []

    for v1 in varfuri:
        for v2 in varfuri:
            if v1 != v2:
                a = dist(punct, v1)
                b = dist(punct, v2)
                c = dist(v1, v2)
                if a > 0 and b > 0:
                    cos_unghi = (a ** 2 + b ** 2 - c ** 2) / (2 * a * b)
                    unghi = acos(cos_unghi)
                    unghiuri.append(unghi)

    numar_ascutit = sum(1 for unghi in unghiuri if degrees(unghi) < 90)
    numar_obtuz = sum(1 for unghi in unghiuri if degrees(unghi) > 90)
    return numar_ascutit == 2 and numar_obtuz == 2


def frecvente_relative(N):
    puncte = genereaza_puncte(N)
    in_cerc = sum(este_in_cerc(p) for p in puncte)
    aproape_de_centru = sum(este_mai_aproape_de_centru(p) for p in puncte)
    puncte_ascutit_obtuz = sum(numara_triunghiuri_ascutit_obtuz(p) for p in puncte)

    # Diagnostice
    print(
        f"Număr puncte în cerc: {in_cerc}, Număr puncte aproape de centru: {aproape_de_centru}, Număr puncte triunghiuri: {puncte_ascutit_obtuz}")

    return (in_cerc / N, aproape_de_centru / N, puncte_ascutit_obtuz / N)


def reprezinta_grafic(puncte, caz, N):
    x, y = zip(*puncte)
    scatter(x, y, s=1)

    num_points = 200
    theta = [i * (pi / 50) for i in range(num_points)]
    cerc_x = [0.5 + 0.25 * sin(2 * t) * cos(t) for t in theta]
    cerc_y = [0.5 + 0.25 * sin(2 * t) * sin(t) for t in theta]

    plot(cerc_x, cerc_y, 'r-', linewidth=2)

    axis('square')
    axis((0, 1, 0, 1))
    plot(0.5, 0.5, 'ro')
    title(f'Puncte generate aleatoriu - {caz} (N = {N})')
    xlabel('X')
    ylabel('Y')
    grid()
    show()


def main():
    N_valori = [500, 1000, 2000]

    for N in N_valori:
        frecvente = frecvente_relative(N)
        print(f"N = {N}")
        print(f"Frecvența relativă a punctelor în interiorul cercului: {frecvente[0]}")
        print(f"Frecvența relativă a punctelor mai aproape de centru: {frecvente[1]}")
        print(
            f"Frecvența relativă a punctelor cu 2 triunghiuri ascuțitunghice și 2 triunghiuri obtuzunghice: {frecvente[2]}")

        puncte = genereaza_puncte(N)
        reprezinta_grafic(puncte, "Puncte aleatorii", N)


main()