#pragma once
#include<iostream>
#include<string>
#include <utility>

using std::cout;
using std::string;
using std::endl;

class Produs{
private:
    string denumire;
    int pret=0;
    string tip;
    string producator;

public:
    Produs() = default;
    //Produs(string denumire, int pret, string tip, string producator): denumire{denumire}, pret{pret}, tip{tip}, producator{producator} {};
    Produs(string denumire, int pret, string tip, string producator)
            : denumire(std::move(denumire)), pret(pret), tip(std::move(tip)), producator(std::move(producator)) {}
    //Produs(const Produs& ot): denumire{ot.denumire}, pret{ot.pret}, tip{ot.tip}, producator{ot.producator} {};
    Produs(const Produs& ot) = default;

    [[nodiscard]]string getDenumire() const;
    [[nodiscard]] int getPret() const;
    [[nodiscard]] string getTip() const;
    [[nodiscard]] string getProducator() const;

    void setPret(int pretNou);
    void setTip(string tipNou);
    void setProducator(string producatorNou);
};

bool cmpPret(const Produs& p1, const Produs& p2);

bool cmpDenumire(const Produs& p1, const Produs& p2);

bool cmpTip(const Produs& p1, const Produs& p2);

void testeDomain();