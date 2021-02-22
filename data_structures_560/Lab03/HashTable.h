#include <functional>

#include "HashTableInterface.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename ItemType>
struct TableEntry {
    bool empty = true;
    bool removed = false;
    ItemType item;
};

template <typename ItemType>
class HashTable : public HashTableInterface<ItemType>
{
private:
int load;
int tableSize = 11;
TableEntry<ItemType> *table;
std::function<int (int, int)> hash;
void resizeAndRehash();
bool isPrime(int n) const;

public:
HashTable(std::function<int (int, int)> hashFunction);
~HashTable();
bool isEmpty() const;
int numItems() const;
bool insert(int searchKey, ItemType item);
bool remove(int searchKey, ItemType item);
bool contains(int searchKey, ItemType item);
void printTable() const;

};

#include "HashTable.cpp"

#endif
