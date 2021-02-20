#ifndef HASH_TABLE_INTERFACE_H
#define HASH_TABLE_INTERFACE_H

template <typename ItemType>
class HashTableInterface {
public:
virtual bool isEmpty() const = 0;
virtual int numItems() const = 0;
virtual bool add(int searchKey, ItemType item) = 0; // 1 if successful, 0 if not
virtual bool remove(int searchKey, ItemType item) = 0; // 1 if successful, 0 if not
virtual bool contains(int searchKey, ItemType item) = 0;

};

#endif
