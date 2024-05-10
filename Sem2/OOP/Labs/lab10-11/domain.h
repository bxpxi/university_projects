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

    void setTipProdus(string tipProdusNou);

    void setPretProdus(int pretProdusNou);

    void setProducatorProdus(string producatorProdusNou);

    Produs() : numeProdus(), tipProdus(), pretProdus(0), producatorProdus() {}

    Produs(string  numeProdus, string  tipProdus, const int pretProdus, string  producatorProdus) : numeProdus{ std::move(numeProdus) }, tipProdus{ std::move(tipProdus) }, pretProdus{ pretProdus }, producatorProdus{ std::move(producatorProdus) } {}

    Produs(const Produs& other) :numeProdus{ other.numeProdus }, tipProdus{ other.tipProdus }, pretProdus{ other.pretProdus }, producatorProdus{ other.producatorProdus } {
        //cout << "!!!!!!!!!!!!!!!!!!!!\n";
    }

};