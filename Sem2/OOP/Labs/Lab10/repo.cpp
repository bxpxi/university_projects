#include "repo.h"

void Repo::adaugaProdus(const Produs& produs) {
    if (exista(produs)) {
        throw ExceptieRepo("Produsul cu numele " + produs.getNumeProdus() + " este deja adaugat!\n");
    }
    produse.push_back(produs);
}

void Repo::stergeProdus(int pozitie) {
    if (pozitie != produse.size() - 1) {
        std::copy(produse.begin() + pozitie + 1, produse.end(), produse.begin() + pozitie);
    }
    produse.pop_back();
}

void Repo::modificaProdus(const Produs& produsModificat) {
    if (!exista(produsModificat))
        throw ExceptieRepo("Numele " + produsModificat.getNumeProdus() + " nu a fost gasit!\n");
    for (auto& produs : produse)
        if (produs.getNumeProdus() == produsModificat.getNumeProdus()) {
            produs.setTipProdus(produsModificat.getTipProdus());
            produs.setPretProdus(produsModificat.getPretProdus());
            produs.setProducatorProdus(produsModificat.getProducatorProdus());
        }
}

bool Repo::exista(const Produs& produs) {
    return std::find_if(produse.begin(), produse.end(), [&](const Produs& p) { return p.getNumeProdus() == produs.getNumeProdus(); }) != produse.end();
}

const Produs& Repo::cautaProdus(std::string nume) {
    auto iterator = std::find_if(produse.begin(), produse.end(), [&](const Produs& p) { return p.getNumeProdus() == nume; });
    if (iterator == produse.end()) {
        throw ExceptieRepo("Nu s-a gasit produsul cu numele " + nume + "!\n");
    }
    return *iterator;
}

int Repo::cautaPozitieDupaNume(const std::string numeProdus) const {
    auto iterator = std::find_if(produse.begin(), produse.end(), [&](const Produs& p) { return p.getNumeProdus() == numeProdus; });
    if (iterator == produse.end()) {
        throw ExceptieRepo("Nu exista produsul cu numele " + numeProdus);
    }
    return static_cast<int>(std::distance(produse.begin(), iterator));
}

const vector<Produs>& Repo::getAll() const noexcept {
    return this->produse;
}

ostream& operator<<(ostream& out, const ExceptieRepo& exceptie) {
    for (const auto& mesaj : exceptie.mesajEroare)
        out << mesaj;
    return out;
}

Repo::~Repo()
{
}


void RepoFile::readAllFromFile() {
    std::ifstream fin(numeFisier);
    if (!fin.is_open()) {
        throw ExceptieRepo("Fisierul nu a putut fi deschis: " + numeFisier);
    }
    while (true) {
        string numeProdus;
        std::getline(fin >> std::ws, numeProdus);
        if (fin.fail()) {
            break;
        }
        string tipProdus;
        std::getline(fin >> std::ws, tipProdus);
        int pretProdus = 0;
        fin >> pretProdus;
        string producatorProdus;
        std::getline(fin >> std::ws, producatorProdus);

        Produs produs{ numeProdus, tipProdus, pretProdus, producatorProdus };
        Repo::adaugaProdus(produs);
    }
    fin.close();
}

void RepoFile::writeAllToFile() {
    std::ofstream fout(numeFisier);
    if (!fout.is_open()) { std::string mesaj("Fisierul nu a putut fi deschis: ");throw ExceptieRepo(mesaj); }
    for (auto& produs : Repo::getAll()) {
        fout << produs.getNumeProdus() << std::endl;
        fout << produs.getTipProdus() << std::endl;
        fout << produs.getPretProdus() << std::endl;
        fout << produs.getProducatorProdus() << std::endl;
    }
    fout.close();
}