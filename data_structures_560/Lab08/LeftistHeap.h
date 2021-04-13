#include <iostream>
#include <math.h>
using namespace std;


template <typename ItemType>
struct Node {
    int rank;
    int key;
    ItemType item;
    Node<ItemType> *lchild;
    Node<ItemType> *rchild;

    ~Node() {
        delete lchild;
        delete rchild;
    }
};

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

template <typename ItemType>
class LeftistHeap
{
private:
Node<ItemType> *m_root;
Node<ItemType> *m_side_heap_root;
int m_size;

/* Helper functions */
void swapChildren(Node<ItemType> *h);
int getDepth(Node<ItemType> *node, int level) const;

public:
LeftistHeap();
LeftistHeap(Node<ItemType> *node);
~LeftistHeap();
ItemType deleteMin();
ItemType findMin() const;
void insert(ItemType item, int key);
bool isEmpty() const;
void inorderTraversal() const;
void inorderTraversal(Node<ItemType> *node) const;
void levelOrderTraversal() const;
void levelOrderTraversal(Node<ItemType> *node, int level, int count) const;

Node<ItemType>* getRoot() const;
Node<ItemType>* merge(Node<ItemType> *a, Node<ItemType> *b);
void insertSideHeap(int key, ItemType item);
void mergeSideHeap();


};

#include "LeftistHeap.cpp"

#endif
