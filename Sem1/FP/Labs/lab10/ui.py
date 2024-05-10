from entities import Specie
from repository import Repository
from controller import Controller

class Console:
    def __init__(self, controller):
        self.controller = controller

    def cerinta1(self):
        data = input("Introduceti data: ")
        afis = self.controller.cerinta1(data)
        if afis == []:
            print("Nu exista specii descoperite inainte de data respectiva.")
        else:
            for specie in afis:
                print(specie)

    def cerinta2(self):
        """
        tip = input("Introduceti tip: ")
        nume = self.controller.cerinta2_1(tip)
        medie = self.controller.cerinta2_2(tip)
        print("Nume: ", nume, "\n")
        print("Durata medie de viata: ", medie)
        """
        lista = self.controller.cerinta2()
        for tip in lista:
            nume = self.controller.cerinta2_1(tip)
            medie = self.controller.cerinta2_2(tip)
            print(nume,",", medie)

    def meniu(self):
        while True:
            print("Meniu\n"
                  "1. Afisarea tuturor speciilor descoperite inainte de o data\n"
                  "2. Statistici - numele speciei descoprite cel mai recent + media duratei de viata\n"
                  "x. Exit")
            optiune = input("Introduceti optiunea: ")
            if optiune == "1":
                self.cerinta1()
            elif optiune == "2":
                self.cerinta2()
            elif optiune == "x":
                break
            else:
                print("Optiune invalida!")