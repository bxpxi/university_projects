#include "service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

void Service::adaugaProdus(const std::string& numeProdus, const std::string& tipProdus, const int pretProdus,
    const std::string& producatorProdus) {
    const Produs produs{ numeProdus, tipProdus, pretProdus, producatorProdus };
    Validator::valideaza(produs);
    repository.adaugaProdus(produs);
    ActiuniUndo.push_back(std::make_unique<UndoAdauga>(produs, this->repository));
}

void Service::stergeProdus(const std::string& numeProdus) {
    const int pozitie = repository.cautaPozitieDupaNume(numeProdus);
    const Produs produs = repository.cautaProdus(numeProdus);
    repository.stergeProdus(pozitie);
    ActiuniUndo.push_back(std::make_unique<UndoSterge>(produs, this->repository));
}

void Service::modificaProdus(const std::string& numeProdus, const std::string& tipProdus, int pretProdus,
    const std::string& producatorProdus) {
    const Produs produsModificat{ numeProdus, tipProdus, pretProdus, producatorProdus };
    Validator::valideaza(produsModificat);
    const Produs produsAnterior = repository.cautaProdus(numeProdus);
    repository.modificaProdus(produsModificat);
    ActiuniUndo.push_back(std::make_unique<UndoModifica>(produsAnterior, this->repository));
}

const vector<Produs>& Service::getAll() {
    return repository.getAll();
}

const Produs& Service::cautaProdus(const std::string& numeProdus) {
    return repository.cautaProdus(numeProdus);
}

vector<Produs> Service::filtreazaDupaTip(const std::string& tipProdus) {
    const vector<Produs>& produse = repository.getAll();
    vector<Produs> produseFiltrate(produse.size());
    auto iterator = copy_if(produse.begin(), produse.end(), produseFiltrate.begin(), [tipProdus](const Produs& film) {
        return film.getTipProdus() == tipProdus;
        });
    produseFiltrate.resize(distance(produseFiltrate.begin(), iterator));
    return produseFiltrate;
}

std::unordered_map<string, vector<string>> Service::raportSrv() {
    std::unordered_map<string, vector<string>> tipuri;
    vector<Produs> produse = getAll();
    for (const auto& produs : produse) {
        tipuri[produs.getTipProdus()].push_back(produs.getNumeProdus());
    }
    return tipuri;
}

vector<Produs> Service::filtreazaDupaPret(int pretProdus) {
    const vector<Produs>& produse = repository.getAll();
    vector<Produs> produseFiltrate(produse.size());
    auto iterator = copy_if(produse.begin(), produse.end(), produseFiltrate.begin(), [pretProdus](const Produs& film) {
        return film.getPretProdus() == pretProdus;
        });
    produseFiltrate.resize(distance(produseFiltrate.begin(), iterator));
    return produseFiltrate;
}

bool comparareDupaNumeCrescator(const Produs& produs1, const Produs& produs2) {
    return produs1.getNumeProdus() < produs2.getNumeProdus();
}

bool comparareDupaProducatorCrescator(const Produs& produs1, const Produs& produs2) {
    return produs1.getProducatorProdus() < produs2.getProducatorProdus();
}

bool comparareDupaTipSiPretCrescator(const Produs& produs1, const Produs& produs2) {
    if (produs1.getPretProdus() == produs2.getPretProdus())
        return produs1.getTipProdus() < produs2.getTipProdus();
    return produs1.getPretProdus() < produs2.getPretProdus();
}

bool comparareDupaNumeDescrescator(const Produs& produs1, const Produs& prdus2) {
    return produs1.getNumeProdus() > prdus2.getNumeProdus();
}

bool comparareDupaProducatorDescrescator(const Produs& produs1, const Produs& produs2) {
    return produs1.getProducatorProdus() > produs2.getProducatorProdus();
}

bool comparareDupaTipSiPretDescrescator(const Produs& produs1, const Produs& produs2) {
    if (produs1.getPretProdus() == produs2.getPretProdus())
        return produs1.getTipProdus() > produs2.getTipProdus();
    return produs1.getPretProdus() > produs2.getPretProdus();
}

vector<Produs> Service::sorteaza(int reperSortare, int ordineSortare) {

    vector<Produs> filme = repository.getAll();

    bool(*functieDeComparare)(const Produs & film1, const Produs & film2) { comparareDupaProducatorCrescator };

    if (reperSortare == 1) {
        if (ordineSortare == 1)
            functieDeComparare = comparareDupaNumeCrescator;
        else
            functieDeComparare = comparareDupaNumeDescrescator;
    }
    else if (reperSortare == 2) {
        if (ordineSortare == 1)
            functieDeComparare = comparareDupaProducatorCrescator;
        else
            functieDeComparare = comparareDupaProducatorDescrescator;
    }
    else if (reperSortare == 3) {
        if (ordineSortare == 1)
            functieDeComparare = comparareDupaTipSiPretCrescator;
        else
            functieDeComparare = comparareDupaTipSiPretDescrescator;
    }

    sort(filme.begin(), filme.end(), functieDeComparare);
    return filme;
}

void Service::undo() {
    if (ActiuniUndo.empty()) { throw ExceptieRepo{ "Nu mai este undo de facut!\n" }; }
    ActiuniUndo.back()->doUndo();
    ActiuniUndo.pop_back();
}

const vector<Produs>& Service::adaugaProdusInCosCumparaturi(const std::string& numeProdus) {
    int produsDejaAdaugat = 0;
    const vector<Produs>& produse = getAllCosCumparaturi();
    const Produs& produsCautat = this->repository.cautaProdus(numeProdus);
    for (const auto& produs : produse)
        if (produs.getNumeProdus() == numeProdus) {
            produsDejaAdaugat = 1;
            break;
        }
    if (!produsDejaAdaugat)
        this->cosCumparaturi.adaugaCosCumparaturi(produsCautat);
    return this->cosCumparaturi.getAllCosCumparaturi();
}

const vector<Produs>& Service::stergeProdusDinCosCumparaturi(const std::string& numeProdus) {
    this->cosCumparaturi.stergeProdusDinCosCumparaturi(numeProdus);
    return this->cosCumparaturi.getAllCosCumparaturi();
}

const vector<Produs>& Service::golesteCosCumparaturi() {
    this->cosCumparaturi.golesteCosCumparaturi();
    return this->cosCumparaturi.getAllCosCumparaturi();
}

const vector<Produs>& Service::umpleRandomCosCumparaturi(int dimensiune) {
    this->cosCumparaturi.umpleRandomCosCumparaturi(dimensiune, this->repository.getAll());
    return this->cosCumparaturi.getAllCosCumparaturi();
}

const vector<Produs>& Service::getAllCosCumparaturi() {
    return this->cosCumparaturi.getAllCosCumparaturi();
}

void Service::exportaInCSV(const string& numeFisier, const vector<Produs>& produse) {
    std::ofstream fout(numeFisier, std::ios::trunc);
    if (!fout.is_open()) { throw ExceptieRepo("Fisierul cu numele " + numeFisier + " nu a putut fi deschis!\n"); }
    for (const auto& produs : produse) {
        fout << produs.getNumeProdus() << "," << produs.getTipProdus() << "," << produs.getPretProdus() << "," << produs.getProducatorProdus() << "\n";
    }
    fout.close();
}

void Service::exportaInHTML(const string& numeFisier, const vector<Produs>& produse) {
    std::ofstream fout(numeFisier);
    if (!fout.is_open()) { throw ExceptieRepo("Fisierul cu numele " + numeFisier + " nu a putut fi deschis!\n"); }
    fout << "<html><body>\n";
    fout << "<table border=\"1\" style=\"width:100 % \">\n";
    for (const auto& produs : produse) {
        fout << "<tr>\n";
        fout << "<td>" << produs.getNumeProdus() << "</td>\n";
        fout << "<td>" << produs.getTipProdus() << "</td>\n";
        fout << "<td>" << produs.getPretProdus() << "</td>\n";
        fout << "<td>" << produs.getProducatorProdus() << "</td>\n";
        fout << "</tr>\n";
    }
    fout << "</table>\n";
    fout << "</body></html>\n";
    fout.close();
}


Service::~Service()
{
}