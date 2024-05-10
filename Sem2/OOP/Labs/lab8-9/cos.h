#pragma once

#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
using std::shuffle;

class CosCumparaturi /*: public Observabil*/ {

private:

    vector<Produs> cosProduse;

public:

    CosCumparaturi();

    void adaugaCosCumparaturi(const Produs& produs);

    void golesteCosCumparaturi();

    void umpleRandomCosCumparaturi(size_t dimensiune, vector<Produs> listaProduse);

    const vector <Produs>& getAllCosCumparaturi();

    void stergeProdusDinCosCumparaturi(const string& numeProdus);

    ~CosCumparaturi();

};