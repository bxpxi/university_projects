#ifndef LAB2_VALIDATOR_H
#define LAB2_VALIDATOR_H

#include "domain.h"
#include<stdbool.h>

typedef bool (*Validator)(CHELTUIALA, char*);

/*
 * Functia valideaza o cheltuiala
 * @parametri: Cheltuiala - o cheltuiala
 *             erori - erori, pointer la char
 * @return: 1 - daca cheltuiala e valida
 *          0 - altfel
 */
bool ValideazaCheltuiala(CHELTUIALA Cheltuiala, char* erori);

#endif //LAB2_VALIDATOR_H
