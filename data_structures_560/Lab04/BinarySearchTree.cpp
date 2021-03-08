#include <iostream>
using namespace std;

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree () : m_root(nullptr), m_numItems(0) {}

template <typename ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree () {}

template <typename ItemType>
int BinarySearchTree<ItemType>::height(BTNode<ItemType>* node) const
{
    if (node == nullptr)
        return 0;
    
    int left_height = height(node->lchild);
    int right_height = height(node->rchild);

    if (left_height < right_height)
        return right_height + 1;
    else
        return left_height + 1;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::insert (int key, ItemType item)
{
    BTNode<ItemType> *newItem = new BTNode<ItemType>();
    newItem->key = key;
    newItem->item = item;
    if (m_root == nullptr) {
        newItem->lchild = nullptr;
        newItem->rchild = nullptr;
        m_root = newItem;
    } else {
        this->insert(m_root, newItem);
    }
    m_numItems++;
    newItem = nullptr;
}

/*
 * Recursive insert
*/
template <typename ItemType>
void BinarySearchTree<ItemType>::insert(BTNode<ItemType> *parent, BTNode<ItemType> *newItem)
{
    // left subtree
    if (newItem->key < parent->key) {
        // check if parent's left child is empty; if so, insert and return
        if (parent->lchild == nullptr) {
            parent->lchild = newItem;
            return;
        // otherwise, recurse on left child
        } else {
            this->insert(parent->lchild, newItem);
        }
    // right subtree
    } else {
        if (parent->rchild == nullptr) {
            parent->rchild = newItem;
        } else {
            this->insert(parent->rchild, newItem);
        }
    }
}

template <typename ItemType>
void BinarySearchTree<ItemType>::remove (int key)
{

}

template <typename ItemType>
void BinarySearchTree<ItemType>::deleteMin ()
{

}

template <typename ItemType>
void BinarySearchTree<ItemType>::deleteMax ()
{

}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMin () const
{
    if (m_root == nullptr)
        throw runtime_error("Cannot find min of empty tree");
    
    BTNode<ItemType> *temp = m_root;
    while (temp->lchild != nullptr)
        temp = temp->lchild;

    ItemType ret = temp->item;
    temp = nullptr;
    return ret;
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMax () const
{
    if (m_root == nullptr)
        throw runtime_error("Cannot find max of empty tree");
    
    BTNode<ItemType> *temp = m_root;
    while (temp->rchild != nullptr)
        temp = temp->rchild;

    ItemType ret = temp->item;
    temp = nullptr;
    return ret;
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::inorderSuccessor (int key) const
{

}

template <typename ItemType>
void BinarySearchTree<ItemType>::printLevelOrder () const
{
    for (int i = 0; i < this->height(m_root); i++) {
        this->printLevel(m_root, i);
        cout << endl;
    }
}

template <typename ItemType>
void BinarySearchTree<ItemType>::printLevel (BTNode<ItemType> *root, int level) const
{
    if (root == nullptr)
        return;
    else if (level == 0)
        cout << root->item << " ";
    else {
        printLevel(root->lchild, level-1);
        printLevel(root->rchild, level-1);
    }

}

template <typename ItemType>
void BinarySearchTree<ItemType>::printSpiralOrder () const
{

}

template <typename ItemType>
void BinarySearchTree<ItemType>::leftSideView () const
{

}

template <typename ItemType>
void BinarySearchTree<ItemType>::rightSideView () const
{

}





