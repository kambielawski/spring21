
using namespace std;

template <typename ItemType>
K_Ary_Heap<ItemType>::K_Ary_Heap(int k, bool minheap) 
: m_size(0), m_root(nullptr), k(k), isMinHeap(minheap)
{}

template <typename ItemType>
K_Ary_Heap<ItemType>::~K_Ary_Heap()
{

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
void K_Ary_Heap<ItemType>::insert(int search_key, ItemType item)
{

}

template <typename ItemType>
ItemType K_Ary_Heap<ItemType>::popRoot()
{

}

template <typename ItemType>
int K_Ary_Heap<ItemType>::size() const
{
    return m_size;
}

template <typename ItemType>
void K_Ary_Heap<ItemType>::remove(int search_key, ItemType item)
{

}

template <typename ItemType>
void K_Ary_Heap<ItemType>::remove(int search_key)
{

}
