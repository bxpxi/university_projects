#include "tests.h"
#include <cassert>
#include <sstream>

using std::ostream;
using std::stringstream;
using std::exception;

//teste repository

void test_getAll_repo() {
    ProdusRepo repo;
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    repo.adauga(Produs("Masă", "Mobilier", "Mobexpert", 500));
    repo.adauga(Produs("Lampă", "Iluminat", "Philips", 150));

    auto produse = repo.getAll();
    assert(produse.size() == 3);
    assert(produse[0].getNume() == "Scaun");
    assert(produse[1].getNume() == "Masă");
    assert(produse[2].getNume() == "Lampă");
}

void test_adauga(){
    ProdusRepo repo;
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getNume() == "Scaun");
    assert(repo.getAll()[0].getTip() == "Mobilier");
    assert(repo.getAll()[0].getProducator() == "Mobexpert");
    assert(repo.getAll()[0].getPret() == 300);
    repo.adauga(Produs("Vaza", "Decoratiuni", "Abcd", 100));
    assert(repo.getAll().size()==2);
}

void test_cauta(){
    ProdusRepo repo;
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size()==1);
    auto p1 = repo.cauta("Scaun", "Mobexpert");
    assert(p1.getNume() == "Scaun");
    assert(p1.getTip() == "Mobilier");
    assert(p1.getProducator() == "Mobexpert");
    assert(p1.getPret() == 300);
}

void test_stergere(){
    ProdusRepo repo;
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    Produs p1 = Produs("Scaun", "Mobilier", "Mobexpert", 300);
    repo.stergere(p1);
    assert(repo.getAll().empty());
    Produs p2 = Produs("Scaun", "Mobilier", "Mobexpert", 300);
}

void test_getAll_repo_fara_produse() {
    ProdusRepo repo;
    const auto& produse = repo.getAll();
    assert(produse.empty());
}


//teste service
void test_getAll(){
    ProdusRepo repo;
    MagazinService service{repo};
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size()==1);
    repo.adauga(Produs("Vaza", "Decoratiuni", "Abcd", 100));
    assert(repo.getAll().size()==2);
    vector<Produs> produse = service.getAll();
    assert(produse.size()==2);
}

void test_adaugaProdus(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    service.adaugaProdus("Scaun", "Mobilier", "Mobexpert", 300);
    assert(repo.getAll().size() == 1);
}

void test_modificaProdus(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    service.modificaProdus("Scaun", "Mobilierrr", "Mobexpert", 3000);
    auto p = repo.cauta("Scaun", "Mobexpert");
    assert(p.getPret() == 3000);
    assert(p.getTip() == "Mobilierrr");
}

void test_stergeProdus(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    service.stergereProdus("Scaun", "Mobexpert");
    assert(repo.getAll().empty());
}

void test_filtrareNume(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    repo.adauga(Produs("Lingura", "Tacamuri", "AAA", 20));
    repo.adauga(Produs("Lingura", "Tacamuri", "BBB", 15));
    vector<Produs> listaFiltrata1 = service.filtrareNume("Lingura");
    assert(listaFiltrata1.size() == 2);
    assert(listaFiltrata1[0].getPret() == 20);
    assert(listaFiltrata1[1].getPret() == 15);
    vector<Produs> listaFiltrata2 = service.filtrareNume("Masa");
    assert(listaFiltrata2.empty());
}

void test_filtrareProducator(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 300));
    assert(repo.getAll().size() == 1);
    repo.adauga(Produs("Lingura", "Tacamuri", "AAA", 20));
    repo.adauga(Produs("Farfurie", "Tacamuri", "AAA", 15));
    vector<Produs> listaFiltrata1 = service.filtrareProducator("AAA");
    assert(listaFiltrata1.size() == 2);
    assert(listaFiltrata1[0].getPret() == 20);
    assert(listaFiltrata1[1].getPret() == 15);
    vector<Produs> listaFiltrata2 = service.filtrareProducator("BBB");
    assert(listaFiltrata2.empty());
}

void test_filtrarePret(){
    ProdusRepo repo;
    MagazinService service{repo};
    assert(repo.getAll().empty());
    repo.adauga(Produs("Scaun", "Mobilier", "Mobexpert", 100));
    assert(repo.getAll().size() == 1);
    repo.adauga(Produs("Lingura", "Tacamuri", "AAA", 100));
    repo.adauga(Produs("Lingura", "Tacamuri", "BBB", 15));
    vector<Produs> listaFiltrata1 = service.filtrarePret(100);
    assert(listaFiltrata1.size() == 2);
    assert(listaFiltrata1[0].getTip() == "Mobilier");
    assert(listaFiltrata1[1].getTip() == "Tacamuri");
    vector<Produs> listaFiltrata2 = service.filtrarePret(400);
    assert(listaFiltrata2.empty());
}



void test_all(){
    //teste repository
    test_adauga();
    test_cauta();
    test_stergere();
    test_getAll_repo();
    //teste service
    test_adaugaProdus();
    test_getAll_repo_fara_produse();
    test_getAll();
    test_modificaProdus();
    test_stergeProdus();
    test_filtrareNume();
    test_filtrareProducator();
    test_filtrarePret();
}