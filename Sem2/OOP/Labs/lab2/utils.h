#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include "domain.h"

typedef bool(*Cmp)(CHELTUIALA Cheltuiala1, CHELTUIALA Cheltuiala2);

/*
 * Functia sorteaza array-ul de cheltuieli prin BubbleSort
 * @parametri: Array - pointer spre un array
 *             Cmp - functia de comparare
 *             len - lungimea array-ului
 * @return: -
 */
void BubbleSort(CHELTUIALA_P Array, Cmp cmp, int len);

/*
 * Functia sorteaza array-ul de cheltuieli prin SelectionSort
 * @parametri: Array - pointer spre un array
 *             Cmp - functia de comparare
 *             len - lungimea array-ului
 * @return: -
 */
//void SelectionSort(CHELTUIALA_P Array, Cmp cmp, int len);

#endif //LAB2_UTILS_H
