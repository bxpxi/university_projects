import random
from math import comb
from random import randrange
from matplotlib.pyplot import bar, hist, grid, show, legend
import matplotlib.pyplot as plt
from scipy.stats import binom
from collections import Counter

def exercitiul1a():
    rosii = 5
    albastre = 3
    verzi = 2

    total = ['rosu']*rosii + ['albastru']*albastre + ['verde']*verzi
    extrageri = 3
    simulari = 100000

    evenimentA = 0
    evenimentBsiA = 0

    for _ in range(simulari):
        bile_extrase = random.sample(total, extrageri)
        contine_rosu = 'rosu' in bile_extrase
        aceeasi_culoare = len(set(bile_extrase)) == 1

        if contine_rosu:
            evenimentA += 1
            if aceeasi_culoare:
                evenimentBsiA += 1

    prob = evenimentBsiA / evenimentA if evenimentA !=0 else 0
    print(f"P(B|A) = {prob}")

exercitiul1a()

def exercitiul1b():
    rosii = 5
    albastre = 3
    verzi = 2
    total = rosii + albastre + verzi

    extrageri = comb(total,3)

    # nu e nico bila rosie => opusA
    opusA = comb(albastre + verzi, 3)
    probA = 1 - opusA / extrageri

    #P(A si B) => toate bilele sunt rosii
    A_si_B = comb(rosii, 3)
    probBsiA = A_si_B / extrageri

    #P(B|A) = P(B si A) / P(A)
    prob = probBsiA / probA if probA != 0 else 0
    print(f"P(B|A) = {prob}")

exercitiul1b()

def exercitiul2():
    data = [randrange(1,7) for _ in range(500)]
    bin_edges = [k + 0.5 for k in range(1,7)]
    hist(data, bins=bin_edges, density=True, rwidth=0.9, color='green',edgecolor='black',alpha=0.5,label='frecvente relative')
    distribution=dict([(i,1/6) for i in range(1,7)])
    bar(distribution.keys(),distribution.values(),width=0.85,color='red',edgecolor='black',alpha=0.6,label='probabilitati')
    legend(loc='lower left')
    grid()
    show()

exercitiul2()

def exercitiul3():
    bile1 = 6
    bile0 = 4
    urna = [1]*bile1 + [0]*bile0
    extrageri = 5
    simulari = 100000

    X_values = [sum(random.choices(urna, k=extrageri)) for _ in range(simulari)]

    plt.hist(X_values, bins=range(min(X_values), max(X_values) + 2), density=True, rwidth=0.9, color='blue',alpha=0.5,edgecolor='black',label='Frecevnte relative')

    n = extrageri
    p = bile0 / (bile1 + bile0) #probabilitatea de a extrage o bila de 1

    prob = [binom.pmf(k,n,p) for k in range(extrageri+1)]
    plt.bar(range(extrageri+1), prob, color='orange',alpha=0.6,edgecolor='black',label='Probabilitati teoretice')
    plt.legend(loc='upper right')
    plt.grid()
    plt.show()

    probC = sum(2<x<=5 for x in X_values) / simulari
    probCTeoretica = binom.cdf(5,n,p) - binom.cdf(2,n,p)

    print(f"P(2<X<5) estimata: {probC}")
    print(f"P(2<X<5) teoretica: {probCTeoretica}")

exercitiul3()

def exercitiul4():
    numere_zar = 6
    simulari = 100000
    sume_posibile = range(3, 3 * numere_zar + 1)

    sume = [sum(random.choices(range(1, numere_zar + 1), k=3)) for _ in range(simulari)]
    counts = Counter(sume)

    frecv_rel = {k: v/simulari for k,v in counts.items()}

    plt.bar(frecv_rel.keys(), frecv_rel.values(), color='blue', alpha=0.5, label='Frecvente relative')

    prob_teoretice = {sum_val : counts[sum_val] / simulari for sum_val in sume_posibile}
    plt.bar(prob_teoretice.keys(), prob_teoretice.values(), color='red', alpha=0.6, edgecolor='black', label='Probabilitati teoretice')

    plt.legend();
    plt.grid()
    plt.show()

    cele_mai_bune_alegeri = sorted(frecv_rel, key=frecv_rel.get,reverse=True)[:3]
    print(f"Cele mai bune numere de ales: {cele_mai_bune_alegeri}")

exercitiul4()
