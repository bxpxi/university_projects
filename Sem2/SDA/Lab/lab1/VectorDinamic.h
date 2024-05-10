//#ifndef LAB1_TEMA_VECTORDINAMIC_H
//#define LAB1_TEMA_VECTORDINAMIC_H

//#endif //LAB1_TEMA_VECTORDINAMIC_H

#pragma once

typedef int TElem;

class IteratorVectorDinamic;


class VectorDinamic {

private:
    /* aici e reprezentarea */
    TElem* elems; //vectorul de elemente
    int size;     //dimensiunea curenta a vectorului
    int capacity; //capacitatea vectorului

    // redimensionare
    void redim();

public:
    // constructor
    //arunca exceptie in cazul in care capacitate e <=0
    VectorDinamic (int capacitate);

    // returnare dimensiune
    int dim() const;

    // returnare element
    //arunca exceptie daca i nu e valid
    //indicii ii consideram de la 0
    TElem element(int i) const;

    // modifica element de pe pozitia i si returneaza vechea valoare
    //arunca exceptie daca i nu e valid
    TElem modifica(int i, TElem e);

    // adaugare element la sfarsit
    void adaugaSfarsit(TElem e);

    // adaugare element pe o pozitie i
    //arunca exceptie daca i nu e valid
    void adauga(int i, TElem e);

    // sterge element de pe o pozitie i si returneaza elementul sters
    //arunca exceptie daca i nu e valid
    TElem sterge(int i);

    // adauga la sfarsit element e de x ori
    void adauga_multiplu(int x, TElem e);

    // returnare iterator
    IteratorVectorDinamic iterator();

    //destructor
    ~VectorDinamic();
};







