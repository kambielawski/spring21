template <typename ItemType>
HashTable<ItemType>::HashTable() : load(0)
{

}

template <typename ItemType>
HashTable<ItemType>::~HashTable()
{

}

template <typename ItemType>
int numItems() const
{
    return load;
}

template <typename ItemType>
bool HashTable<ItemType>::isEmpty()
{
    return load == 0;
}

template <typename ItemType>
bool add(int searchKey, ItemType item)
{

}

template <typename ItemType>
bool remove(int searchKey, ItemType item)
{

}

template <typename ItemType>
bool contains(int searchKey, ItemType item)
{

}
