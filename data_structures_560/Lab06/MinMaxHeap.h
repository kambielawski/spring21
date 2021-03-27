#include <iostream>
using namespace std;

template <typename ItemType>
struct HeapNode {
    ItemType item;
    int search_key;
};

/*
 * Array-based implementation of a minmax heap
*/

#ifndef MIN_MAX_HEAP_H
#define MIN_MAX_HEAP_H

template <typename ItemType>
class MinMaxHeap
{
private:
HeapNode<ItemType> *arr;

public:
MinMaxHeap();
~MinMaxHeap();
void insertItem(int search_key, ItemType item);
void deleteMin();
void printMinLevels() const;
void printMaxLevels() const;

};

#include "MinMaxHeap.cpp"

#endif
