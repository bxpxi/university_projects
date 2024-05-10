#pragma once
#include "service.h"
#include "domain.h"

class UI {
private:

    Service& service;

    void ui_adaugaProdus();

    void ui_stergeProdus();

    void ui_modificaProdus();

    void ui_afiseazaProduse(const vector<Produs>& produse);

    void ui_cautaProdus();

    void ui_filtrare();

    void ui_raport();

    void ui_sortare();

    void ui_adaugaProdusInCosCumparaturi();

    void ui_stergeProdusDinCosCumparaturi();

    void ui_umpleRandomCosCumparaturi();

    void ui_exportaInFisier();

    void ui_undo();

public:
    explicit UI(Service& service) :service{ service } {}
    //nu permitem copierea obiectelor
    UI(const UI& other) = delete;

    ~UI();

    void ui_meniu();

    void ruleaza();

};