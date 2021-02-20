#ifndef HASHTABLE_SC_H
#define HASHTABLE_SC_H

/* this is the implementation of a hash table using separate chaining */

#include "HashTableInterface.h"
#include "LinkedList.h"

#include <iostream>
#include <functional>
using namespace std;

template <typename ItemType>
class HashTable : public HashTableInterface<ItemType> {
private:
LinkedList<ItemType> *m_hashtable;
static const int DEFAULT_BUCKET_SIZE = 11; 
int m_bucketSize;
int m_numItems;
int hashKey(int searchKey);

public:
HashTable(int bucketSize);
HashTable();
~HashTable();

bool isEmpty() const;
int numItems() const;
// to do: accept a string as a searchKey
bool contains(int searchKey, ItemType item);
bool add(int searchKey, ItemType item);
int find(int searchKey, ItemType item);
bool remove(int searchKey, ItemType item);
void printLengths() const;
void printLists() const;
int bucketSize() const;
void traverseTable(std::function<bool (ItemType, int)> compFunc, int compNum, std::function<void (ItemType, int)> func);

};

template <typename ItemType>
HashTable<ItemType>::HashTable(int bucketSize) : m_bucketSize(bucketSize), m_numItems(0) {
  m_hashtable = new LinkedList<ItemType>[m_bucketSize]; 
}

template <typename ItemType>
HashTable<ItemType>::HashTable() : m_bucketSize(DEFAULT_BUCKET_SIZE), m_numItems(0) {
  m_hashtable = new LinkedList<ItemType>[m_bucketSize];
}

template <typename ItemType>
HashTable<ItemType>::~HashTable() {
  delete [] m_hashtable;
  m_hashtable = nullptr;
}

template <typename ItemType>
int HashTable<ItemType>::hashKey(int searchKey) {
  return (searchKey % m_bucketSize);
}

template <typename ItemType>
bool HashTable<ItemType>::isEmpty() const {
  return m_numItems == 0;
}

template <typename ItemType>
int HashTable<ItemType>::numItems() const {
  return m_numItems;
}

template <typename ItemType>
void HashTable<ItemType>::printLengths() const {
  for (int i = 0; i < m_bucketSize; i++) {
    cout << m_hashtable[i].length() << endl;
  }
}

template <typename ItemType>
void HashTable<ItemType>::printLists() const {
  for (int i = 0; i < m_bucketSize; i++) {
    cout << i << ": ";
    for (int j = 0; j < m_hashtable[i].length(); j++) {
      cout << "-> " << m_hashtable[i].getItemAtIndex(j);
    }
    cout << "\n";
  }
}

template <typename ItemType>
int HashTable<ItemType>::bucketSize() const {
  return m_bucketSize;
}

template <typename ItemType>
bool HashTable<ItemType>::contains(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  return m_hashtable[index].find(item);
}

template <typename ItemType>
bool HashTable<ItemType>::add(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  m_hashtable[index].insertBack(item);
  m_numItems++;
  return true;
}

template <typename ItemType>
int HashTable<ItemType>::find(int searchKey, ItemType item)
{
    int index = this->hashKey(searchKey);
    if (m_hashtable[index].find(item))
        return index;
    else
        return -1;
}

/* 
params
@function<bool (ItemType, int)> compFunc - takes two params
    @ItemType item - is the item in the hashtable
    @int num - number for comparing the item's search key (compNum passed)
@int compNum - comparison number for comparing item's search key to
@function<void ItemType> func - takes the item and the index and does something with it

*/
template <typename ItemType>
void HashTable<ItemType>::traverseTable(std::function<bool (ItemType, int)> compFunc, int compNum, std::function<void (ItemType, int)> func) {
  ItemType item;
  for (int i = 0; i < m_bucketSize; i++) {
    for (int j = 0; j < m_hashtable[i].length(); j++) {
      item = m_hashtable[i].getItemAtIndex(j);
      if (compFunc(item, compNum)) {
        func(item, i);
      }
    }
  }
}

/* 
removes item from hashtable
returns true if remove worked, false if item not found
*/
template <typename ItemType>
bool HashTable<ItemType>::remove(int searchKey, ItemType item) {
  int index = this->hashKey(searchKey);
  if (m_hashtable[index].find(item)) {
    m_hashtable[index].removeItem(item);
    m_numItems--;
    return true;
  } else {
    return false;
  }
}

#endif
