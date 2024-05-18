#include "cos.h"

CosCumparaturi::CosCumparaturi() {

}

void CosCumparaturi::adaugaCosCumparaturi(const Produs& produs) {
    this->cosProduse.push_back(produs);
    notifica();
}

void CosCumparaturi::golesteCosCumparaturi() {
    this->cosProduse.clear();
    notifica();
}

void CosCumparaturi::stergeProdusDinCosCumparaturi(const string& numeProdus) {
    if (cosProduse.size() == 0)
        throw "Nu exista produse introduse!\n";

    for (auto it = cosProduse.begin(); it != cosProduse.end(); ++it) {
        if (it->getNumeProdus() == numeProdus) {
            cosProduse.erase(it);
            notifica();
            return;
        }
    }

    throw "Nu s-a gasit produsul cautat!\n";
}

void CosCumparaturi::umpleRandomCosCumparaturi(size_t dimensiune, vector<Produs> listaProduse) {
    vector<Produs> listaProduseAuxiliara;
    shuffle(listaProduse.begin(), listaProduse.end(), std::default_random_engine(std::random_device{}()));
    while ((this->cosProduse.size() < dimensiune) && (!listaProduse.empty())) {
        this->cosProduse.push_back(listaProduse.back());
        listaProduseAuxiliara.push_back(listaProduse.back());
        listaProduse.pop_back();
        if (listaProduse.empty() && cosProduse.size() < dimensiune) {
            listaProduse = listaProduseAuxiliara;
            listaProduseAuxiliara.clear();
            shuffle(listaProduse.begin(), listaProduse.end(), std::default_random_engine(std::random_device{}()));
        }
    }
    notifica();
}

const vector <Produs>& CosCumparaturi::getAllCosCumparaturi() {
    return this->cosProduse;
    notifica();
}

ostream& operator<<(ostream& out, const ExceptieCosProduse& exceptie) {
    for (const auto& mesaj : exceptie.mesajEroare)
        out << mesaj;
    return out;
}

CosCumparaturi::~CosCumparaturi() {

}