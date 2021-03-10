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
void remove(BTNode<ItemType> *root, int key);
void deleteMin();
void deleteMax();
bool find(int key) const;
bool find(BTNode<ItemType> *node, int key) const;
ItemType findMin() const;
ItemType findMin(BTNode<ItemType> *root) const;
BTNode<ItemType>* findMinNode(BTNode<ItemType> *root) const;
ItemType findMax() const;
ItemType findMax(BTNode<ItemType> *root) const;
ItemType inorderSuccessor(int key) const;
void inorderSuccessor(BTNode<ItemType> *root, BTNode<ItemType> *succ, int key) const;
void printLevelOrder() const;
void printLevel(BTNode<ItemType> *root, int level) const;
void printSpiralOrder() const;
void inorderPrint() const;
void postorderPrint() const;
void preorderPrint() const;
void inorderPrint(BTNode<ItemType> *node) const;
void postorderPrint(BTNode<ItemType> *node) const;
void preorderPrint(BTNode<ItemType> *node) const;
void leftSideView() const;
void rightSideView() const;
int height(BTNode<ItemType>* node) const;

};

#include "BinarySearchTree.cpp"

#endif
