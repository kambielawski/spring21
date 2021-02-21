

#include "HashTableInterface.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename ItemType>
class HashTable : public HashTableInterface<ItemType>
{
private:
int load;
int tableSize = 11;

public:
HashTable();
~HashTable();
bool isEmpty() const;
int numItems() const;
bool add(int searchKey, ItemType item);
bool remove(int searchKey, ItemType item);
bool contains(int searchKey, ItemType item);

};

#endif
