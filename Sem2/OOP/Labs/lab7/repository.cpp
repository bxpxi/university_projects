#include "repository.h"
#include <cassert>

bool ProdusRepository::exists(const Produs &p) {
    try{
        find(p.getDenumire());
        return true;
    }
    catch(RepoException&){
        return false;
    }
}

const Produs& ProdusRepository::find(const string& denumire) {
    for(const Produs& p : this->allProduse)
        if(p.getDenumire() == denumire)
            return p;
    throw RepoException("Produsul nu exista!");
}

void ProdusRepository::store(const Produs &p) {
    if(exists(p))
        throw RepoException("Produsul exista deja!");
    this->allProduse.add(p);
}

void ProdusRepository::deleteProdus(const string& denumire) {
    for(int i=0;i<allProduse.size();i++){
        if(allProduse.get(i).getDenumire() == denumire){
            for(int j=i;j<allProduse.size();j++)
                allProduse.set(allProduse.get(j+1), j);
            allProduse.sters();
            return;
        }
    }
}

void ProdusRepository::modify(const Produs& p) {
    for(auto& i : allProduse)
        if(i.getDenumire() == p.getDenumire()){
            i.setProducator(p.getProducator());
            i.setPret(p.getPret());
            i.setTip(p.getTip());
            return;
        }
    throw RepoException("Produsul nu exista!");
}

vector<Produs> ProdusRepository::getallProduse() {
    vector<Produs> produse;
    for(const auto& produs : this->allProduse)
        produse.push_back(produs);
    return produse;
}

void testAddRepo(){
    ProdusRepository testRepo;
    Produs p1{"apa", 4, "plata", "dorna"};
    testRepo.store(p1);
    assert(testRepo.getallProduse().size() == 1);
    Produs p2{"apa", 5, "plata", "dorna"};
    try{
        testRepo.store(p2);
    }
    catch(RepoException&){
        assert(true);
    }
}

void testFindRepo(){
    ProdusRepository testRepo;
    Produs p1{"televizor", 4000, "led", "sony"};
    Produs p2{"laptop", 3500, "mic", "lenovo"};
    Produs p3{"telefon", 4500, "smartphone", "samsung"};
    testRepo.store(p1);
    testRepo.store(p2);

    assert(testRepo.exists(p1));
    assert(!testRepo.exists(p3));

    auto found = testRepo.find("televizor");
    assert(found.getPret() == 4000);
    assert(found.getTip() == "led");
    assert(found.getProducator() == "sony");

    try{
        testRepo.find("masina");
    }
    catch (RepoException& ve){
        assert(ve.getErrorMessage() == "Produsul nu exista!");
    }
}

void testModifyRepo(){
    ProdusRepository testRepo;
    Produs p1{"saltea", 2500, "microfibra", "dormeo"};
    testRepo.store(p1);
    assert(testRepo.getallProduse().size() == 1);

    try{
        Produs p{"covor", 500, "mare", "dedeman"};
        testRepo.modify(p);
    }
    catch (RepoException& ve){
        assert(ve.getErrorMessage() == "Produsul nu exista!");
    }

    Produs pmodif{"saltea", 2500, "spuma", "jysk"};
    testRepo.modify(pmodif);

    auto found = testRepo.find("saltea");
    assert(found.getPret() == 2500);
    assert(found.getTip() == "spuma");
    assert(found.getProducator() == "jysk");
}

void testDeleteRepo(){
    ProdusRepository testRepo;
    Produs p1{"saltea", 2500, "microfibra", "dedeman"};
    testRepo.store(p1);
    assert(testRepo.getallProduse().size() == 1);

    try{
        testRepo.deleteProdus("covor");
    }
    catch (RepoException& ve){
        assert(ve.getErrorMessage() == "Produsul nu exista!");
    }

    testRepo.deleteProdus("saltea");
    assert(testRepo.getallProduse().empty());
}

void testRepo(){
    testAddRepo();
    testFindRepo();
    testModifyRepo();
    testDeleteRepo();
}



