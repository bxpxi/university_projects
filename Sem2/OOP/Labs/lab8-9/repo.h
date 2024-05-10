#pragma once
#include "domain.h"
#include <utility>
#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>

using std::vector;
using std::string;
using std::ostream;

class RepoAbstract{
public:
    virtual ~RepoAbstract()=default;

    virtual void adaugaProdus(const Produs& produs)=0;

    virtual void stergeProdus(int pozitie)=0;

    virtual void modificaProdus(const Produs& produsModificat)=0;

    virtual const Produs& cautaProdus(string nume)=0;

    [[nodiscard]] virtual int cautaPozitieDupaNume(string numeProdus) const = 0;

    [[nodiscard]] virtual const vector<Produs>& getAll() const noexcept = 0;
};

class Repo : public RepoAbstract{
protected:

    vector<Produs> produse;
    
    bool exista(const Produs& produs);

public:

    Repo() = default;

    Repo(const Repo& other) = delete;

    virtual void adaugaProdus(const Produs& produs);

    virtual void stergeProdus(int pozitie);

    virtual void modificaProdus(const Produs& produsModificat);

    virtual const Produs& cautaProdus(string nume);

    virtual int cautaPozitieDupaNume(string numeProdus) const;

    [[nodiscard]] virtual const vector<Produs>& getAll() const noexcept;

    virtual ~Repo();
};

class ExceptieRepo {

    string mesajEroare;

public:

    explicit ExceptieRepo(string mesaj) :mesajEroare{std::move( mesaj )} {}

    friend ostream& operator<<(ostream& out, const ExceptieRepo& exceptie);

    string getMesaj() { return this->mesajEroare; }

};

ostream& operator<<(ostream& out, const ExceptieRepo& exceptie);


class RepoFile :public Repo {
private:

    void readAllFromFile();
    void writeAllToFile();
    string numeFisier;
    void clearFile() {
        std::ofstream fin(numeFisier, std::ios::trunc);
        fin.close();
    }

public:

    explicit RepoFile(string numeFisier) :Repo(), numeFisier{std::move( numeFisier )} {
        readAllFromFile();
    }

    void adaugaProdus(const Produs& produs) override {
        Repo::adaugaProdus(produs);
        writeAllToFile();
    }

    void modificaProdus(const Produs& produs) override {
        Repo::modificaProdus(produs);
        writeAllToFile();
    }

    void stergeProdus(int pozitie) override {
        Repo::stergeProdus(pozitie);
        writeAllToFile();
    }

    ~RepoFile() override {
    }
};
