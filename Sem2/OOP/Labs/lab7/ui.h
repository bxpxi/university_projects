#pragma once
#include "service.h"
class ConsoleUI{
private:
    Magazin& srv;
public:
    explicit ConsoleUI(Magazin& srv):srv{srv}{};
    ConsoleUI(const ConsoleUI& ot)=delete;

    static void printMenu();
    void uiAdd();
    void uiModify();
    void uiDelete();
    void uiFilter();
    void uiSort();
    void uiSearch();
    static void printAll(const vector<Produs>& allProduse);
    void run();
};