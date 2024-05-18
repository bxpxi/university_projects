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
#include <QtCore/qhash.h>

using std::vector;
using std::string;
using std::ostream;

class RepoAbstract {
public:
	virtual ~RepoAbstract() = default;

	virtual void adaugaProdus(const Produs& produs) = 0;

	virtual void stergeProdus(int pozitie) = 0;

	virtual void modificaProdus(const Produs& produsModificat) = 0;

	virtual const Produs& cautaProdus(string nume) = 0;

	virtual int cautaPozitieDupaNume(string numeProdus) const = 0;

	virtual const vector<Produs>& getAll() const noexcept = 0;
};

class Repo : public RepoAbstract {
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

	virtual int cautaPozitieDupaNume(const string numeProdus) const;

	virtual const vector<Produs>& getAll() const noexcept;

	virtual ~Repo();
};

class ExceptieRepo {

	string mesajEroare;

public:

	explicit ExceptieRepo(string mesaj) :mesajEroare{ mesaj } {}

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

	RepoFile(string numeFisier) :Repo(), numeFisier{ std::move(numeFisier) } {
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


class RepoNou : public Repo {
private:

	std::map<string, Produs> produse;
	int probabilitate;

public:

	RepoNou(int probabilitate) :Repo(), probabilitate{ probabilitate } {
	}

	virtual void adaugaProdus(const Produs& produs) override {
		int mergeSauNu = rand() % 100;
		cout << mergeSauNu << "\n";
		if (mergeSauNu < probabilitate) {
			throw ExceptieRepo("Nu vreau!\n");
		}
		if (exista(produs)) {
			throw ExceptieRepo("Produsul cu numele " + produs.getNumeProdus() + " este deja adaugat!\n");
		}
		produse.insert(make_pair(produs.getNumeProdus(), produs));
	}

	virtual void stergeProdus(int pozitie) override {
		int mergeSauNu = rand() % 100;
		cout << mergeSauNu << "\n";
		if (mergeSauNu < probabilitate)
			throw ExceptieRepo("Nu!\n");
		if (pozitie < 0 || pozitie >= produse.size()) {
			throw ExceptieRepo("Pozitie invalida!\n");
		}
		auto iterator = produse.begin();
		std::advance(iterator, pozitie);
		produse.erase(iterator);
	}

	virtual void modificaProdus(const Produs& produsModificat) override {
		int mergeSauNu = rand() % 100;
		cout << mergeSauNu << "\n";
		if (mergeSauNu < probabilitate)
			throw ExceptieRepo("Nu!\n");
		auto iterator = produse.find(produsModificat.getNumeProdus());
		if (iterator == produse.end()) {
			throw ExceptieRepo("Numele " + produsModificat.getNumeProdus() + " nu a fost gasit!\n");
		}
		iterator->second = produsModificat;
	}

	virtual const Produs& cautaProdus(string numeProdus) override {
		auto iterator = produse.find(numeProdus);
		if (iterator == produse.end()) {
			throw ExceptieRepo("Nu s-a gasit produsul cu numele " + numeProdus + "!\n");
		}
		return iterator->second;
	}

	virtual int cautaPozitieDupaNume(const string numeProdus) const override {
		auto iterator = produse.find(numeProdus);
		if (iterator == produse.end()) {
			throw ExceptieRepo("Nu exista produs cu numele " + numeProdus);
		}
		return static_cast<int>(std::distance(produse.begin(), iterator));
	}

	virtual const vector<Produs>& getAll() const noexcept override {
		static vector<Produs> vectorProduse;
		vectorProduse.clear();
		for (const auto& produs : produse) {
			vectorProduse.push_back(produs.second);
		}
		return vectorProduse;
	}

	~RepoNou() override {
	}

};
