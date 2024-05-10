#pragma once

#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "cos.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include "undo.h"
#include <memory>

using std::vector;
using namespace std;

class Service {
private:

    RepoAbstract& repository;
    Validator& validator;
    CosCumparaturi& cosCumparaturi;
    vector<unique_ptr<ActiuneUndo>> ActiuniUndo;

public:

    CosCumparaturi& getCosCumparaturi() {
        return cosCumparaturi;
    }

    Service(RepoAbstract& repository, Validator& validator, CosCumparaturi& cosCumparaturi) noexcept : repository{ repository }, validator{ validator }, cosCumparaturi{ cosCumparaturi } {}

    Service(const Service& other) = delete;

    void adaugaProdus(const string& numeProdus, const string& tipProdus, int pretProdus, const string& producatorProdus);

    void stergeProdus(const string& numeProdus);

    void modificaProdus(const string& numeProdus, const string& tipProdus, int pretProdus, const string& producatorProdus);

    const Produs& cautaProdus(const string& numeProdus);

    [[nodiscard]] const vector<Produs>& getAll();

    vector<Produs> filtreazaDupaTip(const string& tipProdus);

    vector<Produs> filtreazaDupaPret(int pretProdus);

    vector<Produs> sorteaza(int reperSortare, int ordineSortare);

    const vector<Produs>& adaugaProdusInCosCumparaturi(const string& numeProdus);

    const vector<Produs>& stergeProdusDinCosCumparaturi(const string& numeProdus);

    const vector<Produs>& golesteCosCumparaturi();

    const vector<Produs>& umpleRandomCosCumparaturi(int dimensiune);

    const vector<Produs>& getAllCosCumparaturi();

    void exportaInCSV(const string& numeFisier, const vector<Produs>& produse);

    void exportaInHTML(const string& numeFisier, const vector<Produs>& produse);

    void undo();

    std::unordered_map<string, vector<string>> raportSrv();

    void notifica() {
        this->cosCumparaturi.notifica();
    }

    ~Service();

};