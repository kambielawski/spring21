#include <math.h>
#include "HeapInterface.h"

static const int INITIAL_HEAP_SIZE = 32;

#ifndef K_ARY_HEAP_H
#define K_ARY_HEAP_H

template <typename ItemType>
struct HeapNode
{
float search_key;
ItemType item;

};

template <typename ItemType>
class K_Ary_Heap : public HeapInterface<ItemType>
{
private:
bool isMinHeap;
int k;
int m_size;
int m_capacity;
HeapNode<ItemType>* heap_array;

bool keepsHeapProperty(HeapNode<ItemType>* child, HeapNode<ItemType>* parent);
bool isPositivePowerOfK(int check) const;
void resizeArray();
void swap(HeapNode<ItemType>* a, HeapNode<ItemType>* b);
void swapIndex(int i1, int i2);
int getChildIndex(int parent_index) const;


public:
K_Ary_Heap(int k, bool minheap);
~K_Ary_Heap();
void insert(float search_key, ItemType item);
ItemType* asArray() const;
// void remove(float search_key);
// void remove(float search_key, ItemType item);
ItemType popRoot();
ItemType peekRoot() const;
bool contains(ItemType item) const;
int size() const;
void printLevelOrder() const;

};

#include "K_Ary_Heap.cpp"

#endif
