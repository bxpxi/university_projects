#pragma once
#include "domain.h"
#include <ostream>
#include <string>
#include <vector>
#include <utility>

using std::vector;
using std::string;
using std::ostream;

class ProdusRepo {
    vector <Produs> all;

public:
    ProdusRepo() = default;
    ProdusRepo(const ProdusRepo& p) = delete;

    //adaugare produs
    //p - adresa unui Produs
    void adauga(const Produs& p);

    //stergere produs
    //p - adresa unui Produs
    void stergere(Produs& p);

    //cautare produs
    //nume - adresa unui string
    //producator - adresa unui string
    [[nodiscard]]const Produs& cauta(const string& nume, const string& producator) const;

    //getAll produse
    [[nodiscard]]const vector<Produs>& getAll() const noexcept;
};
