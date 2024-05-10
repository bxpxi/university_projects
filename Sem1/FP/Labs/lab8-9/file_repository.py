from repository.in_memory import in_memory_repository
from domain.entities import Persoana
from utils.file_utils import clear_file_content

class persoana_repository_file(in_memory_repository):
    """
    Se ocupa de incarcarea/stocarea persoanelor din/in fisier text
    """
    def __init__(self, file_name):
        in_memory_repository.__init__(self)
        self.__file_name = file_name
        #self.__load_from_file2()

    def create_person_from_line(self, line):
        """
        Se proceseaza o linie din fisier si se creeaza o persoana
        Preconditii: line - linie din fisier
        Postconditii: returneaza persoana
        """
        fields = line.split(" ")
        pers = Persoana(fields[0], fields[1], fields[2])
        return pers

    def load_from_file(self):
        """
        Incarca studentul din fisier
        Fisierul se ia total
        """
        fh = open(self.__file_name)
        content = fh.read()
        fh.close()
        lines = content.split('\n')
        for line in lines:
            if line.strip() == "":
                continue
            pers = self.__create_person_from_line(line)
            self.__participanti[pers.get_id()] = pers

    def load_from_file2(self):
        """
        Incarca studentul din fisier
        Fisierul se ia linie cu linie
        """
        fh = open(self.__file_name)
        for line in fh:
            if line.strip() == "":
                continue
            pers = self.__create_person_from_line(line)
            in_memory_repository.store(self, pers)
        fh.close()

    def store(self,pers):
        in_memory_repository.store(self, pers)
        self.__append_to_file(pers)

    def append_to_file(self, pers):
        """
        Se adauga o noua linie la fisierul ce reprezinta persoana pers
        """
        fh = open(self.__file_name, "a")
        line = pers.get_id() + " " + pers.get_nume() + " " + pers.get_adresa()
        fh.write("\n")
        fh.write(line)
        fh.close()


def test_repository():
    file_name = "test.txt"
    clear_file_content(file_name)
    repo = persoana_repository_file(file_name)
    assert repo.size() == 0
    repo.store(Persoana("1","Patricia", "Oradea"))
    assert repo.size() == 1

def test_read():
    file_name = "c:/temp/test.txt"
    clear_file_content(file_name)
    repo = persoana_repository_file(file_name)
    repo.store(Persoana("1","Patricia","Oradea"))
    repo.store(Persoana("2","Ana","Cluj"))
    repo2 = persoana_repository_file(file_name)
    assert repo2.size() == 2

#test_repository()
#test_read()