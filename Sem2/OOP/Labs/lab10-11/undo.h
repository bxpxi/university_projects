#pragma once
#include "domain.h"
#include "repo.h"
#include <vector>
#include <functional>
#include <fstream>

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Produs produsDeSters;
    RepoAbstract& repository;
public:
    UndoAdauga(const Produs produs, RepoAbstract& repo) : produsDeSters{ produs }, repository{ repo } {}
    void doUndo() override {
        repository.stergeProdus(repository.cautaPozitieDupaNume(produsDeSters.getNumeProdus()));
    }
};

class UndoSterge :public ActiuneUndo {
private:
    Produs produsDeAdaugat;
    RepoAbstract& repository;
public:
    UndoSterge(const Produs produs, RepoAbstract& repo) : produsDeAdaugat{ produs }, repository{ repo } {}
    void doUndo() override {
        repository.adaugaProdus(produsDeAdaugat);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Produs produsDeModificat;
    RepoAbstract& repository;
public:
    UndoModifica(const Produs produs, RepoAbstract& repo) : produsDeModificat{ produs }, repository{ repo } {}
    void doUndo() override {
        repository.stergeProdus(repository.cautaPozitieDupaNume(produsDeModificat.getNumeProdus()));
        repository.adaugaProdus(produsDeModificat);
    }
};