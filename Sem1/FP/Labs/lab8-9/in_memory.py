from domain.entities import Persoana

class RepositoryException(Exception):
    pass

class in_memory_repository:
    def __init__(self):
        self.__participanti = {}

    def store(self,pers):
        """
        Preconditii: pers - o Persoana(id, nume, adresa)
        Postconditii: raise RepositoryException daca exista deja o persoana cu acelasi id
        """
        if pers.get_id() in self.__participanti:
            raise RepositoryException()
        self.__participanti[pers.get_id()] = pers

    def size(self):
        """
        Contorizeaza numarul de participanti din __participanti
        Postconditii: returneaza un int
        """
        return len(self.__participanti)

    def get_all_participanti(self):
        """
        Se extrag din dictionar valorile asociate fiecarei chei(participant) si se transforma intr-o lista
        Postconditii: returneaza lista tuturor participantilor din __participanti
        """
        return list(self.__participanti.values())

def test_store():
    pers = Persoana("1", "Patricia", "Oradea")
    rep = in_memory_repository()
    assert rep.size() == 0
    rep.store(pers)
    assert rep.size() == 1
    pers2 = Persoana("2", "Andreea", "Cluj")
    rep.store(pers2)
    assert rep.store() == 2
    pers3 = Persoana("2","Ana", "Arad")
    try:
        rep.store(pers3)
        assert False
    except RepositoryException:
        pass

#test_store()