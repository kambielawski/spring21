#ifndef HEAP_INTERFACE
#define HEAP_INTERFACE

template <typename ItemType>
class HeapInterface
{
private:
virtual int size() const = 0;
virtual void insert(float search_key, ItemType item) = 0;
// virtual void remove(float search_key) = 0;
virtual ItemType popRoot() = 0;

};

#endif
