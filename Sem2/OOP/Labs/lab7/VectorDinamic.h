#pragma once
constexpr auto INITIAL_CAPACITY = 10;
#include <cassert>

template<typename T>
class IteratorVector;

template<typename T>
class VectorDinamic{
private:
    T* elems;
    int capacitate;
    int lungime;

    //redimensionare
    void resize();
public:
    //constructor default
    VectorDinamic();

    //constructor copy
    VectorDinamic(const VectorDinamic& ot);

    //assignment operator
    VectorDinamic& operator=(const VectorDinamic& ot);

    //destructor
    ~VectorDinamic();

    //adauga element in vector
    void add(T elem);

    //sterge element din vector
    void sters();

    //get element de pe o anumita pozitie
    T& get(int poz);

    //set element pe o anumita pozitie
    void set(T elem, int poz);

    //lungimea vectorului
    int size();

    //iterator
    friend class IteratorVector<T>;

    IteratorVector<T> begin();
    IteratorVector<T> end();
};

template<typename T>
class IteratorVector{
private:
    const VectorDinamic<T>& vec;
    int poz = 0;
public:
    explicit IteratorVector(const VectorDinamic<T>& v) noexcept;
    IteratorVector(const VectorDinamic<T>& v, int poz) noexcept;
    [[nodiscard]] bool valid() const;
    T& element() const;
    void next();
    T& operator*();
    IteratorVector& operator++();
    bool operator==(const IteratorVector& ot) noexcept;
    bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename T>
VectorDinamic<T>::VectorDinamic() {
    this->elems = new T[INITIAL_CAPACITY];
    this->lungime = 0;
    this->capacitate = INITIAL_CAPACITY;
}

template<typename T>
VectorDinamic<T>::VectorDinamic(const VectorDinamic& ot) {
    this->elems = new T[ot.capacitate];
    for(int i=0;i<ot.lungime;i++)
        this->elems[i] = ot.elems[i];
    this->lungime=ot.lungime;
    this->capacitate=ot.capacitate;
}

template<typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic& ot){
    if(this == &ot)
        return *this;
    delete[] this->elems;
    this->elems = new T[ot.capacitate];
    for(int i=0;i<ot.lungime;i++)
        this->elems[i] = ot.elems[i];
    this->lungime=ot.lungime;
    this->capacitate=ot.capacitate;
    return *this;
}

template<typename T>
void VectorDinamic<T>::resize() {
    int newCapacity = this->capacitate * 2;
    T* newElems = new T[newCapacity];
    for (int i = 0; i < this->lungime; i++) {
        newElems[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = newElems;
    this->capacitate = newCapacity;
}

template<typename T>
VectorDinamic<T>::~VectorDinamic() {
    delete[] this->elems;
}

template<typename T>
void VectorDinamic<T>::add(T elem) {
    if (this->lungime == this->capacitate)
        resize();
    this->elems[this->lungime] = elem;
    this->lungime++;
}

template<typename ElementT>
void VectorDinamic<ElementT>::sters() {
    lungime--;
}

template<typename T>
T& VectorDinamic<T>::get(int poz) {
    return this->elems[poz];
}

template<typename T>
void VectorDinamic<T>::set(T elem, int poz) {
    this->elems[poz] = elem;
}

template<typename T>
int VectorDinamic<T>::size() {
   return this->lungime;
}

template<typename T>
IteratorVector<T> VectorDinamic<T>::begin() {
    return IteratorVector<T>(*this);
}

template<typename T>
IteratorVector<T> VectorDinamic<T>::end() {
    return IteratorVector<T>(*this, this->lungime);
}



template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v) noexcept :vec{ v } {};

template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v, int poz) noexcept :vec{ v }, poz{ poz } {};

template<typename T>
bool IteratorVector<T>::valid() const {
    return this->poz < this->vec.lungime;
}

template<typename T>
T& IteratorVector<T>::element() const {
    return this->vec.elems[this->poz];
}

template<typename T>
void IteratorVector<T>::next() {
    this->poz++;
}

template<typename T>
T& IteratorVector<T>::operator*() {
    return this->element();
}

template<typename T>
IteratorVector<T>& IteratorVector<T>::operator++() {
    this->next();
    return *this;
}

template<typename T>
bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept {
    return this->poz == ot.poz;
}

template<typename T>
bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept {
    return !(*this == ot);
}



