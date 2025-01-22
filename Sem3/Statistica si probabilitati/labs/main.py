from random import sample
from math import factorial, perm, comb
from itertools import permutations, combinations, combinations_with_replacement

#Exercitiile 2 si 3
def func(arg):
    match arg:
        case "perm":
            def permutari(word, numar_total, aleator):
                perm_list = [''.join(p) for p in permutations(word)]
                if numar_total:
                    return factorial(len(word))
                if aleator:
                    return ''.join(sample(word, len(word)))
                return perm_list

            print("Permutari: ", permutari("word", False, False))
            print("Numar permutari: ", permutari("word", True, False))
            print("Permutare aleatoare: ", permutari("word", False, True))

        case 'aranj':
            def aranjamente(word, k, numar_total, aleator):
                arr_list = [''.join(p) for p in permutations(word, k)]
                if numar_total:
                    return perm(len(word), k)
                if aleator:
                    return ''.join(sample(arr_list, 1))
                return arr_list

            print("Aranjamente: ", aranjamente("word", 3, False, False))
            print("Numar aranjamente: ", aranjamente("word", 3, True, False))
            print("Aranjament aleator: ", aranjamente("word", 3, False, True))
        case 'comb':
            def combinari(word, k, numar_total, aleator):
                comb_list = [''.join(p) for p in combinations(word,k)]
                if numar_total:
                    return comb(len(word), k)
                if aleator:
                    return ''.join(sample(comb_list, 1))
                return comb_list

            print("Combinari: ", combinari("word", 2, numar_total=False, aleator=False))
            print("Numar combinari: ", combinari("word", 2, True, False))
            print("Combinare aleatoare: ", combinari("word", 2, False, True))

func("perm")
func("aranj")
func("comb")

#Exercitiul 4
comb_repetari_list = [''.join(p) for p in combinations_with_replacement("ABCDE", 4)]
print("Combinari cu repetitii: ", comb_repetari_list, len(comb_repetari_list))

#Exercitiul 5
print("Aranjamente de 8 luate cate 5")
print(perm(8,5))
