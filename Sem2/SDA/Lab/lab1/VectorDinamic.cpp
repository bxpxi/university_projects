#include "VectorDinamic.h"
#include "IteratorVectorDinamic.h"
#include <stdexcept>

using namespace std;

// complexitate: O(n)
void VectorDinamic::redim() {
    // redimensionare vector => se dubleaza capacitatea

    capacity *= 2;
    TElem* newElems = new TElem[capacity]{};

    for(int i=0; i<size; i++){
        newElems[i] = elems[i];
    }

    delete[] elems;
    elems = newElems;
}

// complexitate: O(1)
VectorDinamic::VectorDinamic(int capacitate) : elems(nullptr), size(0), capacity(capacitate) {
    //constructor clasa VectorDinamic

    if(capacity <= 0){
        throw std::invalid_argument("Capacitate invalida");
    }

    elems = new TElem[capacity]{};
}


// complexitate: O(1)
VectorDinamic::~VectorDinamic() {
    //destructor clasa VectorDinamic

    delete[] elems;
}


// complexitate: theta(1)
int VectorDinamic::dim() const{
    return size;
}


// complexitate: theta(1)
TElem VectorDinamic::element(int i) const{
    if(i >= 0 && i < size)
        return elems[i];
    else
        throw std::out_of_range("Index invalid");
}


// complexitate-timp amortizata: theta(1)
void VectorDinamic::adaugaSfarsit(TElem e) {
    if(size == capacity)
        redim();

    elems[size] = e;
    size++;
}

// complexitate: O(n)
void VectorDinamic::adauga(int i, TElem e) {
    if(i < 0 || i > size)
        throw std::out_of_range("Index invalid");

    if(size == capacity)
        redim();

    for(int j = size; j > i; j--)
        elems[j] = elems[j-1];

    elems[i] = e;
    size++;
}

// complexitate: theta(1)
TElem VectorDinamic::modifica(int i, TElem e) {
    if(i >= 0 && i < size){
        TElem oldValue = elems[i];
        elems[i] = e;
        return oldValue;
    }else
        throw std::out_of_range("Index invalid");
}

// complexitat: O(n)
TElem VectorDinamic::sterge(int i) {
    if(i >= 0 && i < size){
        TElem removedValue = elems[i];

        for(int j = i; j < size - 1; j++)
            elems[j] = elems [j+1];

        size--;
        return removedValue;
    }else
        throw std::out_of_range("Index invalid");
}

// complexitate: O(n)
void VectorDinamic::adauga_multiplu(int x, TElem e) {
    for(int i=0; i < x; i++){
        if(size == capacity)
            redim();
        elems[size] = e;
        size++;
    }
}

IteratorVectorDinamic VectorDinamic::iterator() {
    return IteratorVectorDinamic(*this);
}



