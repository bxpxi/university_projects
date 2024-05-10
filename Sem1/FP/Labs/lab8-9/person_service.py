from domain.entities import Persoana
from repository.in_memory import in_memory_repository
from repository.in_memory import RepositoryException
from domain.validators import Persoana_Validator
from itertools import count
from domain.data_transfer import AddressReportItem

class Persoana_service:
    def __init__(self, rep, val):
        """
        Se initializeaza service-ul
        Preconditii: rep - repository - obiect in care se stocheaza studentii
                     val - validator - obiect care verifica studentii
        """
        self.__rep = rep
        self.__val = val

    def creeaza_persoana(self, id, nume, adresa):
        """
        Se stocheaza o persoana
        :param id: string
        :param nume: string
        :param adresa: string
        :return: se stocheaza persoana
        Persoana e adaugata in repository
        RepositoryException daca pers exista deja
        ValidationException daca pers nu e valida
        """
        pers = Persoana(id, nume, adresa)
        self.__val.validate(pers)
        self.__rep.store(pers)
        return pers

    def get_all(self):
        """
        returneaza lista cu toate persoanele din sistem
        """
        return self.__rep.get_all()

    def get_aggregate_on_address(self):
        """
        Numara cati studenti sunt pentru fiecare adresa
        :return: lista de ReportItems
        """
        countDic = {}
        for pers in self.__rep.get_all():
            adr = pers.get_address()
            if adr in countDic:
                countDic[adr].incrementare_count()
            else:
                countDic[adr] = AddressReportItem(adr, 1)
        return list(countDic.values())


def test_creeaza_pers():
    rep = in_memory_repository()
    val = Persoana_Validator()
    srv = Persoana_service()
    pers = srv.creeaza_persoana("1","Patricia","Oradea")
    assert pers.get_id() == "1"
    assert pers.get_nume() == "Patricia"
    assert pers.get_adresa() == "Oradea"
    all = srv.get_all()
    assert len(all) == 1
    assert all[0] == pers
    try:
        pers = srv.creeaza_persoana("1","Ana","Oradea")
        assert False
    except RepositoryException:
        assert True

#test_creeaza_pers()

def test_report_address():
    rep = in_memory_repository()
    val = Persoana_Validator()
    srv = Persoana_service()
    srv.creeaza_persoana("1","Patricia", "Cluj")
    srv.creeaza_persoana("2","Patricia2", "Cluj")
    srv.creeaza_persoana("3","Patricia3", "Oradea")
    srv.creeaza_persoana("4","Patricia4", "Oradea")
    report_items = srv.get_aggregate_on_address()
    assert len(report_items) == 3

#test_report_address()

