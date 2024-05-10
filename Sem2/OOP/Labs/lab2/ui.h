#ifndef LAB2_UI_H
#define LAB2_UI_H

#include "service.h"
#include <stdbool.h>
#define INPUT_SIZE 20

typedef struct UI{
    SERVICE_CHELTUIELI_P Service;
}UI, *UI_P;

/*
 * Functia creeaza din UI
 * @parametri: Ui - pointer spre un pointer spre Ui
 *             Service - pointer spre Service
 * @return: 1 - daca ui-ul a fost creat cu suuces
 *          0 - altfel
 */
bool CreeazaUI(UI_P* Ui, SERVICE_CHELTUIELI_P Service);

/*
 * Functia distruge din UI
 * @parametri: Ui - pointer spre un pointer spre Ui
 * @return: 1 - daca ui-ul a fost distrus cu succes
 *          0 - altfel
 */
bool DistrugeUI(UI_P* Ui);

/*
 * Functia citeste comanda de la tastaura si afiseaza meniul
 * @parametri: -
 * @return: comanda (int)
 */
int CitesteCmd();

/*
 * Functia adauga cheltuiala din Ui
 * @parametri: Ui - pointer spre Ui
 *             erori - sir de erori
 * @return: 1 - daca adaugarea a fost realizata cu succes
 *          0 - altfel
 */
bool AdaugaCheltuialaUI(UI_P Ui, char* erori);

/*
 * Functia sterge cheltuiala din Ui
 * @parametri: Ui - pointer spre Ui
 *             erori - sir de erori
 * @return: 1 - daca stergerea a fost realizata cu succes
 *          0 - altfel
 */
bool StergeCheltuialaUI(UI_P Ui, char* erori);

/*
 * Functia modifica cheltuiala din Ui
 * @parametri: Ui - pointer spre Ui
 *             erori - sir de erori
 * @return: 1 - daca modificarea a fost realizata cu succes
 *          0 - altfel
 */
bool ModificaCheltuialaUI(UI_P Ui, char* erori);

/*
 * Functia citeste optiunea/filtrul pentru afisare
 * @parametri: Ui - pointer spre Ui
 *             erori - sir de erori
 * @return: 1 - daca vizualizarea a fost realizata cu succes
 *          0 - altfel
 */
bool VizualizeazaUI(UI_P Ui, char* erori);

/*
 * Functia citeste optiunea pentru sortare
 * @parametri: Ui - pointer spre Ui
 *             erori - sir de erori
 * @return: 1 - daca sortarea a fost realizata cu succes
 *          0 - altfel
 */
bool SorteazaUI(UI_P Ui, char* erori);

/*
 * Functia care ruleaza aplicatia
 * @parametri: Ui - pointer spre Ui
 * @return: -
 */
void runUI(UI_P Ui);

#endif //LAB2_UI_H
