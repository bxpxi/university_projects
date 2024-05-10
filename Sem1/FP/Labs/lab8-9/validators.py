from domain.entities import Persoana

class ValidatorException(Exception):
    def __init__(self, errors):
        self.errors = errors

    def get_errors(self):
        return self.errors


class Persoana_Validator:
    def validate(self, pers):
        """"
        Arunca ValidatorException daca campurile ce trebuie completate sunt goale, id/nume/adresa sunt siruri vide
        """
        errors=[]
        if pers.get_id() == "":
            errors.append("Trebuie sa completati id-ul!")
        if pers.get_nume() == "":
            errors.append("Trebuie sa completati numele!")
        if pers.get_adresa() == "":
            errors.append("Trebuie sa completati adresa!")
        if len(errors) > 0 :
            raise ValidatorException(errors)


def test_Persoana_Validator():
    validator = Persoana_Validator

    pers = Persoana("","","")
    try:
        validator.validate(pers)
        assert False
    except ValidatorException as ex:
        assert len(ex.get_errors()) == 3

    pers = Persoana("1", "", "")
    try:
        validator.validate(pers)
        assert False
    except ValidatorException as ex:
        assert len(ex.get_errors()) == 2

    pers = Persoana("245","Patricia", "Oradea")
    try:
        validator.validate(pers)
        assert True
    except ValidatorException as ex:
        assert False


#test_Persoana_Validator()