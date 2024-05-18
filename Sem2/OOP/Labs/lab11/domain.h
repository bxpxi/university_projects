#pragma once
#include <iostream>
#include <string>
#include <utility>
using std::string;
using std::cout;

class Produs {

private:

    string numeProdus;
    string tipProdus;
    int pretProdus;
    string producatorProdus;

public:

    int getPretProdus() const;

    string getNumeProdus() const;

    string getTipProdus() const;

    string getProducatorProdus() const;

    void setTipProdus(const string tipProdusNou);

    void setPretProdus(const int pretProdusNou);

    void setProducatorProdus(const string producatorProdusNou);

    Produs() : numeProdus(), tipProdus(), pretProdus(0), producatorProdus() {}

    Produs(const string  numeProdus, const string  tipProdus, const int pretProdus, const string  producatorProdus) : numeProdus{ numeProdus }, tipProdus{ tipProdus }, pretProdus{ pretProdus }, producatorProdus{ producatorProdus } {}

    Produs(const Produs& other) :numeProdus{ other.numeProdus }, tipProdus{ other.tipProdus }, pretProdus{ other.pretProdus }, producatorProdus{ other.producatorProdus } {
        //cout << "!!!!!!!!!!!!!!!!!!!!\n";
    }

};