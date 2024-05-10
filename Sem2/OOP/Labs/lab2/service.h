#ifndef LAB2_SERVICE_H
#define LAB2_SERVICE_H

#include "repository.h"
#include "validator.h"
#include "utils.h"
#include <stdlib.h>

typedef struct _SERVICE_CHELTUIELI{
    REPOSITORY_CHELTUIELI_P Repository;
    Validator ValidatorCheltuiala;
}SERVICE_CHELTUIELI, *SERVICE_CHELTUIELI_P;

/*
 * Functia creeaza service pentru cheltuieli
 * @parametri: Service - un pointer spre un pointer de tip service
 *             Repository - un pointer spre un repository
 *             ValidatorC - un validator
 * @return: 1 - daca service-ul a fost creat cu succes
 *          0 - altfel
 */
bool CreeazaService(SERVICE_CHELTUIELI_P* Service, REPOSITORY_CHELTUIELI_P Repository, Validator ValidatorC);

/*
 * Functia distruge sevice pentru cheltuieli
 * @parametri: Service - un pointer spre pointer de tip service pentru cheltuieli
 * @return: 1 - daca service-ul a fost distrus cu succes
 *          0 - altfel
 */
bool DistrugeService(SERVICE_CHELTUIELI_P* Service);

/*
 * Functia adauga o cheltuiala in service
 * @parametri: Service - un pointer la un service de cheltuieli
 *             Nr_ap - numar apartament(int)
 *             Suma - suma(float)
 *             Tip - tip(char*)
 *             erori - daca sunt erori se vor adauga la adresa specificata(char*)
 * @return: 1 - daca a fost adaugata cu succes
 *          0 - altfel
 */
bool AdaugaCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, float Suma, char* Tip, char* erori);

/*
 * Functia sterge o cheltuiala din service
 * @parametri: Service - un pointer la un service de cheltuieli
 *             Nr_ap - numar apartament(int)
 *             erori - daca sunt erori se vor adauga la adresa specificata(char*)
 * @return: 1 - daca a fost adaugata cu succes
 *          0 - altfel
 */
bool StergeCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, char* erori);

/*
 * Functia modifica o cheltuiala din service
 * @parametri: Service - un pointer la un service de cheltuieli
 *             Nr_ap - numar apartament(int)
 *             Suma - suma(float)
 *             Tip - tip(char*)
 *             erori - daca sunt erori se vor adauga la adresa specificata(char*)
 * @return: 1 - daca a fost adaugata cu succes
 *          0 - altfel
 */
bool ModificaCheltuialaService(SERVICE_CHELTUIELI_P Service, int Nr_ap, float Suma, char* Tip, char* erori);

/*
 * Functia returneaza prin array cheltuielile care pot fi afisate
 * @parametri: Service - un pointer la un service de cheltuieli
 *             optiune - optiunea vizualizarii(int)
 *                     0 - vizualizare toata lista
 *                     1 - vizualizare dupa nr apartamant
 *                     2 - vizualizare dupa suma
 *                     3 - vizualizare dupa tip
 *             filtru - filtrul vizualizarii(char)
 *             Array - un pointer la array-ul de cheltuieli
 *             len - lungimea array-ului(int)
 *             erori - daca sunt erori se vor adauga la adresa specificata(char*)
 * @return: 1 - daca nu sunt erori
 *          0 - altfel
 */
bool GetAllService(SERVICE_CHELTUIELI_P Service, int optiune, char filtru[], CHELTUIALA_P* Array, int* len, char* erori);

/*
 * Functia sorteaza cheltuielile
 * @parametri: Service - un pointer la un service de chetuieli
 *             optiune - optiunea sortarii
 *                     0 - crescator dupa suma
 *                     1 - descrescator dupa suma
 *                     2 - crescator dupa tip
 *                     3 - descrescator dupa tip
 */
bool Sorteaza(SERVICE_CHELTUIELI_P Service, int optiune, CHELTUIALA_P* Array, char* erori);

#endif //LAB2_SERVICE_H
