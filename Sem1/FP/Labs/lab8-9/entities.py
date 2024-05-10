class Persoana:
    def __init__(self, id, nume, adresa):
        """"
        Se creeaza o noua persoana in functie de id, nume si adresa
        Preconditii: id, nume, adresa - string-uri nevide
        """
        self.__id = id
        self.__nume = nume
        self.__adresa = adresa

    def get_id(self):
        return self.__id

    def get_nume(self):
        return self.__nume

    def get_adresa(self):
        return self.__adresa

    def verifica_egal(self, pers):
        """"
        Se verifica daca exista doua persoane cu acelasi id
        Preconditii: pers - o persoana cu id, nume, adresa
        Postconditii: returneaza True daca mai exista vreo persoana cu acelasi id
        """
        return self.get_id() == pers.get_id()


def test_creeaza_persoana():
    """"
    Se testeaza crearea de persoane
    """
    pers = Persoana("1", "Patricia", "Oradea")
    assert pers.get_id() == "1"
    assert pers.get_nume() == "Patricia"
    assert pers.get_adresa() == "Oradea"


def test_verifica_egal():
    pers1 = Persoana("1","Patricia", "Oradea")
    pers2 = Persoana("1","Patricia", "Oradea")
    assert pers1 == pers2

#test_creeaza_persoana()
#test_verifica_egal()
