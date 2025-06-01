import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

'''
1.S-a efectuat un studiu despre starea domeniului Data Science, iar datele colectate sunt salvate in fisierul "data/surveyDataScience.csv".

1.a. Sa se stabileasca:

numarul de respondenti (de la care s-au colectate informatiile)
numar si tipul informatiilor (atributelor, proprietatilor) detinute pentru un respondent
numarul de respondenti pentru care se detin date complete
durata medie a anilor de studii superioare pentru acesti respondenti (cea efectiva sau cea estimata), durata medie a anilor de studii pentru respondentii din Romania si durata medie a anilor de studii pentru respondentii din Romania care sunt femei. Comparati rezultatele obtinute pentru cele trei grupuri de respondenti. Se presupune ca studiile de licenta dureaza 3 ani, cele de master 2 ani si cele de doctorat 3 ani.
numarul de respondenti femei din Romania pentru care se detin date complete
numarul de femei din Romania care programeaza in Python, precum si intervalul de varsta cu cele mai multe femei care programeaza in Python? Dar in C++? Comparati rezultatele obtinute pentru cele doua limbaje de programare.
domeniul de valori posibile si valorile extreme pentru fiecare atribut/proprietate (feature). In cazul proprietatilor nenumerice, cate valori posibile are fiecare astfel de proprietate
transformati informatiile despre vechimea in programare in numar de ani (folositi in locul intervalului, mijlocul acestuia) si apoi calculati momentele de ordin 1 si 2 pentru aceasta variabila (minim, maxim, media, deviatia standard, mediana). Ce se poate spune despre aceasta variabila?
1.b. Sa se vizualizeze:

distributia respondentilor care programeaza in Python pe categorii de varsta
distributia respondentilor din Romania care programeaza in Python pe categorii de varsta
distributia respondentilor femei din Romania care programeaza in Python pe categorii de varsta
respondentii care pot fi considerati "outlieri" din punct de vedere al vechimii in programare (puteti folositi un boxplot pentru a identifica aceste valori)
'''

def numar_respondenti(file):
    data = pd.read_csv(file, low_memory=False)
    return len(data)

def numar_informatii(file):
    data = pd.read_csv(file, low_memory=False)
    return len(data.columns)
    #return data.dtypes.value_counts()

def numar_respondenti_date_complete(file):
    data = pd.read_csv(file,low_memory=False)
    return data.dropna().shape[0]

def durata_studii(row):
    if row == 'Bachelorâ€™s degree':
        return 3
    elif row == 'Masterâ€™s degree':
        return 2
    elif row == 'Doctoral degree':
        return 3
    else:
        return np.nan
def medie_ani_studii_superioare(file):
    data = pd.read_csv(file, low_memory=False)
    medie_studii = data['Q4'].apply(durata_studii).mean()
    medie_studii_romania = data[data['Q3'] == 'Romania']['Q4'].apply(durata_studii).mean()
    medie_studii_romania_femei = data[(data['Q2'] == 'Woman') & (data['Q3'] == 'Romania')]['Q4'].apply(durata_studii).mean()
    print("Durata medie a anilor de studii superioare: ", medie_studii)
    print("Durata medie a anilor de studii superioare in Romania: ", medie_studii_romania)
    print("Durata medie a anilor de studii superioare in Romania pentru femei: ", medie_studii_romania_femei)

def numar_femei_romania_date_complete(file):
    data = pd.read_csv(file, low_memory=False)
    return data[(data['Q3'] == 'Romania') & (data['Q2'] == 'Woman')].dropna().shape[0]

def numar_femei_romania_python_cpp(file):
    data = pd.read_csv(file, low_memory=False)
    femei_romania = data[(data['Q2'] == 'Woman') & (data['Q3'] == 'Romania')]

    femei_ro_python = femei_romania[femei_romania['Q7_Part_1'] == 'Python']
    nr_femei_ro_python = femei_ro_python.shape[0]
    print("Numar femei din Romania care programeaza in Python: ", nr_femei_ro_python)

    femei_ro_cpp = femei_romania[femei_romania['Q7_Part_5'] == 'C++']
    nr_femei_ro_cpp = femei_ro_cpp.shape[0]
    print("Numar femei din Romania care programeaza in C++: ", nr_femei_ro_cpp)

    interval_python = femei_ro_python['Q1'].value_counts().idxmax()
    print("Intervalul de varsta cu cele mai multe femei din Romania care programeaza in Python: ", interval_python)

    interval_cpp = femei_ro_cpp['Q1'].value_counts().idxmax()
    print("Intervalul de varsta cu cele mai multe femei din Romania care programeaza in C++: ", interval_cpp)

def domeniu_valori_extreme(file):
    data = pd.read_csv(file, low_memory=False)

    for col in data.columns:
        print("Atribut: ", col)
        if pd.api.types.is_numeric_dtype(data[col]):
            print("Minim: ", data[col].min())
            print("Maxim: ", data[col].max())
            print("Domeniu: ", data[col].dropna().unique())
            print("\n")
        else:
            print("Domeniu: ", data[col].dropna().unique())
            print("Numar valori unice: ", len(data[col].dropna().unique()) - 1)
            print("\n")

def transforma_vechime(vechime):
    if pd.isna(vechime):
        return np.nan

    if vechime == "I have never written code" or vechime == "For how many years have you been writing code and/or programming?":
        return 0

    vechime = vechime.replace(" years", "")

    if "<" in vechime:
        return float(vechime.replace("<", ""))/2

    if "+" in vechime:
        return float(vechime.replace("+", ""))

    if "-" in vechime:
        valori = vechime.split("-")
        return (float(valori[0]) + float(valori[1]))/2

    return float(vechime)

def analiza_vechime(file):
    data = pd.read_csv(file, low_memory=False)

    minim = data["Q6"].apply(transforma_vechime).min()
    maxim = data["Q6"].apply(transforma_vechime).max()
    medie = round(data["Q6"].apply(transforma_vechime).mean(),2)
    std = round(data["Q6"].apply(transforma_vechime).std(),2)
    mediana = data["Q6"].apply(transforma_vechime).median()

    print("Minim pentru vechimea in programare: ", minim)
    print("Maxim pentru vechimea in programare: ", maxim)
    print("Medie pentru vechimea in programare: ", medie)
    print("Deviatie standard pentru vechimea in programare: ", std)
    print("Mediana pentru vechimea in programare: ", mediana)

def distributie_python_pe_varsta(file):
    data = pd.read_csv(file, low_memory=False)
    data_python = data[data['Q7_Part_1'] == 'Python']['Q1']

    plt.hist(data_python, bins=11, edgecolor='black')
    plt.xlabel('Varsta')
    plt.ylabel("Respondenti in Python")
    plt.grid()
    plt.show()

def distributie_python_pe_varsta_romania(file):
    data = pd.read_csv(file, low_memory=False)
    data_python = data[(data['Q7_Part_1'] == 'Python') & (data['Q3'] == 'Romania')]['Q1']

    plt.hist(data_python, bins=11, edgecolor='black')
    plt.xlabel('Varsta')
    plt.ylabel("Respondenti in Python in Romania")
    plt.grid()
    plt.show()

def distributie_python_pe_varsta_romania_femei(file):
    data = pd.read_csv(file, low_memory=False)
    data_python = data[(data['Q7_Part_1'] == 'Python') & (data['Q3'] == 'Romania') & (data['Q2'] == 'Woman')]['Q1']

    plt.hist(data_python, bins=11, edgecolor='black')
    plt.xlabel('Varsta')
    plt.ylabel("Respondenti femei in Python in Romania")
    plt.grid()
    plt.show()

def distributie_outliers(file):
    data = pd.read_csv(file, low_memory=False)
    medie = data["Q6"].apply(transforma_vechime).mean()
    std = data["Q6"].apply(transforma_vechime).std()
    outliers = data[data["Q6"].apply(transforma_vechime) > medie + 3 * std]

    plt.boxplot(outliers["Q6"], vert=False)
    plt.xlabel("Vechime in programare")
    plt.ylabel("Outliers")
    plt.grid()
    plt.show()

def normalizare(file):
    data = pd.read_csv(file, low_memory=False)

    studii = data['Q4'].apply(durata_studii).dropna()
    if len(studii) > 0:
        studii_min, studii_max = studii.min(), studii.max()
        if studii_max > studii_min:
            studii_normalizate = [(nr - studii_min) / (studii_max - studii_min) for nr in studii]
        else:
            studii_normalizate = [0] * len(studii)
    else:
        studii_normalizate = []

    vechime = data['Q6'].apply(transforma_vechime).dropna()
    if len(vechime) > 0:
        vechime_min, vechime_max = vechime.min(), vechime.max()
        if vechime_max > vechime_min:
            vechime_normalizata = [(nr - vechime_min) / (vechime_max - vechime_min) for nr in vechime]
        else:
            vechime_normalizata = [0] * len(vechime)
    else:
        vechime_normalizata = []

    if studii_normalizate:
        plt.figure(figsize=(7, 5))
        plt.hist(studii_normalizate, bins=20, edgecolor='black')
        plt.title('Durata studii normalizata')
        plt.xlabel('Valori normalizate')
        plt.ylabel('Frecventa')
        plt.grid()
        plt.show()

    if vechime_normalizata:
        plt.figure(figsize=(7, 5))
        plt.hist(vechime_normalizata, bins=20, edgecolor='black')
        plt.title('Vechimea in programare normalizata')
        plt.xlabel('Valori normalizate')
        plt.ylabel('Frecventa')
        plt.grid()
        plt.show()



def main():
    file = "surveyDataSience2.csv"
    print("Numar respondenti: ", numar_respondenti(file))
    print("Numar informatii(atribute): ", numar_informatii(file))
    print("Numar respondenti cu date complete: ", numar_respondenti_date_complete(file))
    medie_ani_studii_superioare(file)
    print(numar_femei_romania_date_complete(file))
    numar_femei_romania_python_cpp(file)
    domeniu_valori_extreme(file)
    analiza_vechime(file)
    distributie_python_pe_varsta(file)
    distributie_python_pe_varsta_romania(file)
    distributie_python_pe_varsta_romania_femei(file)
    distributie_outliers(file)
    normalizare(file)

main()
