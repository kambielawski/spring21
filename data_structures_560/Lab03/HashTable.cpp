#include <iostream> 

template <typename ItemType>
bool HashTable<ItemType>::isPrime(int n) const
{
    if (n == 0 || n == 1)
        return false;
    for (int i = 2; i <= n/2; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

template <typename ItemType>
HashTable<ItemType>::HashTable(std::function<int (int, int)> hashFunction) : load(0)
{
    this->table = new TableEntry<ItemType>[tableSize];
    this->hash = hashFunction; 
}

template <typename ItemType>
HashTable<ItemType>::~HashTable()
{
    delete [] table;
}

template <typename ItemType>
void HashTable<ItemType>::resizeAndRehash()
{
    // find new table size
    int oldTableSize = tableSize;
    int newTableSize = tableSize * 2 + 1;
    while (!isPrime(newTableSize)) 
        newTableSize++;
    tableSize = newTableSize;

    // rehash table
    TableEntry<ItemType>* newTable = new TableEntry<ItemType>[newTableSize];
    TableEntry<ItemType>* oldTable = table;
    table = newTable;
    load = 0;

    for (int i = 0; i < oldTableSize; i++)
    {
        if (!oldTable[i].empty)
            this->insert(oldTable[i].item, oldTable[i].item);
    }

    delete [] oldTable;
    oldTable = nullptr;
    newTable = nullptr;
}

template <typename ItemType>
int HashTable<ItemType>::numItems() const
{
    return load;
}

template <typename ItemType>
bool HashTable<ItemType>::isEmpty() const
{
    return load == 0;
}

template <typename ItemType>
bool HashTable<ItemType>::insert(int searchKey, ItemType item)
{
    int h_i = 0;
    int candidate;
    bool inserted = false;
    
    if (load + 1 > tableSize / 2)
        this->resizeAndRehash();

    while (!inserted)
    {
        if (h_i >= tableSize)
            throw std::runtime_error("Could not find valid hash position");

        candidate = this->hash(searchKey, h_i) % tableSize; 
        if (table[candidate].empty)
        {
            //insert the new item
            table[candidate].empty = false;
            table[candidate].item = item;
            
            load++;
            inserted = true;
        }
        h_i++;
    }
    return true;
}

template <typename ItemType>
bool HashTable<ItemType>::remove(int searchKey, ItemType item)
{
    int h_i = 0;
    int candidate;

    if (!this->contains(searchKey, item))
        return false;

    while (h_i <= tableSize)
    {
        candidate = this->hash(searchKey, h_i) % tableSize;

        if (!table[candidate].empty)
        {
            if (table[candidate].item == item)
            {
                table[candidate].empty = true;
                table[candidate].removed = true;
                load--;
                return true;
            }
        } 
        h_i++;
    }
    throw std::runtime_error("Error deleting item");
}

template <typename ItemType>
bool HashTable<ItemType>::contains(int searchKey, ItemType item)
{
    int h_i = 0;
    int candidate;
    bool found = false;

    while (h_i <= tableSize && !found)
    {
        candidate = this->hash(searchKey, h_i) % tableSize;

        if (!table[candidate].empty)
        {
            if (table[candidate].item == item)
            {
                found = true;
            }
        } else if (!table[candidate].removed) {
            return false;
        } 
        h_i++;
    }
    return found;
}

template <typename ItemType>
void HashTable<ItemType>::printTable() const
{
    for (int i = 0; i < tableSize; i++) {
        std::cout << i << ": ";
        if (!table[i].empty)
            std:: cout << table[i].item;
        std::cout << std::endl;
    }
}
