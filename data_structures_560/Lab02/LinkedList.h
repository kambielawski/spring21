#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <typename ItemType>
struct listNode {
  ItemType item;
  listNode<ItemType> *next;

  listNode() {}
  listNode(ItemType item, listNode<ItemType> *next) : item(item), next(next) {}
};


template <typename ItemType>
class LinkedList {
private:
listNode<ItemType> *m_head;
int m_length;

public:
LinkedList();
~LinkedList();

void insertFront(ItemType item);
void insertBack(ItemType item);
void removeAtIndex(int index);
void removeItem(ItemType item);
int length() const;
void printList() const;
void printListReverse() const;
void printListReverse(listNode<ItemType> *node) const;
bool find(ItemType item) const;
ItemType getItemAtIndex(int index) const;
bool isEmpty() const;

};


template <typename ItemType>
LinkedList<ItemType>::LinkedList() {
  m_head = nullptr;
  m_length = 0;
}

template <typename ItemType>
LinkedList<ItemType>::~LinkedList() {
  while (m_length > 0) {
    removeAtIndex(m_length-1);
  }
}

template <typename ItemType>
void LinkedList<ItemType>::printListReverse() const {
  printListReverse(m_head);
  std::cout << "\n";
}

template <typename ItemType>
void LinkedList<ItemType>::printListReverse(listNode<ItemType> *node) const {
  if (node->next != nullptr) {
    printListReverse(node->next);
  }
  std::cout << " " << node->item;
}

template <typename ItemType>
int LinkedList<ItemType>::length() const {
  return m_length;
}

template <typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {
  return m_length == 0;
}

template <typename ItemType>
void LinkedList<ItemType>::removeAtIndex(int index) {
  if (index < 0 || index > m_length-1) {
    throw std::runtime_error("index out of range");
  }
  if (index == 0) {
    listNode<ItemType> *temp = m_head;
    m_head = m_head->next;
    temp->next = nullptr;
    delete temp;
    temp = nullptr;
  } else {
    listNode<ItemType> *temp = m_head;
    listNode<ItemType> *prev;
    int i = 0;
    while (i < index-1) {
      temp = temp->next;
      i++;
    }
    prev = temp->next->next;
    temp->next->next = nullptr;
    delete temp->next;
    temp->next = prev;
    temp = nullptr;
    prev = nullptr;
  }
  m_length--;
}

/* 
This function assumes the item already exists in the list
i.e. this->find() will already have occurred
*/
template <typename ItemType>
void LinkedList<ItemType>::removeItem(ItemType item) {
  listNode<ItemType> *temp = m_head;
  int index = 0;
  int indexOfItem = 0;
  while (temp != nullptr) {
    if (temp->item == item) {
      indexOfItem = index;
    }
    temp = temp->next;
    index++;
  }
  this->removeAtIndex(indexOfItem);
}

template <typename ItemType>
void LinkedList<ItemType>::insertFront(ItemType item) {
  struct listNode<ItemType> *temp = new listNode<ItemType>();
  temp->item = item;
  if (m_head == nullptr) {
    temp->next = nullptr;
  } else {
    temp->next = m_head;
  }
  m_head = temp;
  temp = nullptr;
  m_length++;
}

template <typename ItemType>
bool LinkedList<ItemType>::find(ItemType item) const {
  listNode<ItemType> *temp = m_head;
  while (temp != nullptr) {
    if (temp->item == item) {
      temp = nullptr;
      return true;
    }
    temp = temp->next;
  }
  temp = nullptr;
  return false;
}

template <typename ItemType>
void LinkedList<ItemType>::insertBack(ItemType item) {
  struct listNode<ItemType> *temp;
  if (m_head == nullptr) {
    temp = new listNode<ItemType>(item, nullptr);
    m_head = temp;
  } else {
    temp = m_head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = new listNode<ItemType>(item, nullptr);
  }
  temp = nullptr;
  m_length++;
}

template <typename ItemType>
ItemType LinkedList<ItemType>::getItemAtIndex(int index) const {
  if (index < 0 || index > m_length-1) 
    throw std::runtime_error("list index out of range");

  listNode<ItemType>* temp = m_head;
  ItemType item;
  int i = 0;

  while (i < index) {
    temp = temp->next;
    i++;
  }
  item = temp->item;
  temp = nullptr;
  return item;
}

template <typename ItemType>
void LinkedList<ItemType>::printList() const {
  struct listNode<ItemType> *temp = m_head;
  for (int i = 0; i < m_length; i++) {
    std::cout << temp->item << " ";    
    temp = temp->next;
  }
  std::cout << "\n";
}

#endif
