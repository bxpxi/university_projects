def creeaza_user(_id_user, _user_name, _scor):
    """"
    functie care creeaza un user pe baza _id_user, _user_name, _scor
    preconditii: _id_user: int>0
                 _user_name: string nenul
                 _scor: int>=0, int<=100
    postconditii: un user cu id-ul _id_user, numele _user_name, scorul _scor
    """
    return [_id_user,_user_name,_scor]

def get_id_user(user):
    """"
    functie care returneaza id-ul user-ului user
    preconditii: user: un user
    postconditii: id_user: int>0 , id-ul user-ului user
    """
    return user[0]

def get_nume(user):
    """
    functie care returneaza numele user-ului user
    preconditii: user: un user
    postconditii: user_name: string nenul, numele user-ului user
    """
    return user[1]

def get_scor(user):
    """"
    functie care returneaza scorul user-ului user
    preconditii: user:un user
    postconditii: scor: int=>0, int<=100, scorul user-ului user
    """
    return user[2]


def egal_useri(user_a,user_b):
    """"
    functie care verifica daca id-urile a doi useri, numele lor si scorurile sunt egale
    preconditii: user_a, user_b: useri
    postconditii: true, daca user_a si user_b au aceleasi atribute
                  false, altfel
    """
    return user_a[0]==user_b[0]

def valideaza_user(user):
    """"
    functie care verifica daca id-ul user-ului este pozitiv, daca numele este nevid si daca scorul este in intervalul [0,100]
    preconditii: user: un user
    postconditii: -
    raises: Exception cu mesajul : string
            "ID invalid!\n" daca id-ul<=0
            "Nume invalid!\n" daca numele este nul
            "Scor invalid!\n" daca scorul este <0 sau >100
    """
    eroare=""
    if get_id_user(user)<=0:
        eroare+="ID invalid!\n"
    if get_nume()=="":
        eroare+="Nume invalid!\n"
    if get_scor(user)<0 or get_scor(user)>100:
        eroare+="Scor invalid!\n"
    if(len(eroare)>0):
        raise Exception(eroare)

def adauga_user_in_lista_useri(lista_useri,user):
    """"
    functie care adauga user-ul user in lista de useri daca nu exista deja
    un user cu acelasi id in lista_useri
    preconditii: un user
                lista_useri: lista de useri unic identificabili prin id intreg pozitiv
    postconditii: lista_useri = lista_useri U {user}, daca user nu apartine lista_useri
    raises: Exception cu mesajul: string
            "User existent!\n" daca exista un uer cu acelasi id in lista_useri
    """
    for user in lista_useri:
        if egal_useri(_user,user):
            raise Exception("User existent\n")
    lista_useri.append(user)


def test_adauga_user_in_lista_useri():
    lista_useri=[]
    id_user_valid = 24
    user_name_valid = "Patricia"
    scor_valid = 62
    user_valid = creeaza_user(id_user_valid, user_name_valid, scor_valid)
    assert(len(lista_useri)==0)
    adauga_user_in_lista_useri(lista_useri,user_valid)
    assert(len(lista_useri)==1)
    user= creeaza_user(id_user_valid,user_name_valid,scor_valid)
    assert(egal_useri(user,lista_useri[0]))
    try:
        adauga_user_in_lista_useri(lista_useri, user_valid)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "User existent!\n")

def test_valideaza_user():
    id_user_valid = 24
    user_name_valid = "Patricia"
    scor_valid = 62
    user_valid = creeaza_user (id_user_valid, user_name_valid, scor_valid)
    valideaza_user(user_valid)
    id_user_invalid = -24
    user_name_invalid = ""
    scor_invalid = -5
    user_invalid = creeaza_user(id_user_invalid, user_name_invalid, scor_invalid)
    try:
        valideaza_user(user_invalid)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="ID invalid!\nNume invalid!\nScor invalid!\n")

def service_adauga_user_in_lista_useri(lista_useri,id_user,user_name,scor):
    """
    functie care pe baza unui id intreg id_user, unui string user_name si a unui scor int scor va crea si valida
    un user si dac acesta este valid il va adauga in lista de useri doar daca nu exista deja un user cu acelasi id in lista useri
    preconditii: lista_useri: lista de useri unic identificabili
    postconditii: -, daca user-ul este creat, validat si adaugat la lista cu succes
                 raises Exception cu mesajul string
                                  "ID invalid!\n" daca id-ul<=0
                                "Nume invalid!\n" daca numele este nul
                                 "Scor invalid!\n" daca scorul este <0 sau >100

    """
    user=creeaza_user(id_user,user_name,scor)
    valideaza_user(user)
    adauga_user_in_lista_useri(lista_useri,user)

def test_service_adauga_user_in_lista_useri():
    id_user = 24
    user_name = "Patricia"
    scor = 62
    lista_useri=[]
    user = creeaza_user(id_user,user_name,scor)
    service_adauga_user_in_lista_useri(lista_useri,id_user,user_name,scor)
    assert(len(lista_useri)==1)
    assert(egal_useri(user,lista_useri[0]))
    try:
        service_adauga_user_in_lista_useri(lista_useri,id_user,user_name,scor)
        assert(False)
    except Exception as ex:
        assert(str(ex) == "User existent!\n")
    id_user_invalid = -24
    user_name_invalid = ""
    scor_invalid = -5
    try:
        service_adauga_user_in_lista_useri(lista_useri, id_user_invalid, user_name_invalid, scor_invalid)
        assert(False)
    except Exception as ex:
        assert(str(ex)=="ID invalid!\nNume invalid!\nScor invalid!\n")


def citeste_numar(prompt,f,msg):
    while True:
        try:
            return f(input(prompt))
        except ValueError:
            print(msg)

def ui_adauga_user_in_lista_de_useri(lista_useri):
    id_user = citeste_numar("Introduceti un ID intreg pozitiv: ",int,"Valoare numerica invalida!")
    user_name = input("Introduceti numele nevid")
    scor = citeste_numar("Introduceti scorul intreg cuprins in intervalul [0,100]",int,"Valoare numerica invalida!")
    service_adauga_user_in_lista_useri(lista_useri,id_user,user_name,scor)


def run():
    lista_useri=[]
    while True:
        cmd = input()
        if cmd == "adauga_user":
            try:
                ui_adauga_user_in_lista_de_useri(lista_useri)
            except Exception as ex:
                print(ex)


def test_creeaza_user():
    id_user = 24
    user_name = "Patricia"
    scor = 62
    user = creeaza_user(id_user,user_name,scor)
    assert(get_id_user(user)==id_user)
    assert(get_nume(user)==user_name)
    assert(get_scor(user)==scor)

def ruleaza_teste():
    test_creeaza_user()
    test_valideaza_user()
    test_adauga_user_in_lista_useri()
    test_service_adauga_user_in_lista_useri()

def main():
    ruleaza_teste()
    run()

main()
