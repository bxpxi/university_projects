#pragma once

#include "domain.h"
#include "repository.h"
#include <string>
#include <vector>
#include <functional>

using std::vector;
using std::string;
using std::function;

class MagazinService {
    ProdusRepo& Repo;
    vector<Produs> filtrare(const function<bool(const Produs&)>& fct);
public:
    explicit MagazinService(ProdusRepo& repo):Repo{repo}{}
    MagazinService() = delete;
    MagazinService(const MagazinService& pt) = delete;

    ~MagazinService() = default;

    const vector<Produs>& getAll() noexcept {
        return Repo.getAll();
    }

    /*
     * adauga produs in service
     * nume - adresa unui string
     * tip - adresa unui string
     * producator - adresa unui string
     * pret - numar real
     */
    void adaugaProdus(const string& nume, const string& tip, const string& producator, float pret);
    /*
     * modifica produs in service
     * nume - adresa unui string
     * tip - adresa unui string
     * producator - adresa unui string
     * pret - numar real
     */
    void modificaProdus(const string& nume, const string& tip, const string& producator, float pret);
    /*
     * stergere produs in service
     * nume - adresa unui string
     * producator - adresa unui string
     */
    void stergereProdus(const string& nume, const string& producator);
    /*
     * filtrare produse dupa pret
     * pret - numar real
     */
    vector<Produs> filtrarePret(float pret);
    /*
     * filtrare produse dupa nume
     * nume - adresa unui string
     */
    vector<Produs> filtrareNume(const string& nume);
    /*
    * filtrare produse dupa producator
    * nume - adresa unui string
    */
    vector<Produs> filtrareProducator(const string& producator);
};