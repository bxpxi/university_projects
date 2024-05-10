#include "IteratorMDO.h"
#include "MDO.h"
#include <stdexcept>

//complexitate theta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
    prim();
}

//complexitate theta(1)
void IteratorMDO::prim(){
    curent = dict.prim;
}

//complexitate theta(1)
void IteratorMDO::urmator(){
    if(valid())
        curent = curent->urmator;
    else
        throw std::runtime_error("Iterator invalid");
}

//complexitate theta(n)
void IteratorMDO::avanseazaKpasi(int k){
    if(valid() && k>=1){
        for(int i=1;i<=k;i++)
            urmator();
    }
    else
        throw std::runtime_error("Iterator invalid");
}

//complexitate theta(1)
bool IteratorMDO::valid() const{
    return curent != nullptr;
}

//complexitate theta(1)
TElem IteratorMDO::element() const{
    if(valid())
        return curent->e;
    else
        throw std::runtime_error("Iterator invalid: elementul nu poate fi accesat");
}


