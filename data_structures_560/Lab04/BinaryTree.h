#ifndef BINARY_TREE_H
#define BINARY_TREE_H

class BinaryTree : public BinaryTreeInterface {
private:
BTNode<ItemType> *m_root;

public:
BinaryTree();
~BinaryTree();

};

BinaryTree::BinaryTree() : m_root(nullptr) {}

BinaryTree::~BinaryTree() {}

#endif
