#include <iostream>
using namespace std;

template <typename ItemType>
struct DSNode
{
    ItemType item;
    int key;
    int rank;
    DSNode<ItemType> *parent;

    ~DSNode() {
        parent = nullptr;
    }
};

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

template <typename ItemType>
class DisjointSets 
{
private:
DSNode<ItemType> *disjoint_sets;
int num_items;

DSNode<ItemType>* find(ItemType item);
DSNode<ItemType>* getRepresentativeElement(DSNode<ItemType>* node);

public:
DisjointSets();
~DisjointSets();
void makeSet(ItemType* item_arr, int size);
void printSets() const;
ItemType findItem(ItemType item);
void unionByRank(ItemType item1, ItemType item2);
void pathCompression(ItemType item);
void printPath(ItemType item) const;

};

#include "DisjointSets.cpp"

#endif
