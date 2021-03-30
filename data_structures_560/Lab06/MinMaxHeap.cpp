/*
 * CONSTRUCTOR
*/
template <typename ItemType>
MinMaxHeap<ItemType>::MinMaxHeap()
{
    arr = new HeapNode<ItemType>*[DEFAULT_HEAP_SIZE];
    size = 0;
    capacity = DEFAULT_HEAP_SIZE;
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
    HeapNode<ItemType> **newArr = new HeapNode<ItemType>*[capacity * 2];

    /* Copy previous array to new array */
    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    /* Delete previous array and replace with resized array */
    delete [] arr;
    arr = newArr;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::swap(HeapNode<ItemType> **a, HeapNode<ItemType> **b)
{
    HeapNode<ItemType> *temp = *a;
    *a = *b;
    *b = temp;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::swapIndex(int a, int b)
{
    this->swap(&arr[a], &arr[b]);
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

/* Recursively swaps an item up only comparing with min-levels */
template <typename ItemType>
void MinMaxHeap<ItemType>::swapUpMinLevels(int index)
{
    if (index == 0)
        return;

    int grandparent_index = this->parent(this->parent(index)); 

    if (arr[index]->item < arr[grandparent_index]->item) {
        this->swapIndex(index, grandparent_index);
        this->swapUpMinLevels(grandparent_index);
    }
}

/* Recursively swaps an item up only comparing with max-levels */
template <typename ItemType>
void MinMaxHeap<ItemType>::swapUpMaxLevels(int index)
{
    if (index <= 2)
        return;

    int grandparent_index = this->parent(this->parent(index));

    if (arr[index]->item > arr[grandparent_index]->item) {
        this->swapIndex(index, grandparent_index);
        this->swapUpMaxLevels(grandparent_index);
    }
}

template <typename ItemType>
int MinMaxHeap<ItemType>::leftChild(int index) const
{
    return (index * 2) + 1;
}

template <typename ItemType>
int MinMaxHeap<ItemType>::rightChild(int index) const
{
    return (index * 2) + 2;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::printGivenLevel(int level, int root) const
{
    /* index out of range of tree (base case) */
    if (root >= size) {
        return;
    }

    /* print the level (leaf case) */
    if (level == 0) {
        cout << arr[root]->item << " i=" << root << ", ";
        return;
    } 
    
    /* call recursively */
    printGivenLevel(level-1, this->leftChild(root));
    printGivenLevel(level-1, this->rightChild(root));
}

template <typename ItemType>
void MinMaxHeap<ItemType>::inorderTraversal() const
{
    for (int i = 0; i < size; i++)
        cout << arr[i]->item << " ";
    cout << endl;
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

    int new_item_index = size;
    int parent_index = this->parent(new_item_index);

    /* Add new item to array */
    HeapNode<ItemType>* new_item = new HeapNode<ItemType>;
    new_item->item = item;
    new_item->search_key = search_key;
    arr[new_item_index] = new_item;
    size++;

    /* return if initially empty or if new item == its parent */
    if (size == 1 || arr[new_item_index]->item == arr[parent_index]->item) 
        return;

    cout << "INSERT: " << item << endl;

    /* Compare item and its parent */
    if (arr[new_item_index]->item < arr[parent_index]->item) {
        /* Check parent's level */
        if (this->isMinLevel(parent_index)) {
            /* Swap upward accordingly */
            this->swapIndex(new_item_index, parent_index);
            this->swapUpMinLevels(parent_index);
        } else {
            this->swapUpMinLevels(new_item_index);
        }
    } else {
        if (this->isMinLevel(parent_index)) {
            this->swapUpMaxLevels(new_item_index);
        } else {
            this->swapIndex(new_item_index, parent_index);
            this->swapUpMaxLevels(parent_index);
        }
    }
    this->printHeap();
    this->inorderTraversal();
    cout << "\n\n";
}

template <typename ItemType>
void MinMaxHeap<ItemType>::deleteMin()
{

}

template <typename ItemType>
void MinMaxHeap<ItemType>::printHeap() const
{
    for (int i = 0; i <= ceil(log2(size)); i++) {
        this->printGivenLevel(i, 0);
        cout << endl;
    }
}

template <typename ItemType>
void MinMaxHeap<ItemType>::printMinLevels() const
{
    for (int i = 0; i < size; i++) {

    }
}

template <typename ItemType>
void MinMaxHeap<ItemType>::printMaxLevels() const
{

}

