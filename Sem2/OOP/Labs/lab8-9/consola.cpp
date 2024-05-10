#include "consola.h"
#include "domain.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;

constexpr int Optiune_Adaugare_Produs = 1;
constexpr int Optiune_Stergere_Produs = 2;
constexpr int Optiune_Modificare_Produs = 3;
constexpr int Optiune_Afisare_Produse = 4;
constexpr int Optiune_Cautare_Produs = 5;
constexpr int Optiune_Filtrare_Produs = 6;
constexpr int Optiune_Sortare_Produs = 7;
constexpr int Optiune_Adaugare_In_Cos_Cumparaturi = 8;
constexpr int Optiune_Stergere_Din_Cos_Cumparaturi = 9;
constexpr int Optiune_Golire_Cos_Cumparaturi = 10;
constexpr int Optiune_Umple_Random_Cos_Cumparaturi = 11;
constexpr int Optiune_Afisare_Cos_Cumparaturi = 12;
constexpr int Optiune_Exportare_In_Fisier_CSV = 13;
constexpr int Optiune_Iesire = 0;
constexpr int Optiune_Raport_Tip = 14;
constexpr int Optiune_Undo = 15;

void UI::ui_adaugaProdus() {
    int pretProdus = 0;
    string numeProdus, tipProdus, producatorProdus;
    cin.ignore();
    cout << "Introduceti numele produsului: ";
    getline(cin, numeProdus);
    cout << "Introduceti tipul produsului: ";
    getline(cin, tipProdus);
    cout << "Introduceti pretul produsului: ";
    cin >> pretProdus;
    cin.ignore();
    cout << "Introduceti producatorul produsului: ";
    getline(cin, producatorProdus);
    service.adaugaProdus(numeProdus, tipProdus, pretProdus, producatorProdus);
    cout << "Produsul " << numeProdus << " a fost adaugat cu succes!\n";
}

void UI::ui_stergeProdus() {
    string numeProdus;
    cin.ignore();
    cout << "Introduceti numele produsului pentru stergere: ";
    getline(cin, numeProdus);
    service.stergeProdus(numeProdus);
    cout << "Produsul " << numeProdus << " a fost sters cu succes!\n";
}

void UI::ui_modificaProdus() {
    int pretProdus = 0;
    string numeProdus, tipProdus, producatorProdus;
    cin.ignore();
    cout << "Introduceti numele produsului pentru modificat: ";
    getline(cin, numeProdus);
    cout << "Introduceti noul tip al produsului: ";
    getline(cin, tipProdus);
    cout << "Introduceti noul pret al produsului: ";
    cin >> pretProdus;
    cin.ignore();
    cout << "Introduceti noul producator al produsului: ";
    getline(cin, producatorProdus);
    service.modificaProdus(numeProdus, tipProdus, pretProdus, producatorProdus);
    cout << "Produsul " << numeProdus << " a fost modificat cu succes!\n";
}

void UI::ui_afiseazaProduse(const vector<Produs> &produse) {
    if (produse.empty()) {
        cout << "\nNu exista produse in lista!\n";
        return;
    }
    cout << "Produse: \n";
    cout << "=================================\n";
    int i = 0;
    for (const auto& produs : produse) {
        i++;
        cout << i << ". " << produs.getNumeProdus() << "; tip: " << produs.getTipProdus() << "; pret: " << produs.getPretProdus() << "; producator: " << produs.getProducatorProdus() << "\n";
    }
    cout << "=================================\n";
}

void UI::ui_cautaProdus() {
    string numeProdus;
    cin.ignore();
    cout << "Introduceti numele produsului cautat: ";
    getline(cin, numeProdus);
    const Produs& produs = service.cautaProdus(numeProdus);
    cout << produs.getNumeProdus() << "; tip: " << produs.getTipProdus() << "; pret: " << produs.getPretProdus() << "; producator: " << produs.getProducatorProdus() << "\n";
}

void UI::ui_filtrare() {
    // 1 -> tip / 2 -> pret / 0 -> iesire (sunt optiunile utilizatorului)
    int reperFiltrare = 0;
    cin.ignore();
    cout << "Alegeti reperul de filtrare (1 -> tip / 2 -> pret / 0 -> iesire): ";
    cin >> reperFiltrare;
    if (reperFiltrare == 1) {
        string tipProdus;
        cout << "Introduceti tipul dupa care sa se filtreze: ";
        cin.ignore();
        getline(cin, tipProdus);
        ui_afiseazaProduse(service.filtreazaDupaTip(tipProdus));
    }
    else if (reperFiltrare == 2) {
        int pretProdus = 0;
        cout << "Introduceti pretul dupa care sa se filtreze: ";
        cin >> pretProdus;
        ui_afiseazaProduse(service.filtreazaDupaPret(pretProdus));
    }
    else if (reperFiltrare == 0) return;
    else {
        cout << "Reper de filtrare necunoscut!\n";
        ui_filtrare();
    }
}

void UI::ui_raport(){
    std::unordered_map<string, vector<string>> tipuri = service.raportSrv();
    for(auto& it:tipuri){
        cout<<it.first<<": ";
        for(auto& it2:it.second)
            cout<<it2<<' ';
        cout<<std::endl;
    }
}

void UI::ui_sortare() {
    // 1 -> nume / 2 -> producator / 3 -> pret + tip / 0 -> iesire (pentru reperul de sortare) -> prima optiune a utilizatorului
    // 1 -> crescator / 2 -> descrescator (pentru ordinea de sortare) -> a doua optiune a utilizatorului
    int reperSortare = 0, ordineSortare = 0;
    cin.ignore();
    cout << "Alegeti reperul dupa care sa se sorteze (1 -> nume / 2 -> producator / 3 -> pret + tip / 0 -> iesire): ";
    cin >> reperSortare;
    if (reperSortare == 0) return;
    if (reperSortare != 1 && reperSortare != 2 && reperSortare != 3) {
        cout << "Reper invalid! Va rugam sa introduceti 1, 2 sau 3!\n";
        ui_sortare();
    }
    cout << "Alegeti ordinea de sortare (1 -> crescator / 2 -> descrescator): ";
    cin >> ordineSortare;
    if (ordineSortare != 1 && ordineSortare != 2) {
        cout << "Ordine de sortare invalida! Va rugam sa introduceti 1 sau 2!\n";
        ui_sortare();
    }
    const vector<Produs>& produse = service.sorteaza(reperSortare, ordineSortare);
    ui_afiseazaProduse(produse);
}

void UI::ui_adaugaProdusInCosCumparaturi() {
    string numeProdus;
    cin.ignore();
    cout << "Introduceti numele produsului pentru a-l adauga in cosul de cumparaturi: ";
    getline(cin, numeProdus);
    ui_afiseazaProduse(service.adaugaProdusInCosCumparaturi(numeProdus));
}

void UI::ui_stergeProdusDinCosCumparaturi() {
    string numeProdus;
    cin.ignore();
    cout << "Introduceti numele produsului pentru a-l sterge din cosul de cumparaturi: ";
    getline(cin, numeProdus);
    ui_afiseazaProduse(service.stergeProdusDinCosCumparaturi(numeProdus));
}

void UI::ui_umpleRandomCosCumparaturi() {
    int dimensiune = 0;
    cin.ignore();
    cout << "Introduceti numarul de produse de adaugat in cosul de cumparaturi: ";
    cin >> dimensiune;
    ui_afiseazaProduse(service.umpleRandomCosCumparaturi(dimensiune));
}

void UI::ui_exportaInFisier() {
    string numeFisier, formatFisier;
    cin.ignore();
    cout << "Introduceti tipul de fisier in care sa se introduca cosul (CSV / HTML): ";
    getline(cin, formatFisier);
    cout << "Introduceti numele unui fisier pentru a salva continutul cosului de inchirieri: ";
    getline(cin, numeFisier);
    const vector<Produs>& produse = service.getAllCosCumparaturi();
    if (formatFisier == "CSV")
        service.exportaInCSV(numeFisier, produse);
    else if (formatFisier == "HTML")
        service.exportaInHTML(numeFisier, produse);
    else
        cout << "Tip fisier invalid!\n";
}

void UI::ui_undo() {
    service.undo();
    ui_afiseazaProduse(service.getAll());
}

void UI::ruleaza() {
    while (true) {
        cout << "\n=================================\n";
        cout << "   Meniu magazin: \n";
        cout << "1. Adauga produs.\n";
        cout << "2. Sterge produs.\n";
        cout << "3. Modifica produs.\n";
        cout << "4. Afiseaza toate produsele.\n";
        cout << "5. Cauta un produs dupa nume.\n";
        cout << "6. Filtreaza produse dupa nume / pret.\n";
        cout << "7. Sorteaza produse dupa nume / producator / pret + tip.\n";
        cout << "8. Adauga produs in cosul de cumparaturi.\n";
        cout << "9. Sterge produs din cosul de cumparaturi.\n";
        cout << "10. Goleste cosul de cumparaturi.\n";
        cout << "11.Adauga un numar de produse aleatoare in cosul de cumparaturi.\n";
        cout << "12.Afiseaza cosul de cumparaturi.\n";
        cout << "13.Exporta cosul in fisier CSV / HTML.\n";
        cout << "14.Raport-tip\n";
        cout << "15.Undo\n";
        cout << "";
        cout << "0. Iesire din aplicatie.\n";
        cout << "=================================\n";
        int comanda = 0;
        cout << ">>>";
        cin >> comanda;
        try {
            switch (comanda) {
                case Optiune_Adaugare_Produs:
                    ui_adaugaProdus();
                    break;
                case Optiune_Stergere_Produs:
                    ui_stergeProdus();
                    break;
                case Optiune_Modificare_Produs:
                    ui_modificaProdus();
                    break;
                case Optiune_Afisare_Produse:
                    ui_afiseazaProduse(service.getAll());
                    break;
                case Optiune_Cautare_Produs:
                    ui_cautaProdus();
                    break;
                case Optiune_Filtrare_Produs:
                    ui_filtrare();
                    break;
                case Optiune_Sortare_Produs:
                    ui_sortare();
                    break;
                case Optiune_Adaugare_In_Cos_Cumparaturi:
                    ui_adaugaProdusInCosCumparaturi();
                    break;
                case Optiune_Golire_Cos_Cumparaturi:
                    ui_afiseazaProduse(service.golesteCosCumparaturi());
                    break;
                case Optiune_Umple_Random_Cos_Cumparaturi:
                    ui_umpleRandomCosCumparaturi();
                    break;
                case Optiune_Afisare_Cos_Cumparaturi:
                    ui_afiseazaProduse(service.getAllCosCumparaturi());
                    break;
                case Optiune_Exportare_In_Fisier_CSV:
                    ui_exportaInFisier();
                    break;
                case Optiune_Iesire:
                    return;
                case Optiune_Undo:
                    ui_undo();
                    break;
                case Optiune_Stergere_Din_Cos_Cumparaturi:
                    ui_stergeProdusDinCosCumparaturi();
                    break;
                case Optiune_Raport_Tip:
                    ui_raport();
                    break;
                default:
                    cout << "Comanda necunoscuta!\n";
            }
            cout << '\n';
        }
        catch (const ExceptieRepo& exceptie) {
            cout << exceptie << "\n";
        }
        catch (const ExceptieValidare& exceptie) {
            cout << exceptie << "\n";
        }
    }
}

UI::~UI()
{
}