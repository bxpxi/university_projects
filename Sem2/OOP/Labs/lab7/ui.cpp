#include "ui.h"
#include<iostream>
using namespace std;
void ConsoleUI::printMenu() {
    cout << "Comenzi:" << endl;
    cout << "1. Adauga produs" << endl;
    cout << "2. Modifica produs" << endl;
    cout << "3. Sterge produs" << endl;
    cout << "4. Cauta produs" << endl;
    cout << "5. Afiseaza toate produsele" << endl;
    cout << "6. Filtreaza produsele" << endl;
    cout << "7. Sorteaza produsele" << endl;
    cout << "0. Exit" << endl;

}

void ConsoleUI::uiAdd() {
    string denumire, tip, producator;
    int pret = 0;

    cout << "Denumire:";
    getline(cin >> ws, denumire);

    cout << "Pret:";
    cin >> pret;

    cout << "Tip:";
    getline(cin >> ws, tip);

    cout << "Producator:";
    getline(cin >> ws, producator);

    try {
        srv.addProdus(denumire, pret, tip, producator);
        cout << "Produs adaugat cu succes";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
}

void ConsoleUI::uiModify() {
    string denumire, tip, producator;
    int pret = 0;

    cout << "Denumire:";
    getline(cin >> ws, denumire);

    cout <<"Pret nou:";
    cin >> pret;

    cout << "Tip nou:";
    getline(cin >> ws, tip);

    cout << "Producator nou:";
    getline(cin >> ws, producator);

    try {
        srv.modifyProdus(denumire, pret, tip, producator);
        cout << "Produs modificat cu succes";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }

}

void ConsoleUI::uiDelete() {

    string denumire;
    cout << "Denumire:";
    getline(cin >> ws, denumire);

    try {
        srv.deleteProdus(denumire);
        cout << "Produs stears cu succes";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }

}

void ConsoleUI::uiSort() {
    cout << "Criteriul de sortare este: ";
    string criteriu;
    cin >> criteriu;

    if (criteriu == "denumire")
        printAll(srv.sortByDenumire());
    else if (criteriu == "pret")
        printAll(srv.sortByPret());
    else if (criteriu == "nume+tip")
        printAll(srv.sortByTip());
    else
        cout << "Nu se poate sorta dupa criteriul dat";
}

void ConsoleUI::uiFilter() {
    cout << "Criteriul de filtrare este: ";
    string criteriu;
    cin >> criteriu;

    if (criteriu == "pret") {
        cout << "Pret:";
        int pret = 0;
        cin >> pret;
        printAll(srv.filtrarePret(pret));
    }
    else if (criteriu == "producator") {
        cout << "Producator:";
        string producator;
        cin >> producator;
        printAll(srv.filtrareProducator(producator));
    }
    else
        cout << "Nu se poate filtra dupa criteriul dat";
}

void ConsoleUI::uiSearch() {
    string denumire;

    cout << "Denumire:";
    getline(cin >> ws, denumire);

    try {
        Produs produs = srv.search(denumire);
        cout << "Denumire: " << produs.getDenumire() << " | Pret: " << produs.getPret() << " | Tip: " << produs.getTip() << " | Producator: " << produs.getProducator() << endl;
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
}


void ConsoleUI::printAll(const vector<Produs>& allProduse) {
    if (allProduse.empty())
        cout << "Nu exista produse." << endl;
    else
        for (const auto& produs : allProduse) {
            cout << "Denumire: " << produs.getDenumire() << " | Pret: " << produs.getPret() << " | Tip: " << produs.getTip() << " | Producator: " << produs.getProducator() << endl;
        }
}

void ConsoleUI::run()
{
    int running = 1;
    int cmd = 0;
    while (running) {
        printMenu();
        cout << "\nComanda este:";
        cin >> cmd;
        switch (cmd)
        {
            case 1:
                uiAdd();
                break;
            case 2:
                uiModify();
                break;
            case 3:
                uiDelete();
                break;
            case 4:
                uiSearch();
                break;
            case 5:
                printAll(srv.getAllProduse());
                break;
            case 6:
                uiFilter();
                break;
            case 7:
                uiSort();
                break;
            case 0:
                running = 0;
                break;
            default:
                break;
        }
    }
}