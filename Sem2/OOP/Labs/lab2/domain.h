#ifndef LAB2_DOMAIN_H
#define LAB2_DOMAIN_H

#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

typedef struct CHELTUIALAA{
    int Nr_ap;
    float Suma;
    char* Tip;
}CHELTUIALA, *CHELTUIALA_P;

/*
 * Functia creeaza o cheltuiala si returneaza cheltuiala printr-un pointer
 * @parametri:  Cheltuiala - pointer la un pointer la cheltuiala
 *              Nr_ap - numar intreg (int)
 *              Suma - numar rational (float)
 *              Tip - pointer la char
 * @return:  1 - daca Cheltuiala a fost creata cu succes
 *           0 - altfel
 */
bool CreeazaCheltuiala(CHELTUIALA_P* Cheltuiala, int Nr_ap, float Suma, char* Tip);


/*
 * Functia distruge o cheltuiala
 * @parametri:  Cheltuiala - pointer la un pointer la cheltuiala
 * @return: 1 - daca Cheltuiala a fost distrusa cu succes
 *          0 - altfel
 */
bool DistrugeCheltuiala(CHELTUIALA_P* Cheltuiala);

/*
 * Functia afiseaza o cheltuiala in format de tip [Nr apartament: ; Suma: ; Tip: ;]
 * @parametri: Cheltuiala - o cheltuiala
 * @return: -
 */
void PrintCheltuiala(CHELTUIALA Cheltuiala);

/*
 * Functia returneaza numarul apartamentului pentru o cheltuiala
 * @parametri:  Cheltuiala - o cheltuiala
 * @return: numarul apartamentului (int)
 */
int GetNr_ap(CHELTUIALA Cheltuiala);

/*
 * Functia returneaza suma de plata pentru o cheltuiala
 * @parametri: Cheltuiala - o cheltuiala
 * @return: suma (float)
 */
float GetSuma(CHELTUIALA Cheltuiala);

/*
 * Functia returneaza tipul pentru o cheltuiala
 * @parametri: Cheltuiala - o cheltuiala
 * @return - tip (char*)
 */
char* GetTip(CHELTUIALA Cheltuiala);

/*
 * Functia seteaza numarul apartamentului pentru o cheltuiala
 * @parametri: Cheltuiala - pointer la o cheltuiala
 *             Nr_ap - int
 * @return: -
 */
void SetNr_ap(CHELTUIALA_P Cheltuiala, int Nr_ap);

/*
 * Functia seteaza suma pentru o cheltuiala
 * @parametri: Cheltuiala - pointer la cheltuiala
 *             Suma - float
 * @return: -
 */
void SetSuma(CHELTUIALA_P Cheltuiala, float Suma);

/*
 * Functia seteaza tipul pentru o cheltuiala
 * @parametri: Cheltuiala - pointer la o cheltuiala
 *             Tip - char*
 * @return: -
 */
void SetTip(CHELTUIALA_P Cheltuiala, char* Tip);

/*
 * Functia returneaza daca doua cheltuieli sunt egale sau nu
 * @parametri: Cheltuiala1 - o cheltuiala
 *             Cheltuiala2 - o cheltuiala
 * @return: 1 - daca cheltuielile sunt egale
 *          0 - altfel
 */
bool CheltuieliEgale(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

/*
 * Functia compara doua cheltuieli dupa suma
 * @parametri: Cheltuiala1 - o cheltuiala
 *             Cheltuiala2 - o cheltuiala
 * @return: 1 - daca suma Cheltuiala1 < suma Cheltuiala2
 *          0 - altfel
 */
bool ComparaCrescatorSuma(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

/*
 * Functia compara doua cheltuieli dupa suma
 * @parametri: Cheltuiala1 - o cheltuiala
 *             Cheltuiala2 - o cheltuiala
 * @return: 1 - daca suma Cheltuiala1 > suma Cheltuiala2
 *          0 - altfel
 */
bool ComparaDescrescatorSuma(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

/*
 * Functia compara doua cheltuieli dupa tip
 * @parametri: Cheltuiala1 - o cheltuiala
 *             Cheltuiala2 - o cheltuiala
 * @return: 1 - daca tip Cheltuiala1 < tip Cheltuiala2
 *          0 - altfel
 */
bool ComparaCrescatorTip(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

/*
 * Functia compara doua cheltuieli dupa tip
 * @parametri: Cheltuiala1 - o cheltuiala
 *             Cheltuiala2 - o cheltuiala
 * @return: 1 - daca tip Cheltuiala1 > tip Cheltuiala2
 *          0 - altfel
 */
bool ComparaDescrescatorTip(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

#endif //LAB2_DOMAIN_H
