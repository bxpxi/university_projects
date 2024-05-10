#pragma once
#include "service.h"
#include "domain.h"

class Consola {
    MagazinService& service;
    //adauga produs in ui
    void adaugaUI();
    //afisare lista de produse in ui
    //produse - vector de elemente de tip Produs
    static void afisareUI(const std::vector<Produs>& produse);
    //modifica produs in ui
    void modificaUI();
    //modifica stergere in ui
    void stergereUI();
    //filtrare lista de produse dupa nume in ui
    void filtrareNumeUI();
    //filtrare lista de produse dupa producator in ui
    void filtrareProducatorUI();
    //filtrare lista de produse dupa pret in ui
    void filtrarePretUI();
public:
    explicit Consola(MagazinService& service): service{service} {}
    Consola(const Consola& pt) = delete;

    void run();
};