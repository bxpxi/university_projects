#pragma once

#include "domain.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;

class ValidationException{
    vector<string> errorMsg;
public:
    explicit ValidationException(vector<string> errorMessages): errorMsg{std::move(errorMessages)} {};

    string getErrorMessages(){
        string fullMsg;
        for(const string& e : errorMsg)
            fullMsg += e + '\n';
        return fullMsg;
    }
};

/*
Clasa pentru validarea produselor
Un produs este valid daca:
	are denumirea formata din mai mult de 1 caractere
	pretul este mai mare de 0
	are tipul format din mai mult de 1 caractere
	are producatorul format din mai mult de 1 caractere
*/
class ProdusValidator{
public:
    static void valideaza(const Produs& p){
        vector<string> errors;
        if(p.getDenumire().empty())
            errors.push_back("Denumire invalida!");
        if(p.getPret() <= 0)
            errors.push_back("Pret invalid!");
        if(p.getTip().empty())
            errors.push_back("Tip invalid!");
        if(p.getProducator().empty())
            errors.push_back("Producator invalid!");

        if(!errors.empty())
            throw ValidationException(errors);
    }
};