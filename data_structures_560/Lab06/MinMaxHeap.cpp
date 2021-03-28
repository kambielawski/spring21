/*
 * CONSTRUCTOR
*/
template <typename ItemType>
MinMaxHeap<ItemType>::MinMaxHeap()
{
    arr = new HeapNode<ItemType>[DEFAULT_HEAP_SIZE];
}

/*
 * DESTRUCTOR
*/
template <typename ItemType>
MinMaxHeap<ItemType>::~MinMaxHeap()
{
    delete [] arr;
    arr = nullptr;
}

/*
 * HELPER FUNCTIONS
*/
template <typename ItemType>
void MinMaxHeap<ItemType>::resizeHeapArray()
{
    /* Double the array size */
    HeapNode<ItemType> *newArr = new HeapNode<ItemType>[capacity * 2];

    /* Copy previous array to new array */
    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    /* Delete previous array and replace with resized array */
    delete [] arr;
    arr = newArr;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::swapIndex(int a, int b)
{
    HeapNode<ItemType> temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

template <typename ItemType>
int MinMaxHeap<ItemType>::parent(int index) const
{
    return (index - 1) / 2;
}

template <typename ItemType>
bool MinMaxHeap<ItemType>::isMinLevel(int index) const
{
    if (index == 0)
        return true;

    if (isMinLevel(this->parent(index)))
        return false;
    return true;
}

/*
 * PUBLIC FUNCTIONS 
*/
template <typename ItemType>
void MinMaxHeap<ItemType>::insertItem(int search_key, ItemType item)
{
    /* Resize if heap has reached capacity */
    if (size == capacity)
        this->resizeHeapArray();

    /* Add new item to array */
    HeapNode<ItemType> newItem = { search_key, item };
    arr[size] = newItem;
    size++;

    /* return if initially empty or if new item == its parent */
    if (size == 1 || arr[size].item == arr[this->parent(size)].item) return;

    

        
}

template <typename ItemType>
void MinMaxHeap<ItemType>::deleteMin()
{

}

template <typename ItemType>
void MinMaxHeap<ItemType>::printMinLevels() const
{

}

template <typename ItemType>
void MinMaxHeap<ItemType>::printMaxLevels() const
{

}

