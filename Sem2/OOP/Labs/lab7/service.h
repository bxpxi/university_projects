#pragma once

#include "repository.h"
#include "validators.h"
#include <functional>

using std::function;

class Magazin{
private:
    ProdusRepository& repo;
    ProdusValidator& val;

    /*
    Filtreaza
     */

    vector<Produs> filter(const function<bool(const Produs&)>& fct);

    /*
    * Functie de sortare proprie
    *
    * @param maiMicF: functia de comparare folosita pentru sortare
    *
    * @return: lista de produse sortata dupa criteriul dat (vector cu elemente de
    *			tip Produs)
    */
    vector<Produs> generalSort(bool(*maiMicF)(const Produs&, const Produs&));

public:
    Magazin(ProdusRepository& produsRepo, ProdusValidator& produsVal):repo{produsRepo}, val{produsVal} {};
    Magazin(const Magazin& ot) = delete;

    /*
    Adauga un produs cu denumirea denumire, pretul pret, tipul tip si producatorul producator
    *@param denumire: numele produsului care se adauga (string)
    *@param pret: pretul produsului care se adauga (int)
    *@param tip: tipul produsului care se adauga (string)
    *@param producator: producatorul produsului care se adauga (string)
    *
    * @throws:
    *	RepoException daca mai exista produsul cu denumirea data
    */

    void addProdus(string denumire, int pret, string tip, string producator);

    /*
    * Modifica un produs cu identificator unic denumire
    * @param denumire: denumirea produsului unic identificabil (string)
    * @param pretNou: pretul nou (int)
    * @param tipNou: tipul nou (string)
    * @param producatorNou: producatorul nou(string)
    *
    * @throws
    *	RepoExcepction daca produsul nu exista
    */

    void modifyProdus(const string& denumire, int pretNou, string tipNou, string producatorNou);

    /*
    * Sterge un produs existent
    * @param denumire: numele produsului unic identificabil (string)
    *
    * @throws
    *	RepoException daca produsul nu exista
    */

    void deleteProdus(const string& denumire);

    const Produs& search(const string& denumire);

    /*
    Returneaza un vector cu toate produsele disponibile

    @return: lista cu toate produsele disponibile (vector cu obiecte de tip Produs)
    */

    vector <Produs> getAllProduse() {
        return this->repo.getallProduse();
    }

    vector<Produs> filtrarePret(int pret);


    vector<Produs> filtrareProducator(const string& producator);


    vector<Produs> sortByPret();


    vector<Produs> sortByDenumire();

    vector<Produs> sortByTip();


};
void testeService();