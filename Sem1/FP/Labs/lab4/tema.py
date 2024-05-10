def deschidere_program():
    # aceasta functie va aparea la deschiderea programului
    # are rolul de a informa utilizatorul despre scopul acestui program
    print("\nConcurs de programare \n Aceasta este platforma unde va aparea scorul obtinut de fiecare participant la cele 10 probe de concurs.")

def meniu():
    # prezinta meniul aplicatiei ce va avea mai multe optiuni legate de adaugarea scorului, modificarea scorului, tiparirea unei liste de participanti'
    # , operatii pe un subset de participanti sau undo
        print("Meniu\n")
        print("1. Adauga scor pentru un participant")
        print("2. Inserare scor pentru un participant")
        print("3. Șterge scorul pentru un participant")
        print("4. Șterge scorul pentru un interval de participanți")
        print("5. Înlocuiește scorul de la un participant")
        print("6. Tipărește participanții care au scor mai mic decât un scor dat")
        print("7. Tipărește participanții ordonat după scor")
        print("8. Tipărește participanții cu scor mai mare decât un scor dat, ordonat după scor")
        print("9. Calculează media scorurilor pentru un interval dat")
        print("10. Calculează scorul minim pentru un interval de participanți dat")
        print("11. Tipărește participanții dintr-un interval dat care au scorul multiplu de 10")
        print("12. Filtrare participanți care au scorul multiplu unui număr dat")
        print("13. Filtrare participanți care au scorul mai mic decât un scor dat")
        print("14. Undo")
        print("15. Iesire\n")

def adauga_scor_participant(nr_conc):
    # se adauga scor pentru un singur participant, pe ultima pozitie in lista
    # in lista pe ultima pozitie se pune scorul total
    # in lista pe prima pozitie (index 0) se pune ID-ul concurentului
    p=[0,0,0,0,0,0,0,0,0,0,0,0]
    p[0]=nr_conc
    for i in range(1,10):
      p[i]=int(input(f"Introduceti scorul obtinut de concurent la proba {i+1}: "))
      p[10]+=p[i]
    tabel.append(p)
    print(tabel)


def inserare_scor_participant(nr_conc,poz):
    # se insereaza un scor la un participant pe o pozitie data
    # se inlocuieste vechea valoare cu noul scor
    # in lista pe prima pozitie e ID-ul, iar pe ultima e scorul total
    p = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    total = 0
    for i in range(1,10):
        p[0]=nr_conc
        p[i] = int(input(f"Introduceti scorul obtinut de concurent la proba {i + 1}: "))
        p[11]+=p[i]
    tabel.insert(poz+1,p)
    print(tabel)


def sterge_scor_participant(nr_conc,poz):
    # se sterge un participant din lista
    tabel.pop(poz)



nr_conc = 0
tabel=[]
poz = 0

deschidere_program()
while True:
    meniu()
    op = int(input("Introduceti optiunea dorita: (1/2/3/4/5/6/7/8/9/10/11/12/13/14/15)"))
    if(op==1):
        adauga_scor_participant(nr_conc)
        nr_conc+=1
    elif op==2:
        nr_conc+=1
        poz=int(input("Introduceti pozitia la care doriti sa inserati: "))
        inserare_scor_participant(nr_conc,poz)
    elif op ==3:
        nr_conc-=1
        poz = int(input("Introduceti numarul concurentului pe care doriti sa il stergeti: "))
        sterge_scor_participant(nr_conc, poz)
