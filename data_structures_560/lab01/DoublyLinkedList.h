

template <typename ItemType>
struct ListNode
{
    ListNode<ItemType> *prev;
    ListNode<ItemType> *next;
    ItemType value;
};

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <typename ItemType>
class DoublyLinkedList
{
private:
ListNode<ItemType> *head;
ListNode<ItemType> *tail;
int m_length;

public:
DoublyLinkedList();
~DoublyLinkedList();
int find(ItemType value) const;
bool isEmpty() const;
int length();
void insertItem(ItemType value);
void deleteItem(ItemType value);
ItemType getItemAtIndex(int index);

};

#include "DoublyLinkedList.cpp"

#endif
