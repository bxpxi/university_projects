//domain.c
#include "domain.h"

bool CreeazaCheltuiala(CHELTUIALA_P* Cheltuiala, int Nr_ap, float Suma, char* Tip){
    if(Cheltuiala == NULL)
        return 0;

    CHELTUIALA_P Cheltuiala_p = (CHELTUIALA_P)malloc(sizeof(CHELTUIALA));

    if(Cheltuiala_p == NULL)
        return 0;

    Cheltuiala_p->Nr_ap = Nr_ap;
    Cheltuiala_p->Suma = Suma;

    unsigned int TipLen = strlen(Tip) + 1;
    char* tip = (char*)malloc(sizeof(char)*TipLen);
    strcpy(tip, Tip);
    Cheltuiala_p->Tip = tip;

    *Cheltuiala = Cheltuiala_p;

    return 1;
}

bool DistrugeCheltuiala(CHELTUIALA_P* Cheltuiala){
    if(Cheltuiala == NULL)
        return 0;

    free((*Cheltuiala)->Tip);
    free(*Cheltuiala);

    *Cheltuiala = NULL;

    return 1;
}
/*
void PrintCheltuiala(CHELTUIALA Cheltuiala){
    printf("\n [Nr apartament: %d; Suma: %.2f; Tip: %s] \n", Cheltuiala.Nr_ap, Cheltuiala.Suma, Cheltuiala.Tip);
}
*/
int GetNr_ap(CHELTUIALA Cheltuiala){
    return Cheltuiala.Nr_ap;
}

float GetSuma(CHELTUIALA Cheltuiala){
    return Cheltuiala.Suma;
}

char* GetTip(CHELTUIALA Cheltuiala){
    return Cheltuiala.Tip;
}

void SetNr_ap(CHELTUIALA_P Cheltuiala, int Nr_ap){
    Cheltuiala->Nr_ap = Nr_ap;
}

void SetSuma(CHELTUIALA_P Cheltuiala, float Suma){
    Cheltuiala->Suma = Suma;
}

void SetTip(CHELTUIALA_P Cheltuiala, char* Tip){
    unsigned int TipLen = strlen(Tip) + 1;
    char* NewTip = (char*)malloc(sizeof(char)*TipLen);
    if(NewTip == NULL)
        return;
    strcpy(NewTip, Tip);
    free(Cheltuiala->Tip);
    Cheltuiala->Tip = NewTip;
}

bool CheltuieliEgale(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2){
    if(GetNr_ap(Cheltuiala1) == GetNr_ap(Cheltuiala2) &&
        (GetSuma(Cheltuiala1) == GetSuma(Cheltuiala2)) &&
            GetTip(Cheltuiala1) == GetTip(Cheltuiala2))
        return 1;
    return 0;
}

bool ComparaCrescatorSuma(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2){
    if(GetSuma(Cheltuiala1) < GetSuma(Cheltuiala2))
        return 1;
    if(GetSuma(Cheltuiala1) == GetSuma(Cheltuiala2) && GetNr_ap(Cheltuiala1) < GetNr_ap(Cheltuiala2))
        return 1;
    return 0;
}

bool ComparaDescrescatorSuma(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2){
    if(GetSuma(Cheltuiala1) > GetSuma(Cheltuiala2))
        return 1;
    if(GetSuma(Cheltuiala1) == GetSuma(Cheltuiala2) && GetNr_ap(Cheltuiala1) > GetNr_ap(Cheltuiala2))
        return 1;
    return 0;
}

bool ComparaCrescatorTip(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2){
    if(strcmp(GetTip(Cheltuiala1), GetTip(Cheltuiala2)) < 0)
        return 1;
    if(strcmp(GetTip(Cheltuiala1), GetTip(Cheltuiala2)) == 0 && GetNr_ap(Cheltuiala1) < GetNr_ap(Cheltuiala2))
        return 1;
    return 0;
}

bool ComparaDescrescatorTip(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2){
    if(strcmp(GetTip(Cheltuiala1), GetTip(Cheltuiala2)) > 0)
        return 1;
    if(strcmp(GetTip(Cheltuiala1), GetTip(Cheltuiala2)) == 0 && GetNr_ap(Cheltuiala1) > GetNr_ap(Cheltuiala2))
        return 1;
    return 0;
}
