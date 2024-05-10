#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//complexitate theta(1)
MDO::MDO(Relatie r) {
    relatie = r;
    prim = nullptr;
    ultim = nullptr;
}

//complexitate theta(n)
void MDO::adauga(TCheie c, TValoare v) {
    //caut in functie de cheie pentru a sti unde sa adaug
    Nod* p = prim;
    while (p != nullptr && relatie(p->e.first, c))
        p = p->urmator;

    // verific daca exista deja elemetul cu acesta cheie si aceasta valoare
    if (p != nullptr && p->e.first == c && p->e.second == v)
        return;

    Nod* nodNou = new Nod{TElem(c, v), nullptr, nullptr};
    if (p == nullptr) {
        // adaug la sfarsitul listei
        if (ultim != nullptr) {
            ultim->urmator = nodNou;
            nodNou->anterior = ultim;
        } else {
            prim = nodNou;
        }
        ultim = nodNou;
    } else if (p->anterior != nullptr) {
        // adaug intre doua noduri oarecare din lista
        p->anterior->urmator = nodNou;
        nodNou->anterior = p->anterior;
        nodNou->urmator = p;
        p->anterior = nodNou;
    } else {
        // adaug la inceputul listei
        nodNou->urmator = prim;
        prim->anterior = nodNou;
        prim = nodNou;
    }
}

//complexitate theta(n)
vector<TValoare> MDO::cauta(TCheie c) const {
    vector<TValoare> rezultat;

    Nod* p = prim;
    while (p != nullptr && relatie(p->e.first, c))
    {
        if (p->e.first == c)
            rezultat.push_back(p->e.second);
        p = p->urmator;
    }

    return rezultat;
}

//complexitate theta(n)
bool MDO::sterge(TCheie c, TValoare v) {
    Nod* p = prim;
    while (p != nullptr && relatie(p->e.first, c)) {
        if (p->e.first == c && p->e.second == v) {
            if (p->anterior != nullptr)
                p->anterior->urmator = p->urmator;
            else
                prim = p->urmator;
            if (p->urmator != nullptr)
                p->urmator->anterior = p->anterior;
            else
                ultim = p->anterior;
            delete p;
            return true;
        }
        p = p->urmator;
    }
    return false;

}

//complexitate theta(n)
int MDO::dim() const {
    int dimensiune = 0;
    Nod* p = prim;
    while (p != nullptr) {
        dimensiune++;
        p = p->urmator;
    }
    return dimensiune;
}

//complexitate theta(1)
bool MDO::vid() const {
    return prim == nullptr;
}

//complexitate theta(1)
IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

//complexitate theta(n)
MDO::~MDO() {
    Nod* p = prim;
    while (p != nullptr) {
        Nod* temp = p;
        p = p->urmator;
        delete temp;
    }
    prim = nullptr;
    ultim = nullptr;
}
