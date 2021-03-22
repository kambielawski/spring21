#include "HeapInterface.h"

#ifndef K_ARY_HEAP_H
#define K_ARY_HEAP_H

template <typename ItemType>
struct HeapNode
{
int search_key;
ItemType item;
HeapNode **children;

};

template <typename ItemType>
class K_Ary_Heap : public HeapInterface<ItemType>
{
private:
bool isMinHeap;
int k;
int m_size;
HeapNode<ItemType>* m_root;

bool keepsHeapProperty(HeapNode<ItemType>* child, HeapNode<ItemType>* parent);

public:
K_Ary_Heap(int k, bool minheap);
~K_Ary_Heap();
void insert(int search_key, ItemType item);
void remove(int search_key);
void remove(int search_key, ItemType item);
ItemType popRoot();
int size() const;

};

#include "K_Ary_Heap.cpp"

#endif
