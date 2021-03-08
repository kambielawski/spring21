#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <typename ItemType>
struct BTNode {
    int key;
    ItemType item;
    BTNode<ItemType> *lchild;
    BTNode<ItemType> *rchild;
};

template <typename ItemType>
class BinarySearchTree {
private:
BTNode<ItemType> *m_root;
int m_numItems;

public:
BinarySearchTree();
~BinarySearchTree();
void insert(int key, ItemType item);
void insert(BTNode<ItemType> *parent, BTNode<ItemType> *newItem);
void remove(int key);
void deleteMin();
void deleteMax();
ItemType findMin() const;
ItemType findMax() const;
ItemType inorderSuccessor(int key) const;
void printLevelOrder() const;
void printLevel(BTNode<ItemType> *root, int level) const;
void printSpiralOrder() const;
void leftSideView() const;
void rightSideView() const;
int height(BTNode<ItemType>* node) const;

};

#include "BinarySearchTree.cpp"

#endif
