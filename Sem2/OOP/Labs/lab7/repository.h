#pragma once
#include "domain.h"
#include "VectorDinamic.h"
#include <utility>
#include <vector>

using std::vector;

class RepoException {
private:
    string errorMsg;
public:
    explicit RepoException(string errorMsg) :errorMsg{std::move( errorMsg )} {};
    string getErrorMessage() {
        return this->errorMsg;
    }
};

class ProdusRepository{
private:
    VectorDinamic<Produs> allProduse;
public:
    ProdusRepository()=default;
    ProdusRepository(const ProdusRepository& ot)=delete;
    void store(const Produs& p);
    vector<Produs> getallProduse();
    const Produs& find(const string& denumire);
    void deleteProdus(const string& denumire);
    void modify(const Produs& p);
    bool exists(const Produs& p);
};

void testRepo();