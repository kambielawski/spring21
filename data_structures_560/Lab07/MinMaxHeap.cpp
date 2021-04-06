/*
 * CONSTRUCTOR
*/
template <typename ItemType>
MinMaxHeap<ItemType>::MinMaxHeap()
{
    arr = new HeapNode<ItemType>[DEFAULT_HEAP_SIZE];
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
    HeapNode<ItemType> *newArr = new HeapNode<ItemType>[capacity * 2];

    /* Copy previous array to new array */
    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    /* Delete previous array and replace with resized array */
    delete [] arr;
    arr = newArr;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::swap(HeapNode<ItemType> *a, HeapNode<ItemType> *b)
{
    HeapNode<ItemType> temp = *a;
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

    if (arr[index].item < arr[grandparent_index].item) {
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

    if (arr[index].item > arr[grandparent_index].item) {
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
        cout << arr[root].item << ", ";
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
    HeapNode<ItemType> new_item;
    new_item.item = item;
    new_item.search_key = search_key;
    arr[new_item_index] = new_item;
    size++;

    /* return if initially empty or if new item == its parent */
    if (size == 1 || arr[new_item_index].search_key == arr[parent_index].search_key) 
        return;

    /* Compare item and its parent */
    if (arr[new_item_index].search_key < arr[parent_index].search_key) {
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
}

template <typename ItemType>
int MinMaxHeap<ItemType>::findSmallestDescendent(int index) const
{
    
    int min_index = index;
    int left_child_left = this->leftChild(this->leftChild(index));
    int left_child_right = this->rightChild(this->leftChild(index));
    int right_child_left = this->leftChild(this->rightChild(index));
    int right_child_right = this->leftChild(this->rightChild(index));
    int left_child = this->leftChild(index);
    int right_child = this->rightChild(index);

    if (left_child_left < size && arr[left_child_left].search_key < arr[min_index].search_key)
        min_index = left_child_left;
    if (left_child_right < size && arr[left_child_right].search_key < arr[min_index].search_key)
        min_index = left_child_right;
    if (right_child_left < size && arr[right_child_left].search_key < arr[min_index].search_key)
        min_index = right_child_left;
    if (right_child_right < size && arr[right_child_right].search_key < arr[min_index].search_key)
        min_index = right_child_right;
    if (left_child < size && arr[left_child].search_key < arr[min_index].search_key)
        min_index = left_child;
    if (right_child < size && arr[right_child].search_key < arr[min_index].search_key)
        min_index = right_child;
    return min_index;
}

template <typename ItemType>
bool MinMaxHeap<ItemType>::isEmpty() const
{
    return size == 0;
}

template <typename ItemType>
void MinMaxHeap<ItemType>::deleteMin()
{
    /* Small heap cases */
    if (size == 0)
        throw runtime_error("Can't delete from an empty heap");
    if (size == 1) {
        size--;
        return;
    }

    arr[0].search_key = INT_MAX;
    int smallest_descendent_index = this->findSmallestDescendent(0);
    int last_element_index = size - 1;

    /* If last element equals the second smallest, make last element the root and be done */
    if (arr[last_element_index].search_key <= arr[smallest_descendent_index].search_key) {
        arr[0] = arr[last_element_index];
    } else {
        /* Make second smallest the new root */
        arr[0] = arr[smallest_descendent_index];

        /* Now compare last element with the hole left by s */
        int parent_of_smallest = this->parent(smallest_descendent_index);
        if (parent_of_smallest == 0) {
            /* If the 2nd min node was a child of the root, we just use it and we're done */
            arr[smallest_descendent_index] = arr[last_element_index];
        } else {
            /* Otherwise we use the last element or the parent to patch up the hole */
            arr[smallest_descendent_index] = arr[last_element_index]; 
            if (arr[smallest_descendent_index].search_key > arr[parent_of_smallest].search_key) {
                this->swapIndex(smallest_descendent_index, parent_of_smallest);
            }
            
            /* Now we insert the item downward */
            int insertion_index = smallest_descendent_index;
            int smallest_descendent;
            /* break if we're the smallest index at a min node */
            while (insertion_index < size && (smallest_descendent = this->findSmallestDescendent(insertion_index)) != insertion_index)
            {
                /* swap with smallest descendent */
                this->swapIndex(smallest_descendent, insertion_index);
                insertion_index = smallest_descendent;
                /* If we've swapped with a min node and now our position breaks the max node above it, swap and continue swapping down */
                if (arr[insertion_index].search_key > arr[this->parent(insertion_index)].search_key) {
                    this->swapIndex(insertion_index, this->parent(insertion_index));
                }
            }
            
        }
    }
    size--;
}

template <typename ItemType>
int MinMaxHeap<ItemType>::findLargestDescendent(int index, int search_depth) const
{
    int max_index = index;
    int left_child_index = this->leftChild(index);
    int right_child_index = this->rightChild(index);
    if (search_depth == 1) {

        if (left_child_index > size-1 && right_child_index > size-1) {
            return index; 
        } else if (left_child_index > size-1) {
            if (arr[right_child_index].item > arr[index].item)
                return right_child_index;
            else
                return index;
        } else if (right_child_index > size-1) {
            if (arr[left_child_index].item > arr[index].item)
                return left_child_index;
            else
                return index;
        } else {
            if (arr[left_child_index].item > arr[max_index].item)
                max_index = left_child_index;
            if (arr[right_child_index].item > arr[max_index].item)
                max_index = right_child_index;
            return max_index;
        }
    } else {
        /* check right subtree */
        int contender_index = this->findLargestDescendent(right_child_index, search_depth-1);
        if (arr[contender_index].item > arr[max_index].item)
            max_index = contender_index;
        /* check left subtree */
        contender_index = this->findLargestDescendent(left_child_index, search_depth-1);
        if (arr[contender_index].item > arr[max_index].item)
            max_index = contender_index;
        
        return max_index;
    }
}

template <typename ItemType>
void MinMaxHeap<ItemType>::deleteMax()
{
    /* small heap size cases */
    if (size == 0)
        throw runtime_error("Can't delete from an empty heap");
    if (size == 1) {
        size--;
        return;
    }

    int max_index = this->findLargestDescendent(0, 2); 
    int second_largest_index = this->findLargestDescendent(max_index, 2);
    int last_element_index = size-1;

    if (arr[last_element_index].search_key >= arr[second_largest_index].search_key) {
        /* when the last element == the largest element, just replace it */
        arr[second_largest_index] = arr[last_element_index];
    } else {
        /* fill max hole w/ 2nd largest element */
        arr[max_index] = arr[second_largest_index];
        arr[second_largest_index] = arr[last_element_index];
        /* now there is a hole at second largest index */
        int parent_second_largest = this->parent(second_largest_index);
        /* now compare p(L2) and last element; if equal, just replace */
        if (arr[second_largest_index].search_key < arr[parent_second_largest].search_key)
            this->swapIndex(second_largest_index, parent_second_largest);

        /* now put it in its proper place */
        int insertion_index = second_largest_index;
        int largest_descendent;
        while (insertion_index < size && (largest_descendent = this->findLargestDescendent(insertion_index, 2)) != insertion_index)
        {
            this->swapIndex(insertion_index, largest_descendent);
            insertion_index = largest_descendent;

            /* ensure we don't break the minmax property w/ the min node above */
            if (arr[insertion_index].search_key < arr[this->parent(insertion_index)].search_key)
                this->swapIndex(insertion_index, this->parent(insertion_index));
        }
    }
    size--;
}

template <typename ItemType>
ItemType MinMaxHeap<ItemType>::findMin() const
{
    if (size == 0 )
        throw runtime_error("Heap is empty");

    return arr[0].item;
}

template <typename ItemType>
ItemType MinMaxHeap<ItemType>::findMax() const
{
    if (size == 0)
        throw runtime_error("Heap is empty");

    return arr[this->findLargestDescendent(0, 2)].item;
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
    for (int i = 0; i < ceil(log2(size)); i+=2) {
        this->printGivenLevel(i, 0);
        cout << endl;
    }
}

template <typename ItemType>
void MinMaxHeap<ItemType>::printMaxLevels() const
{
    for (int i = 1; i < ceil(log2(size)); i+=2) {
        this->printGivenLevel(i, 0);
        cout << endl;
    }
}

