#include "domain.h"

int Produs::getPretProdus() const {
    return pretProdus;
}

string Produs::getNumeProdus() const {
    return numeProdus;
}

string Produs::getTipProdus() const {
    return tipProdus;
}

string Produs::getProducatorProdus() const {
    return producatorProdus;
}

void Produs::setTipProdus(const string tipProdusNou) {
    this->tipProdus = tipProdusNou;
}

void Produs::setPretProdus(const int pretProdusNou) {
    this->pretProdus = pretProdusNou;
}

void Produs::setProducatorProdus(const string producatorProdusNou) {
    this->producatorProdus = producatorProdusNou;
}