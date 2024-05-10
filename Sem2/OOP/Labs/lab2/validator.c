//validator.c
#include "validator.h"

bool ValideazaCheltuiala(CHELTUIALA Cheltuiala, char* erori){
    erori[0] = '\0';
    if(GetNr_ap(Cheltuiala) <= 0)
        strcat(erori, "Numar apartament invalid\n");
    if(GetSuma(Cheltuiala) <= 0)
        strcat(erori, "Suma invalida\n");
    if(strcmp(GetTip(Cheltuiala), "apa") !=0 && strcmp(GetTip(Cheltuiala), "canal") !=0
        && strcmp(GetTip(Cheltuiala), "incalzire") !=0 && strcmp(GetTip(Cheltuiala), "gaz") !=0)
        strcat(erori, "Tip invalid\n");

    if(strlen(erori)>0)
        return 0;

    return 1;
}