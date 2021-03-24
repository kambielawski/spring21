#include <iostream>
using namespace std;

template <typename ItemType>
K_Ary_Heap<ItemType>::K_Ary_Heap(int k, bool minheap) 
: m_size(0), k(k), isMinHeap(minheap)
{
    m_capacity = INITIAL_HEAP_SIZE;
    heap_array = new HeapNode<ItemType>[INITIAL_HEAP_SIZE];
}

template <typename ItemType>
K_Ary_Heap<ItemType>::~K_Ary_Heap()
{
    delete[] heap_array;
    heap_array = nullptr;
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::swap (HeapNode<ItemType> *a, HeapNode<ItemType> *b)
{
    HeapNode<ItemType> temp = *a;
    *a = *b;
    *b = temp;
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::swapIndex (int i1, int i2)
{
    this->swap(&heap_array[i1], &heap_array[i2]);
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::resizeArray()
{
    /* Double size of array */
    HeapNode<ItemType>* temp = new HeapNode<ItemType>[m_size * 2];

    /* Copy over elements of array */
    for (int i = 0; i < m_size; i++)
        temp[i] = heap_array[i];

    /* delete contents of previous array */
    delete [] heap_array;

    /* clean up pointers */
    heap_array = temp;
    temp = nullptr;
}

template <typename ItemType>
bool K_Ary_Heap<ItemType>::keepsHeapProperty(HeapNode<ItemType>* child, HeapNode<ItemType>* parent)
{
    if ((isMinHeap && child->search_key > parent->search_key)
    or (!isMinHeap && child->search_key < parent->search_key))
        return true;
    return false;
}

template <typename ItemType>
bool K_Ary_Heap<ItemType>::contains(ItemType item) const
{
    for (int i = 0; i < m_size; i++)
    {
        if (heap_array[i].item == item)
            return true;
    }
    return false;
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::insert(float search_key, ItemType item)
{
    HeapNode<ItemType> new_item = { search_key, item }; 
    int index = m_size;

    if (this->contains(item))
        throw runtime_error("Cannot insert duplicate element");

    /* Double array size if we have reached capacity */
    if (m_size == m_capacity)
        this->resizeArray();

    /* Set item to root if heap is empty */
    if (m_size == 0)
        heap_array[0] = new_item;
    else {
        heap_array[index] = new_item;
        int parent_index = (index-1) / k; 
        
        while (!keepsHeapProperty(&heap_array[index], &heap_array[parent_index])) {
            /* Swap upward in the tree until heap property is satisfied */
            swapIndex(index, parent_index);
            index = parent_index;
            parent_index = (index - 1) / k;

            /* Check for root */
            if (index == 0)
                break;
        }
    }
    m_size++;
}

template <typename ItemType>
ItemType K_Ary_Heap<ItemType>::popRoot()
{
    if (m_size == 0)
        throw runtime_error("Can't remove from an empty tree");

    ItemType ret = heap_array[0].item;

    /* If size 1, just return root and decrease size */
    if (m_size == 1) {
        m_size--;
        return ret;
    }

    /* Otherwise, we have to get fancy */
    /* swap root and last node, "delete" last node */
    swap(&heap_array[0], &heap_array[m_size-1]);
    m_size--;

    /* then swap the root downward until heap property is satisfied */
    int parent_index = 0;
    int min_child_index = this->getChildIndex(0);
        
    while ((min_child_index < m_size) && !keepsHeapProperty(&heap_array[min_child_index], &heap_array[parent_index])) {
        swapIndex(min_child_index, parent_index);
        parent_index = min_child_index;
        min_child_index = this->getChildIndex(parent_index);
        cout << "index of child: " << min_child_index << " index of parent: " << parent_index << endl;
    }

    return ret;
}

/* returns index of child w/ minimum key in a minheap & max key in a maxheap */
template <typename ItemType>
int K_Ary_Heap<ItemType>::getChildIndex(int parent_index) const
{
    int child_index = (parent_index * k) + 1;
    int test_index;
    for (int i = 2; i <= k; i++) {
        test_index = (parent_index * k) + i;
        if (test_index < m_size) {
            if (isMinHeap) {
                if (heap_array[(parent_index * k) + i].search_key < heap_array[child_index].search_key) {
                    child_index = (parent_index * k) + i;
                }
            } else {
                if (heap_array[(parent_index * k) + i].search_key > heap_array[child_index].search_key)
                    child_index = (parent_index * k) + i;
            }
        }
    }

    return child_index;
}

template <typename ItemType>
ItemType K_Ary_Heap<ItemType>::peekRoot() const
{
    if (m_size == 0)
        throw runtime_error("Heap is empty\n");
    return heap_array[0].item;
}

template <typename ItemType>
int K_Ary_Heap<ItemType>::size() const
{
    return m_size;
}

template <typename ItemType>
bool K_Ary_Heap<ItemType>::isPositivePowerOfK(int check) const
{
    int temp = 1;
    while (pow(k, temp) < m_size && pow(k, temp) <= check) {
        if (pow(k, temp) == check)
            return true;
        temp++;
    }

    return false;
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::printLevelOrder() const
{
    int newline_index = 1;
    for (int i = 0; i < m_size; i++) {
        if (isPositivePowerOfK(i) || i == 0 || i == m_size-1) 
            cout << heap_array[i].item << "\n";
        else
            cout << heap_array[i].item << " : ";
    }
    cout << endl;
}

template <typename ItemType>
ItemType* K_Ary_Heap<ItemType>::asArray() const
{
    ItemType *arr = new ItemType[m_size];
    
    for (int i = 0; i < m_size; i++)
        arr[i] = heap_array[i].item;

    return arr;
}

// template <typename ItemType>
// void K_Ary_Heap<ItemType>::remove(float search_key, ItemType item)
// {

// }

// template <typename ItemType>
// void K_Ary_Heap<ItemType>::remove(float search_key)
// {

// }
