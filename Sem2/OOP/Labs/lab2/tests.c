#include "tests.h"
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
void runTests(){
    testDomain();
    testValidator();
    testRepo();
    testService();
    testUtils();
}

void testDomain() {
    //creare cheltuiala
    CHELTUIALA_P Cheltuiala, CheltuialaDif;
    assert(CreeazaCheltuiala(&Cheltuiala, 1, 500, "gaz"));
    assert(CreeazaCheltuiala(&CheltuialaDif, 15, 100, "canal"));
    assert(!CreeazaCheltuiala(NULL, 1, 500, "gaz"));
    //PrintCheltuiala(*Cheltuiala);

    //get + set
    SetNr_ap(Cheltuiala, 11);
    assert(GetNr_ap(*Cheltuiala) == 11);
    SetSuma(Cheltuiala, 700);
    assert(GetSuma(*Cheltuiala) == 700);
    SetTip(Cheltuiala, "apa");
    assert(strcmp(GetTip(*Cheltuiala), "apa") == 0);

    //comparare cheltuieli
    assert(CheltuieliEgale(*Cheltuiala, *Cheltuiala));
    assert(CheltuieliEgale(*Cheltuiala, *CheltuialaDif) == 0);
    assert(ComparaCrescatorSuma(*Cheltuiala, *CheltuialaDif) == 0);
    assert(ComparaDescrescatorSuma(*Cheltuiala, *CheltuialaDif) == 1);
    assert(ComparaCrescatorTip(*Cheltuiala, *CheltuialaDif) == 1);
    assert(ComparaDescrescatorTip(*Cheltuiala, *CheltuialaDif) == 0);

    //distrugere materie
    assert(DistrugeCheltuiala(&Cheltuiala));
    assert(DistrugeCheltuiala(&CheltuialaDif));
    assert(Cheltuiala == NULL);
    assert(CheltuialaDif == NULL);
}

void testValidator() {
    CHELTUIALA_P Cheltuiala, CheltuialaInv;
    char* erori = (char*)malloc(sizeof(char) * 100);
    erori[0] = '\0';
    assert(CreeazaCheltuiala(&Cheltuiala, 24, 100, "apa"));
    assert(ValideazaCheltuiala(*Cheltuiala, erori));
    assert(strlen(erori) == 0);
    assert(CreeazaCheltuiala(&CheltuialaInv, -1, -200, ""));
    assert(!(ValideazaCheltuiala(*CheltuialaInv, erori)));
    assert(strlen(erori)!=0);
    assert(strcmp(erori, "Nume invalid\nSuma invalida\nTip invalid\n") != 0);
    DistrugeCheltuiala(&CheltuialaInv);
    DistrugeCheltuiala(&Cheltuiala);
    free(erori);
}

void testRepo() {
    //creare repo
    REPOSITORY_CHELTUIELI_P Repo = NULL;
    assert(CreeazaRepository(&Repo));
    assert(CreeazaRepository(NULL) == 0);
    assert(GetLungimeRepository(Repo) == 0);
    assert(Repo->Capacitate == 2);

    //adaugare
    CHELTUIALA_P c1, c2, c3, c4, c5;
    CreeazaCheltuiala(&c1, 1, 200, "apa");
    CreeazaCheltuiala(&c2, 2, 500, "gaz");
    CreeazaCheltuiala(&c3, 3, 75, "canal");
    CreeazaCheltuiala(&c4, 4, 150, "apa");
    CreeazaCheltuiala(&c5, 5, 1000, "incalzire");

    assert(AdaugaCheltuialaRepository(Repo, c1));
    assert(GetLungimeRepository(Repo) == 1);
    assert(AdaugaCheltuialaRepository(Repo, c3));
    assert(GetLungimeRepository(Repo) == 2);
    assert(AdaugaCheltuialaRepository(Repo, c2));
    assert(GetLungimeRepository(Repo) == 3);

    //getall
    CHELTUIALA_P c;
    assert(GetAll(NULL, &c) == 0);
    assert(GetAll(Repo, NULL) == 0);
    assert(GetAll(Repo, &c) == 1);

    assert(CautaCheltuialaRepository(Repo, *c1) != -1);
    assert(CautaCheltuialaRepository(Repo, *c3) != -1);

    //modifica
    assert(ModificaCheltuialaRepository(NULL, c5) == 0);
    assert(ModificaCheltuialaRepository(Repo, NULL) == 0);
    assert(ModificaCheltuialaRepository(Repo, c1) == 1);
    assert(ModificaCheltuialaRepository(Repo, c5) == 0);


    //sterge
    assert(StergeCheltuialaRepository(Repo, *c2) == 1);
    assert(StergeCheltuialaRepository(Repo, *c1) == 1);

    /*
    //cauta
    assert(GetLungimeRepository(Repo) == 1);
    assert(StergeCheltuialaRepository(Repo, *c3) == 1);
    assert(GetLungimeRepository(Repo) == 0);
    assert(Repo->Capacitate == 2);
     */

    //distruge repo
    assert(DistrugeRepository(&Repo));
    assert(DistrugeRepository(NULL) == 0);
    assert(Repo == NULL);

    DistrugeCheltuiala(&c5);
    DistrugeCheltuiala(&c4);
    free(c);
}


void testService() {
    CHELTUIALA_P c1, c2, c3;
    CreeazaCheltuiala(&c1, 1, 200, "apa");
    CreeazaCheltuiala(&c2, 2, 200, "apa");
    CreeazaCheltuiala(&c3, 3, 1000, "incalzire");

    //creeaza
    SERVICE_CHELTUIELI_P service;
    Validator validator = ValideazaCheltuiala;
    REPOSITORY_CHELTUIELI_P repository1, repository2 = NULL;

    CreeazaRepository(&repository1);
    CreeazaRepository(&repository2);

    assert(CreeazaService(NULL, NULL, NULL) == 0);
    assert(CreeazaService(NULL, repository1, NULL) == 0);
    assert(CreeazaService(&service, repository2, validator));

    //adauga
    CHELTUIALA_P Array;
    CHELTUIALA_P sortedArray;
    int len;
    char* erori = (char*)malloc(100 * sizeof(char));
    assert(GetAllService(service, 0, "", &Array, &len, erori) == 0);
    assert(strcmp(erori, "Nu  exista cheltuieli in bloc.\n") == 0);
    assert(AdaugaCheltuialaService(service, 1, 200, "apa", erori));
    assert(strlen(erori) == 0);
    assert(GetLungimeRepository(service->Repository) == 1);

    //GetAll
    assert(GetAllService(service, 0, "", &Array, &len, NULL) == 0);

    assert(GetAllService(service, 0, "", &Array, &len, erori));
    assert(len == 1);
    assert(strlen(erori) == 0);
    assert(GetNr_ap(Array[0]) == 1);
    assert(GetSuma(Array[0]) == 200);
    assert(strcmp(GetTip(Array[0]), "apa") == 0);
    free(Array);

    //modifica materii
    //assert(ModificaCheltuialaService(service, 1, 200, "apa", NULL) == 0);
    //assert(ModificaCheltuialaService(NULL, 1, 200, "apa", erori) == 0);
    //assert(ModificaCheltuialaService(service, 3, 1000, "incalzire", erori) == 1);
    //assert(strlen(erori) == 0);
    //assert(ModificaCheltuialaService(service, -10, -1, "", erori) == 0);
    //assert(strcmp(erori, "Parametri invalizi!\nCheltuiala nu poate fi modificata\n") == 0);
    //free(Array);

    //sorteaza
    assert(AdaugaCheltuialaService(service, 2, 70, "canal", erori));
    assert(GetAllService(service, 0, "", &Array, &len, erori));
    assert(Sorteaza(NULL, 0, NULL, NULL) == 0);
    assert(Sorteaza(NULL, 0, NULL, erori) == 0);
    assert(Sorteaza(service, 0, &sortedArray, erori));
    assert(!CheltuieliEgale(*c2, sortedArray[0]));
    assert(!CheltuieliEgale(*c3, sortedArray[1]));
    free(sortedArray);
    assert(Sorteaza(service, -2, &sortedArray, erori) == 0);
    assert(strcmp(erori, "Optiune invalida.\n"));
    free(sortedArray);


    free(Array);
    assert(Sorteaza(service, 1, &sortedArray, erori));
    assert(!CheltuieliEgale(*c2, sortedArray[0]));
    assert(!CheltuieliEgale(*c3, sortedArray[1]));
    free(sortedArray);
    assert(Sorteaza(service, 2, &sortedArray, erori));
    assert(!CheltuieliEgale(*c2, sortedArray[1]));
    assert(!CheltuieliEgale(*c3, sortedArray[0]));
    free(sortedArray);
    assert(Sorteaza(service, 3, &sortedArray, erori));
    assert(!CheltuieliEgale(*c2, sortedArray[1]));
    assert(!CheltuieliEgale(*c3, sortedArray[0]));
    free(sortedArray);

    //distruge
    assert(DistrugeService(NULL) == 0);
    assert(DistrugeService(&service));
    assert(service == NULL);
    DistrugeCheltuiala(&c1);
    DistrugeCheltuiala(&c2);
    DistrugeCheltuiala(&c3);
    free(erori);
}

void testUtils() {
    CHELTUIALA_P Array = (CHELTUIALA_P)malloc(10*sizeof(CHELTUIALA));
    CHELTUIALA_P c1, c2;
    CreeazaCheltuiala(&c1, 1, 200, "apa");
    CreeazaCheltuiala(&c2, 2, 300, "gaz");

    Array[0] = *c1;
    Array[1] = *c2;

    BubbleSort(Array, ComparaCrescatorSuma, 2);
    assert(CheltuieliEgale(Array[1], *c2));
    assert(CheltuieliEgale(Array[0], *c1));

    BubbleSort(Array, ComparaDescrescatorSuma, 2);
    assert(CheltuieliEgale(Array[0], *c2));
    assert(CheltuieliEgale(Array[1], *c1));

    BubbleSort(Array, ComparaDescrescatorTip, 2);
    assert(CheltuieliEgale(Array[0], *c2));
    assert(CheltuieliEgale(Array[1], *c1));

    BubbleSort(Array, ComparaCrescatorTip, 2);
    assert(CheltuieliEgale(Array[1], *c2));
    assert(CheltuieliEgale(Array[0], *c1));

    DistrugeCheltuiala(&c1);
    DistrugeCheltuiala(&c2);
    free(Array);
}
