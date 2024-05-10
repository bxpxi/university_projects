//main.c
#include "ui.h"
#include "tests.h"

int main() {
    runTests();
    printf("Tests passed");

    Validator validator = ValideazaCheltuiala;
    REPOSITORY_CHELTUIELI_P repository;
    if (CreeazaRepository(&repository) == 0)
        exit(-1);
    SERVICE_CHELTUIELI_P service;
    if (CreeazaService(&service, repository, validator) == 0) {
        DistrugeRepository(&repository);
        exit(-1);
    }
    UI_P console;
    if (CreeazaUI(&console, service) == 0) {
        if (DistrugeService(&service) == 0)
            DistrugeRepository(&repository);
        exit(-1);
    }

    runUI(console);

    if (DistrugeUI(&console) == 0) {
        if (DistrugeService(&service) == 0)
            DistrugeRepository(&repository);
        exit(-1);
    }

}

