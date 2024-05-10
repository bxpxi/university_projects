from services.person_service import Persoana_service
from domain.entities import Persoana
from repository.in_memory import RepositoryException
from domain.validators import ValidatorException

class Console:
    def __init__(self,srv):
        self.__srv = srv
    def __show__all(self):
        """
        View/print toti participantii
        """
        persoane = self.__srv.get_all()
        if len(persoane) == 0:
            print("Nu exista persoana inscrisa :(")
        else:
            print("ID   NUME    ADRESA")
            for pers in persoane:
                print(pers.get_id(), pers.get_nume(), pers.get_adresa())

    def __add(self):
        """
        Adauga o persoana
        """
        id = input("Introduceti id-ul persoanei: ")
        nume = input("Introduceti numele persoanei: ")
        adresa = input("Introduceti adresa persoanei: ")
        try:
            pers = self.__srv.creeaza_persoana(id, nume, adresa)
            print("Participant" + pers.get_nume() + "a fost salvat")
        except RepositoryException:
            print("Mai exista un participant cu acelasi id!")
        except ValidatorException as ex:
            print(ex.get_errors())

    def __show_nr_pers_pe_adresa(self):
        """
        Arata tabelul cu adresa si cati participanti sunt pe adresa
        """
        report_items = self.__srv.get_aggregate_on_address()
        print("| {:^10} | | {:^10} |".format("Address", "Count"))
        for item in report_items:
            print("| {:^10} | | {:^10} |".format(item.get_address(), item.get_count()))

    def show_ui(self):
        while True:
            cmd= input("Introduceti comanda (Add/View/Report)")
            if cmd == "Add":
                self.__add()
            if cmd == "View":
                self.__show__all()
            if cmd == "Report":
                self.__show_nr_pers_pe_adresa()
