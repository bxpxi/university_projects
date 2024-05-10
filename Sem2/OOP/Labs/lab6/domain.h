#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Produs {
    string Nume;
    string Tip;
    string Producator;
    float Pret;

public:
    /*Produs(const string& nume, const string& tip, const string& producator, float pret){
        Nume = nume;
        Tip =tip;
        Producator = producator;
        Pret = pret;
    }

    Produs(const string& nume, const string& tip, const string& producator, float pret)
            : Nume(nume), Tip(tip), Producator(producator), Pret(pret) {}
    */

    Produs(string nume, string tip, string producator, float pret)
            : Nume(std::move(nume)), Tip(std::move(tip)), Producator(std::move(producator)), Pret(pret) {}



    //Produs(const Produs& p) = default;

    Produs(const Produs& p):Nume{p.Nume}, Tip{p.Tip}, Producator{p.Producator}, Pret{p.Pret} {
        cout<<"copy constructor\n";
    }


    //getters
    [[nodiscard]] std::string getNume() const{
        return Nume;
    }

    [[nodiscard]] std::string getTip() const{
        return Tip;
    }

    [[nodiscard]] std::string getProducator() const{
        return Producator;
    }

    [[nodiscard]]float getPret() const{
        return Pret;
    }
};

