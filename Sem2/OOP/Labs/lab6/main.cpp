#include "ui.h"
#include "repository.h"
#include "service.h"
#include "tests.h"

int main(){
    test_all();
    ProdusRepo repo;
    MagazinService service{repo};
    Consola ui{service};
    ui.run();
}
