"""Se da un fisier care contine un text (format din mai multe propozitii) in limba romana - a se vedea fisierul
”data/texts.txt”. Se cere sa se determine si sa se vizualizeze:

numarul de propozitii din text;
numarul de cuvinte din text
numarul de cuvinte diferite din text
cel mai scurt si cel mai lung cuvant (cuvinte)
textul fara diacritice
sinonimele celui mai lung cuvant din text
"""

import string
import nltk as nl
import rowordnet as rwn
import spacy
import unidecode as uni

def numar_propozitii(text):
    #nl.download('punkt_tab')
    return len(nl.tokenize.sent_tokenize(text))

def numar_cuvinte(text):
    cuvinte = nl.tokenize.word_tokenize(text)
    cuvinte_fara_punctuatie = [cuvant for cuvant in cuvinte if cuvant not in string.punctuation]
    return len(cuvinte_fara_punctuatie)

def numar_cuvinte_diferite(text):
    cuvinte = nl.tokenize.word_tokenize(text)
    cuvinte_fara_punctuatie = [cuvant for cuvant in cuvinte if cuvant not in string.punctuation]
    cuvinte_diferite = set([cuvant.lower() for cuvant in cuvinte])
    return len(cuvinte_diferite)

def cel_mai_scurt(text):
    cuvinte = nl.tokenize.word_tokenize(text)
    cuvinte_fara_punctuatie = [cuvant for cuvant in cuvinte if cuvant not in string.punctuation]
    cel_mai_scurt = min(cuvinte_fara_punctuatie, key=len)
    return cel_mai_scurt

def cel_mai_lung(text):
    cuvinte = nl.tokenize.word_tokenize(text)
    cuvinte_fara_punctuatie = [cuvant for cuvant in cuvinte if cuvant not in string.punctuation]
    cel_mai_lung = max(cuvinte_fara_punctuatie, key=len)
    return cel_mai_lung

def eliminare_diacritice(text):
    return uni.unidecode(text)

def lematizare(cuvant):
    limbaj_natural = spacy.load('ro_core_news_sm')
    doc = limbaj_natural(cuvant)
    return [token.lemma_ for token in doc]

def sinonime_pentru_cel_mai_lung(text):
    cuvant = cel_mai_lung(text)
    word_net = rwn.RoWordNet()
    doc = lematizare(cuvant)[0]
    synsets = word_net.synsets(literal=str(doc))
    sinonime = []
    for synset_id in synsets:
        synset = word_net.synset(synset_id)
        for literal in synset.literals:
            if literal != str(doc):
                sinonime.append(literal)
    return sinonime

def normalizare_propozitie(propozitie):
    cuvinte = nl.tokenize.word_tokenize(propozitie.lower())
    frecvente_cuvinte = nl.FreqDist(cuvinte)
    max_clipping = 2
    cuvinte_normalizare = {}

    for cuvant, frecventa in frecvente_cuvinte.items():
        if frecventa >= max_clipping:
            cuvinte_normalizare[cuvant] = max_clipping
        else:
            cuvinte_normalizare[cuvant] = frecventa

    propozitie_normalizata = ' '.join([cuvant for cuvant in cuvinte_normalizare])

    return propozitie_normalizata

def normalizare(text):
    propozitii = nl.tokenize.sent_tokenize(text)
    for propozitie in propozitii:
        print(normalizare_propozitie(propozitie))

def main():
    with open("texts.txt", "r", encoding="utf-8") as file:
        text = file.read()
        print("Numar propozitii: ",numar_propozitii(text))
        print("Numar cuvinte: ", numar_cuvinte(text))
        print("Numar cuvinte diferite: ", numar_cuvinte_diferite(text))
        print("Cel mai scurt cuvant: ", cel_mai_scurt(text))
        print("Cel mai lung cuvant: ", cel_mai_lung(text))
        print("Fara diacritice: ", eliminare_diacritice(text))
        print("Sinonime pentru cel mai lung cuvant: ", sinonime_pentru_cel_mai_lung(text))
        normalizare(text)

main()
