#pragma once

#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ostream>
#include <string>
#include <functional>
#include <fstream>
#include <iostream>
#include "observator.h"

using std::vector;
using std::shuffle;
using std::ostream;

class CosCumparaturi : public Observabil {

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

class ExceptieCosProduse {

    string mesajEroare;

public:

    ExceptieCosProduse(string mesaj) :mesajEroare{ mesaj } {}

    friend ostream& operator<<(ostream& out, const ExceptieCosProduse& exceptie);

    string getMesaj() { return this->mesajEroare; }

};

ostream& operator<<(ostream& out, const ExceptieCosProduse& exceptie);