#ifndef HEAP_INTERFACE
#define HEAP_INTERFACE

template <typename ItemType>
class HeapInterface
{
private:
virtual int size() const = 0;
virtual void insert(int search_key, ItemType item) = 0;
virtual void remove(int search_key) = 0;
virtual ItemType popRoot() = 0;

};

#endif
