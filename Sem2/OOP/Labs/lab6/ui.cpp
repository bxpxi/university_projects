#include "ui.h"
#include "domain.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

void Consola::adaugaUI() {
    cout<<"ADAUGARE PRODUS"<<endl;
    string nume, tip, producator;
    float pret=0.0;
    cout<<"Nume: ";
    cin>>nume;
    cout<<"Tip: ";
    cin>>tip;
    cout<<"Producator: ";
    cin>>producator;
    cout<<"Pret: ";
    cin>>pret;
    service.adaugaProdus(nume, tip, producator, pret);
    cout<<"Produsul a fost adaugat cu succes!"<<endl;
}

void Consola::afisareUI(const std::vector<Produs> &produse) {
    cout<<"PRODUSE"<<endl;
    for(const auto& produs:produse)
        cout<<"Nume: "<<produs.getNume()<<"; Tip: "<<produs.getTip()<<"; Producator: "<<produs.getProducator()<<"; Pret: "<<produs.getPret()<<endl;
}

void Consola::modificaUI() {
    cout<<"MODIFICARE PRODUS"<<endl;
    string nume, tip_nou, producator;
    float pret_nou=0.0;
    cout<<"Nume: ";
    cin>>nume;
    cout<<"Producator: ";
    cin>>producator;
    cout<<"Tip nou: ";
    cin>>tip_nou;
    cout<<"Pret nou: ";
    cin>>pret_nou;
    service.adaugaProdus(nume, tip_nou, producator, pret_nou);
    cout<<"Produsul a fost modificat cu succes!"<<endl;
}

void Consola::stergereUI() {
    cout<<"STERGERE PRODUS"<<endl;
    string nume, producator;
    cout<<"Nume: ";
    cin>>nume;
    cout<<"Producator: ";
    cin>>producator;
    service.stergereProdus(nume, producator);
    cout<<"Produsul a fost sters cu succes!"<<endl;
}

void Consola::filtrareNumeUI(){
    cout<<"FILTRARE DUPA NUME"<<endl;
    string nume;
    cout<<"Nume: ";
    cin>>nume;
    afisareUI(service.filtrareNume(nume));
}

void Consola::filtrareProducatorUI() {
    cout<<"FILTRARE DUPA PRODUCATOR"<<endl;
    string producator;
    cout<<"Producator: ";
    cin>>producator;
    afisareUI(service.filtrareProducator(producator));
}

void Consola::filtrarePretUI(){
    cout<<"FILTRARE DUPA PRET"<<endl;
    float pret=0.0;
    cout<<"Pret: ";
    cin>>pret;
    afisareUI(service.filtrarePret(pret));
}

void Consola::run(){
    while(true){
        cout<<"MENIU"<<endl;
        cout<<"1.Adaugare produs\n2.Afisare produse\n3.Modificare produs\n4.Stergere produs\n5.Filtrare dupa nume\n6.Filtrare dupa producator\n7.Filtrare dupa pret\n0.Iesire\n";
        int optiune=-1;
        cout<<"Optiunea: ";
        cin>>optiune;
        switch (optiune) {
                case 1:
                    adaugaUI();
                    break;
                case 2:
                    afisareUI(service.getAll());
                    break;
                case 3:
                    modificaUI();
                    break;
                case 4:
                    stergereUI();
                    break;
                case 5:
                    filtrareNumeUI();
                    break;
                case 6:
                    filtrareProducatorUI();
                    break;
                case 7:
                    filtrarePretUI();
                    break;
                case 0:
                    cout<<"Iesire din aplicatie...";
                    return;
                default:
                    cout<<"Comanda invalida!\n";
        }
    }
}