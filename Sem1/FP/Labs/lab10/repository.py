from entities import Specie

class Repository:
    def __init__(self, file):
        self.file = file
    def get_all(self):
        #returneaza toate elementele din fisier
        #lista - o lista ce contine elementele din fisier
        f = open(self.file, "r")
        linie = f.readline()
        lista = []
        while linie != "":
            atribut = linie.split(',')
            if len(atribut) == 6:
                lista.append(Specie(atribut[0], atribut[1], atribut[2], atribut[3], atribut[4], atribut[5]))
            linie = f.readline()
        f.close()
        return lista

