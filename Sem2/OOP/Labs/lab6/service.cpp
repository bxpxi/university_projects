#include <string>
#include "service.h"

vector<Produs> MagazinService::filtrare(const function<bool(const Produs&)>& fct){
    vector<Produs> rez;
    for(const auto& produs:Repo.getAll())
        if(fct(produs))
            rez.push_back(produs);
    return (rez);
}

void MagazinService::adaugaProdus(const std::string &nume, const std::string &tip, const std::string &producator, float pret) {
    Produs p{nume, tip, producator, pret};
    Repo.adauga(p);
}

void MagazinService::modificaProdus(const string& nume, const string& tip, const string& producator, float pret) {
    Produs p = Repo.cauta(nume, producator);
    Repo.stergere(p);
    Produs new_p{nume, tip, producator, pret};
    Repo.adauga(new_p);
}

void MagazinService::stergereProdus(const string& nume, const string& producator) {
    Produs p = Repo.cauta(nume, producator);
    Repo.stergere(p);
}

vector<Produs> MagazinService::filtrareNume(const string& nume) {
    return filtrare([nume](const Produs& p){
        return p.getNume() == nume;
    });
}

vector<Produs> MagazinService::filtrareProducator(const string& producator) {
    return filtrare([producator](const Produs& p){
        return p.getProducator() == producator;
    });
}

vector<Produs> MagazinService::filtrarePret(float pret) {
    return filtrare([pret](const Produs& p){
        return p.getPret() == pret;
    });
}

