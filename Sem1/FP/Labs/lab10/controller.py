from repository import Repository
from entities import Specie

class Controller:
    def __init__(self, repo):
        self.repo = repo

    def cerinta1(self, data):
        """
        Functie care returneaza speciile descoperite inainte de o data
        :param data: str de froma YYYY/MM/DD
        :return: rez - o lista
        """
        f = open("file.txt", "r")
        lista = self.repo.get_all()
        f.close()

        rez = []

        for specie in lista:
            if specie.get_data() < data:
                rez.append(specie)

        return rez

    def cerinta2_1(self, tip):
        """
        Functie care returneaza specia cea mai recenta
        :param tip: str nevid
        :return: str
        """
        f = open("file.txt", "r")
        lista = self.repo.get_all()
        f.close()

        rez = []

        for specie in lista:
            if specie.get_tip() == tip:
                rez.append(specie)

        data_recenta = "0000/00/00"
        specie_recenta = ""
        for specie in rez:
            if specie.get_data() > data_recenta:
                specie_recenta = specie.get_nume()
                data_recenta = specie.get_data()

        return specie_recenta

    def cerinta2_2(self, tip):
        """
        Functie care returneaza durata de viata medie
        :param tip: str
        :return: int
        """
        f = open("file.txt", "r")
        lista = self.repo.get_all()
        f.close()

        rez = []

        for specie in lista:
            if specie.get_tip() == tip:
                rez.append(specie)

        medie_lifespan = 0
        suma = 0
        numar = 0

        for specie in rez:
            suma += int(specie.get_lifespan())
            numar += 1

        if numar!= 0:
            medie_lifespan = int(suma/numar)

        return medie_lifespan

    def cerinta2(self):
        f = open("file.txt", "r")
        lista = self.repo.get_all()
        f.close()

        lista_tip = []

        for specie in lista:
            if specie.get_tip() not in lista_tip:
                lista_tip.append(specie.get_tip())

        return lista_tip

