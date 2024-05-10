#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"
#include <stdexcept>


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) : v(_v) {
    prim();
}


// complexitate: theta(1)
void IteratorVectorDinamic::prim() {
    current = 0;
}


// complexitate: theta(1)
bool IteratorVectorDinamic::valid() const{
    return current >= 0 && current < v.dim();
}


// complexitate: theta(1)
TElem IteratorVectorDinamic::element() const{
    if(valid())
        return v.element(current);
    else
        throw std::out_of_range("Iterator invalid");
}


// complexitate: theta(1)
void IteratorVectorDinamic::urmator() {
    if(valid())
        current++;
    else
        throw std::out_of_range("Iterator invalid");
}

