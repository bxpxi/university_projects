#include "domain.h"
//#include <assert.h>
#include <cassert>
#include <utility>

string Produs::getDenumire() const{
    return this->denumire;
}

int Produs::getPret() const{
    return this->pret;
}

string Produs::getTip() const{
    return this->tip;
}

string Produs::getProducator() const{
    return this->producator;
}

void Produs::setPret(int pretNou){
    this->pret = pretNou;
}

void Produs::setTip(string tipNou){
    this->tip = std::move(tipNou);
}

void Produs::setProducator(string producatorNou){
    this->producator = std::move(producatorNou);
}

bool cmpDenumire(const Produs& p1, const Produs& p2){
    return p1.getDenumire() < p2.getDenumire();
}

bool cmpPret(const Produs& p1, const Produs& p2){
    return p1.getPret() < p2.getPret();
}

bool cmpTip(const Produs& p1, const Produs& p2){
    if(p1.getTip() == p2.getTip())
        return p1.getDenumire() < p2.getDenumire();
    else
        return p1.getTip() < p2.getTip();
}

void testGetSet(){
    Produs p1{"apa",4,"plata","borsec"};
    assert(p1.getDenumire() == "apa");
    assert(p1.getPret() == 4);
    assert(p1.getTip() == "plata");
    assert(p1.getProducator() == "borsec");

    p1.setPret(5);
    p1.setTip("minerala");
    p1.setProducator("dorna");

    assert(p1.getTip() == "minerala");
    assert(p1.getPret() == 5);
    assert(p1.getProducator() == "dorna");
}

void testCMP(){
    Produs p1{"apa", 4, "plata", "dorna"};
    Produs p2{"apa", 5, "minerala", "dorna"};
    Produs p3{"suc", 4, "natural", "prigat"};

    assert(cmpDenumire(p1, p3) == true);
    assert(cmpPret(p2, p3) == false);
    assert(cmpTip(p1, p2) == false);
    assert(cmpTip(p1, p3) == false);
}

void testeDomain(){
    testGetSet();
    testCMP();
}