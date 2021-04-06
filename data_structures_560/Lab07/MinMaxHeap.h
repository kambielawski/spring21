#include <iostream>
#include <climits>
#include <math.h>
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
static const int DEFAULT_HEAP_SIZE = 32;
HeapNode<ItemType> *arr;
int size;
int capacity;

/* Helper functions */
void resizeHeapArray();
bool isMinLevel(int index) const;
int parent(int index) const;
int leftChild(int index) const;
int rightChild(int index) const;
void swap(HeapNode<ItemType> *a, HeapNode<ItemType> *b);
void swapIndex(int a, int b);
void swapUpMinLevels(int index);
void swapUpMaxLevels(int index);
int findSmallestDescendent(int index) const;
int findLargestDescendent(int index, int search_depth) const;
void printGivenLevel(int level, int root) const;
void inorderTraversal() const;

public:
MinMaxHeap();
~MinMaxHeap();
void insertItem(int search_key, ItemType item);
ItemType findMin() const;
ItemType findMax() const;
void deleteMin();
void deleteMax();
void printMinLevels() const;
void printMaxLevels() const;
void printHeap() const;
bool isEmpty() const;

};

#include "MinMaxHeap.cpp"

#endif
