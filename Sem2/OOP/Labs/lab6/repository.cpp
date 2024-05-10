#include "repository.h"

#include <iostream>
#include <sstream>
#include <vector>

using std::stringstream;
using std::cout;

void ProdusRepo::adauga(const Produs& p) {
    all.push_back(p);
}

void ProdusRepo::stergere(Produs& p){
    for(unsigned int i=0; i<all.size();i++)
        if(all[i].getNume() == p.getNume())
            all.erase(all.begin()+i);
}

const Produs& ProdusRepo::cauta(const string& nume, const string& producator) const {
    static const Produs produs_default("-", "-", "-", 0.0);
    for(const auto& p:all){
        if(p.getNume() == nume && p.getProducator() == producator)
            return p;
    }
    return produs_default;
}

const vector<Produs>& ProdusRepo::getAll() const noexcept {
    return all;
}
