#include <iostream>
#include "ui.h"

using std::cout;
using std::endl;

void testAll()
{
    testeDomain();
    testRepo();
    testeService();
    cout << "Teste rulate cu succes." << endl;
}

void startApp() {
    ProdusRepository repo;
    ProdusValidator val;
    Magazin srv{ repo, val };
    ConsoleUI ui{ srv };

    ui.run();
}

int main() {
    testAll();
    startApp();
}
