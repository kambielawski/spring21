#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <typename ItemType>
struct BTNode {
    int key;
    ItemType item;
    BTNode *lchild;
    BTNode *rchild;
};

template <typename ItemType>
class BinarySearchTree {
private:
BTNode<ItemType> *m_root;

public:
BinarySearchTree();
~BinarySearchTree();
void insert(int key, ItemType item);
void remove(int key);
void deleteMin();
void deleteMax();
ItemType findMin() const;
ItemType findMax() const;
ItemType inorderSuccessor(int key) const;
void printLevelOrder() const;
void printSpiralOrder() const;
void leftSideView() const;
void rightSideView() const;

};

#endif
