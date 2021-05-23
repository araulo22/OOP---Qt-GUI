//
// Created by araul on 28.03.2021.
//

#ifndef A45_ARAULO22_DYNAMICVECTOR_H
#define A45_ARAULO22_DYNAMICVECTOR_H
#endif //A45_ARAULO22_DYNAMICVECTOR_H


#pragma once
#include <stdexcept>

#include "Movie.h"
typedef Movie TElem;

template <typename TElem>


class DynamicVector {

private:
    TElem* elementsList;
    int vectorSize;
    int vectorCapacity;

public:
    DynamicVector(int capacityGiven = 4);
    DynamicVector(const  DynamicVector& vectorToSet);
    ~DynamicVector();
    void resizeElementsList();
    bool needsResize();
    int searchElementInList(const TElem& elementToSearch);
    void append(TElem elementToAppend);
    void remove(const TElem& elementToRemove);
    void update(const TElem& elementToUpdate, const TElem& updatedElement);
    TElem& operator[](int positionOfTheElement);
    int size();
    int capacity();
    DynamicVector& operator=(const  DynamicVector& vectorUsed);
};

template<typename TElem>
DynamicVector<TElem>::DynamicVector(int capacityGiven){
    this->vectorCapacity = capacityGiven;
    this->vectorSize = 0;
    this->elementsList = new TElem[this->vectorCapacity];
}
template<typename TElem>
DynamicVector<TElem>::DynamicVector(const  DynamicVector& vectorToSet){
    vectorCapacity = vectorToSet.vectorCapacity;
    vectorSize = vectorToSet.vectorSize;
    elementsList = new TElem[vectorToSet.vectorCapacity];
    for (int i = 0; i < vectorSize; ++i) {
        elementsList[i] = vectorToSet.elementsList[i];
    }
}

template<typename TElem>
DynamicVector<TElem>::~DynamicVector()
{
    delete[] elementsList;
}

template<typename TElem>
inline void DynamicVector<TElem>::resizeElementsList()
{
    TElem* newList = new TElem[vectorCapacity * 2];
    for (int i = 0; i < vectorSize; ++i)
        newList[i] = elementsList[i];
    vectorCapacity *= 2;
    delete[] elementsList;
    elementsList = newList;
}

template<typename TElem>
inline bool DynamicVector<TElem>::needsResize()
{
    return vectorSize == vectorCapacity;
}

template<typename TElem>
int DynamicVector<TElem>::searchElementInList(const TElem& elementToSearch) {
    for (int i = 0; i < vectorSize; ++i) {
        if (elementsList[i] == elementToSearch)
            return i;
    }
    return -1;
}

template<typename TElem>
void DynamicVector<TElem>::append(TElem elementToAppend) {
    if (needsResize())
        resizeElementsList();
    elementsList[vectorSize++] = elementToAppend;
}

template<typename TElem>
void DynamicVector<TElem>::remove(const TElem& elementToRemove) {
    int positionWhereFound = searchElementInList(elementToRemove);
    if (positionWhereFound != -1) {
        for (int i = positionWhereFound; i < vectorSize - 1; ++i) {
            elementsList[i] = elementsList[i + 1];
        }
        --vectorSize;
    }
}

template<typename TElem>
void DynamicVector<TElem>::update(const TElem& elementToUpdate, const TElem& updatedElement) {
    int positionWhereFound = searchElementInList(elementToUpdate);
    if (positionWhereFound != -1) {
        elementsList[positionWhereFound] = updatedElement;
    }
}

template<typename TElem>
TElem& DynamicVector<TElem>::operator[](int positionOfTheElement) {
    if (positionOfTheElement < 0 || positionOfTheElement >= vectorSize)
        throw std::runtime_error("Invalid position");
    return elementsList[positionOfTheElement];}

template<typename TElem>
int DynamicVector<TElem>::size() {
    return vectorSize;
}

template<typename TElem>
int DynamicVector<TElem>::capacity()
{
    return vectorCapacity;
}

template<typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(const  DynamicVector& vectorUsed){
    if (this != &vectorUsed) {
        if (vectorCapacity < vectorUsed.vectorSize) {
            delete[] elementsList;
            elementsList = new TElem[vectorUsed.vectorCapacity];
        }
        vectorSize = vectorUsed.vectorSize;
        vectorCapacity = vectorUsed.vectorCapacity;
        for (int i = 0; i < vectorSize; ++i)
            elementsList[i] = vectorUsed.elementsList[i];
    }
    return *this;
}