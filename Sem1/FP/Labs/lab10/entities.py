class Specie:
    def __init__(self, id, nume, data, locatie, tip, lifespan):
        self.id = id
        self.nume = nume
        self.data = data
        self.locatie = locatie
        self.tip = tip
        self.lifespan = lifespan

    def get_id(self):
        #returneaza id-ul unei specii
        return self.id

    def get_nume(self):
        #returneaza numele unei specii
        return self.nume

    def get_data(self):
        #returneaza data unei specii
        return self.data

    def get_locatie(self):
        #returneaza locatia unei specii
        return self.locatie

    def get_tip(self):
        #returneaza tipul unei specii
        return self.tip

    def get_lifespan(self):
        #returneaza durata de viata a unei specii
        return self.lifespan

def test_specie():
    specie = Specie("1","Bober", "2023/12/12","Poland", "mammal", "10")
    assert specie.get_id() == "1"
    assert specie.get_nume() == "Bober"
    assert specie.get_data() == "2023/12/12"
    assert specie.get_locatie() == "Poland"
    assert specie.get_tip() == "mammal"
    assert specie.get_lifespan() == "10"

test_specie()
