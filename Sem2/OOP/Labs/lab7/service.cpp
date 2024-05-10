#include "service.h"
#include <cassert>
#include <utility>
#include <vector>
#include <algorithm>

using std::sort;

void Magazin::addProdus(string denumire, int pret, string tip, string producator) {
    Produs p{std::move(denumire), pret, std::move(tip), std::move(producator)};
    val.valideaza(p);
    repo.store(p);
}

void Magazin::modifyProdus(const string& denumire, int pretNou, string tipNou, string producatorNou) {
    if(search(denumire).getDenumire() != denumire)
        throw RepoException("\nProdusul nu exista!\n");

    Produs p{denumire, pretNou, std::move(tipNou), std::move(producatorNou)};
    val.valideaza(p);
    repo.modify(p);
}

const Produs& Magazin::search(const string& denumire) {
    return repo.find(denumire);
}

void Magazin::deleteProdus(const string& denumire) {
    if(search(denumire).getDenumire() != denumire)
        throw RepoException("\nProdusul nu exista!\n");
    repo.deleteProdus(denumire);
}

vector<Produs> Magazin::generalSort(bool (*maiMicF)(const Produs &, const Produs &)) {
    vector<Produs> v{repo.getallProduse()};
    for(size_t i=0;i<v.size();i++){
        for(size_t j=i+1;j<v.size();j++){
            if(!maiMicF(v[i], v[j])){
                Produs aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    return v;
}

vector<Produs> Magazin::filter(const function<bool(const Produs&)>& fct){
    vector<Produs> filteredProduse;
    for(const auto& produs : repo.getallProduse()){
        if(fct(produs))
            filteredProduse.push_back(produs);
    }
    return filteredProduse;
}

vector<Produs> Magazin::filtrarePret(int pret) {
    return filter([pret](const Produs& p){
        return p.getPret() == pret;
    });
}

vector<Produs> Magazin::filtrareProducator(const string& producator) {
    return filter([producator](const Produs& p){
        return p.getProducator() == producator;
    });
}

vector<Produs> Magazin::sortByPret() {
    return generalSort(cmpPret);
}

vector<Produs> Magazin::sortByDenumire() {
    return generalSort(cmpDenumire);
}

vector<Produs> Magazin::sortByTip() {
    return generalSort(cmpTip);
}

void testAddService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 2500, "microfibra", "dormeo");
    testService.addProdus("covor", 400, "mic", "jysk");
    testService.addProdus("canapea", 4500, "confort", "mobexpert");

    assert(testService.getAllProduse().size() == 3);

    try{
        testService.addProdus("saltea", 1000, "spuma", "dormeo");
    }
    catch(RepoException&){
        assert(true);
    }

    try{
        testService.addProdus("", 200, "mic","lems");
        assert(false);
    }
    catch (ValidationException& ve){
        assert(ve.getErrorMessages() == "Denumire invalida!\n");
    }

    try{
        testService.addProdus("saltea", -1, "mic","lems");
        assert(false);
    }
    catch (ValidationException& ve){
        assert(ve.getErrorMessages() == "Pret invalid!\n");
    }

    try{
        testService.addProdus("saltea", 200, "","lems");
        assert(false);
    }
    catch (ValidationException& ve){
        assert(ve.getErrorMessages() == "Tip invalid!\n");
    }

    try{
        testService.addProdus("saltea", 200, "mic","");
        assert(false);
    }
    catch (ValidationException& ve){
        assert(ve.getErrorMessages() == "Producator invalid!\n");
    }
}

void testModifyService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 2500, "spuma", "dormeo");
    assert(testService.getAllProduse().size() == 1);

    testService.modifyProdus("saltea", 2000, "microfibra", "jysk");

    auto found = testService.search("saltea");
    assert(found.getProducator() == "jysk");
    assert(found.getPret() == 2000);
    assert(found.getTip() == "microfibra");

    try{
        testService.modifyProdus("covor", 400, "mediu", "jysk");
    }
    catch (RepoException&){
        assert(true);
    }
}


void testDeleteService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 2500, "spuma", "dormeo");
    assert(testService.getAllProduse().size() == 1);

    try{
        testService.deleteProdus("covor");
    }
    catch (RepoException&){
        assert(true);
    }

    testService.deleteProdus("saltea");
    assert(testService.getAllProduse().empty());
}

void testFindService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 2500, "spuma", "dormeo");
    assert(testService.getAllProduse().size() == 1);

    auto found = testService.search("saltea");
    assert(found.getPret() == 2500);
    assert(found.getProducator() == "dormeo");
    assert(found.getTip() == "spuma");

    try{
        testService.search("covor");
    }
    catch (RepoException&){
        assert(true);
    }
}

void testFilerService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 4500, "microfibra", "jysk");
    testService.addProdus("covor", 400, "mic", "jysk");
    testService.addProdus("canapea", 4500, "confort", "mobexpert");

    assert(testService.getAllProduse().size() == 3);

    vector<Produs> Produse2 = testService.filtrarePret(4500);
    assert(Produse2.size() == 2);
    vector<Produs> Produse0 = testService.filtrarePret(8000);
    assert(Produse0.empty());

    vector<Produs> produseProd2 = testService.filtrareProducator("jysk");
    assert(produseProd2.size() == 2);
    vector<Produs> produseProd0 = testService.filtrareProducator("dorna");
    assert(produseProd0.empty());
}

void testSortService(){
    ProdusRepository testRepo;
    ProdusValidator testVal;
    Magazin testService{testRepo, testVal};

    testService.addProdus("saltea", 3500, "microfibra", "jysk");
    testService.addProdus("covor", 400, "mic", "jysk");
    testService.addProdus("canapea", 4500, "confort", "mobexpert");

    assert(testService.getAllProduse().size() == 3);

    vector<Produs> sortedByDenumire = testService.sortByDenumire();
    assert(sortedByDenumire[0].getDenumire() == "canapea");

    vector<Produs> sortedByPret = testService.sortByPret();
    assert(sortedByPret[0].getDenumire() == "covor");
    assert(sortedByPret[1].getDenumire() == "saltea");
    assert(sortedByPret[2].getDenumire() == "canapea");

    vector<Produs> sortedByTip = testService.sortByTip();
    assert(sortedByTip[0].getDenumire() == "canapea");
    assert(sortedByTip[1].getDenumire() == "covor");
    assert(sortedByTip[2].getDenumire() == "saltea");
}

void testeService(){
    testAddService();
    testModifyService();
    testDeleteService();
    testFindService();
    testFilerService();
    testSortService();
}