#ifndef LAB2_REPOSITORY_H
#define LAB2_REPOSITORY_H

#include "domain.h"
#include <stdbool.h>
#define INIT_SIZE 2

typedef struct RREPOSITORY_CHELTUIELI{
    CHELTUIALA_P* Array;
    int Lungime;
    int Capacitate;
}REPOSITORY_CHELTUIELI, *REPOSITORY_CHELTUIELI_P;

/*
 * Functia creeaza un repository de cheltuieli
 * @parametri: Repository - un pointer la un pointer de repository de cheltuieli
 * @return: 1 - daca repository a fost creat cu succes
 *          0 - altfel
 */
bool CreeazaRepository(REPOSITORY_CHELTUIELI_P* Repository);

/*
 * Functia distruge un repository de cheltuieli
 * @parametri: Repository - pointer la un pointer de repository de cheltuieli
 * @return: 1 - daca repository a fost distrus cu succes
 *          0 - altfel
 */
bool DistrugeRepository(REPOSITORY_CHELTUIELI_P* Repository);

/*
 * Functia redimensioneaza repository-ul de cheltuieli
 * Se apeleaza doar cand se adauga/sterge o cheltuiala
 * @parametri: Repository - un pointer la un pointer de repository de cheltuieli
 * @return: 1 - daca repository a fost redimensionat cu succes
 *          0 - altfel
 */
bool RedimRepository(REPOSITORY_CHELTUIELI_P Repository);

/*
 * Functia numraul de elemente(cheltuieli) dintr-un repository
 * @parametri: Repository - un pointer la un repository de cheltuieli
 * @return: int - numarul de cheltuieli stocate in repository
 */
int GetLungimeRepository(REPOSITORY_CHELTUIELI_P Repository);

/*
 * Functia realizeaza un deep copy al cheltuielilor din repository
 * @parametri: Repository - un pointer la un repository de cheltuieli
 * @return: 1 - daca procesul de deep copy a fost realizat cu succes
 *          0 - altfel
 */
bool GetAll(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P* Array);

/*
 *Functia adauga o cheltuiala la repository-ul de cheltuieli
 * @parametri: Repository - un pointer la un repository de cheltuieli
 *             Cheltuiala - un pointer la o cheltuiala
 * @return: 1 - daca adaugarea a fost realizata cu succes
 *          0 - altfel
 */
bool AdaugaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P Cheltuiala);

/*
 *Functia sterge o cheltuiala din repository-ul de cheltuieli
 * @parametri: Repository - un pointer la un repository de cheltuieli
 *             Cheltuiala - un pointer la o cheltuiala
 * @return: 1 - daca stererea a fost realizata cu succes
 *          0 - altfel
 */
bool StergeCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA Cheltuiala);

/*
 *Functia modifica o cheltuiala din repository-ul de cheltuieli
 * @parametri: Repository - un pointer la un repository de cheltuieli
 *             Cheltuiala - un pointer la o cheltuiala
 * @return: 1 - daca modificarea a fost realizata cu succes
 *          0 - altfel
 */
bool ModificaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA_P Cheltuiala);

/*
 *Functia cauta o cheltuiala din repository-ul de cheltuieli
 * @parametri: Repository - un pointer la un repository de cheltuieli
 *             Cheltuiala - o cheltuiala
 * @return: pozitia pe care se afla cheltuiala in array
 *          -1, daca nu exista acea cheltuiala in repository-ul de cheltuieli
 */
int CautaCheltuialaRepository(REPOSITORY_CHELTUIELI_P Repository, CHELTUIALA Cheltuiala);

#endif //LAB2_REPOSITORY_H
