#include <iostream>
using namespace std;

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree () : m_root(nullptr), m_numItems(0) {}

template <typename ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree ()
{
    while (m_numItems > 0) {
        if (m_numItems % 2 == 0)
            this->deleteMin();
        else
            this->deleteMax();
    }
}

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
    if (!this->find(key))
        throw runtime_error("Couldn't remove item: not in tree");
    
    this->remove(m_root, key);
    m_numItems--;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::remove (BTNode<ItemType> *root, int key)
{
    BTNode<ItemType> *parent = nullptr;
    BTNode<ItemType> *current = root;
    
    // get to the node to be deleted
    while (current->key != key) {
        parent = current;
        if (key < current->key)
            current = current->lchild;
        else
            current = current->rchild;
    }

    // case 1: node has no children
    if (current->lchild == nullptr && current->rchild == nullptr) {
        if (current == m_root) {
            m_root = nullptr;
        } else {
            // use parent pointer to delete child node
            if (parent->lchild == current)
                parent->lchild = nullptr;
            else
                parent->rchild = nullptr;
        }
    }
    // case 2: node has 2 children
    else if (current->lchild && current->rchild) {
        // inorder successor
        BTNode<ItemType> *succ = this->findMinNode(current->rchild);
        int minNodeKey = succ->key;
        // recursively delete successor (it will have max 1 child)
        this->remove(root, succ->key);
        current->key = minNodeKey;
    }
    // case 3: node has 1 child
    else {
        BTNode<ItemType> *child;
        if (current->lchild)
            child = current->lchild;
        else
            child = current->rchild;

        // if we're deleting the root
        if (current == root) {
            root = child;
        } else {
            if (current == parent->lchild)
                parent->lchild = child;
            else
                parent->rchild = child;
        }
    }

    delete current;
    current = nullptr;
    parent = nullptr;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::deleteMin ()
{
    if (m_root == nullptr) {
        throw runtime_error("Cannot delete minimum of empty tree");
    }

    BTNode<ItemType> *temp = m_root;
    BTNode<ItemType> *temp2 = nullptr;
    while (temp->lchild != nullptr) {
        temp2 = temp;
        temp = temp->lchild;
    }
    // point min's parent's lchild to min's rchild
    if (temp2 != nullptr)
        temp2->lchild = temp->rchild;
    if (temp == m_root) {
        if (m_root->rchild)
            m_root = m_root->rchild;
        else
            m_root = nullptr;
    }
    
    // clean up pointers
    temp->lchild = nullptr;
    temp->rchild = nullptr;
    delete temp;
    temp = nullptr;
    temp2 = nullptr;

    m_numItems--;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::deleteMax ()
{
    if (m_root == nullptr) {
        throw runtime_error("Cannot delete maximum of empty tree");
    }

    BTNode<ItemType> *temp = m_root;
    BTNode<ItemType> *temp2 = nullptr;
    while (temp->rchild != nullptr) {
        temp2 = temp;
        temp = temp->rchild;
    }
    // point min's parent's lchild to min's rchild
    if (temp2 != nullptr)
        temp2->rchild = temp->lchild;
    // check if max is the root node
    if (temp == m_root) {
        if (m_root->lchild)
            m_root = m_root->lchild;
        else
            m_root = nullptr;
    }

    // clean up pointers
    temp->rchild = nullptr;
    temp->lchild = nullptr;
    delete temp;
    temp = nullptr;
    temp2 = nullptr;

    m_numItems--;

}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMin () const
{
    return this->findMin(m_root);
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMin (BTNode<ItemType> *root) const
{
    if (root == nullptr)
        return NULL;
    
    BTNode<ItemType> *temp = root;
    while (temp->lchild != nullptr)
        temp = temp->lchild;

    ItemType ret = temp->item;
    temp = nullptr;
    return ret;
}

template <typename ItemType>
BTNode<ItemType>* BinarySearchTree<ItemType>::findMinNode(BTNode<ItemType> *root) const
{
    if (root == nullptr)
        return nullptr;

    BTNode<ItemType> *temp = root;
    while (temp->lchild != nullptr)
        temp = temp->lchild;

    return temp;
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMax () const
{
    return this->findMax(m_root);
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findMax (BTNode<ItemType> *root) const
{
    if (root == nullptr)
        throw runtime_error("Cannot find max of empty tree");
    
    BTNode<ItemType> *temp = root;
    while (temp->rchild != nullptr)
        temp = temp->rchild;

    ItemType ret = temp->item;
    temp = nullptr;
    return ret;
}

template <typename ItemType>
bool BinarySearchTree<ItemType>::find(int key) const
{
    if (m_root == nullptr)
        return false;

    return this->find(m_root, key);
}

template <typename ItemType>
bool BinarySearchTree<ItemType>::find(BTNode<ItemType> *node, int key) const
{
    if (node == nullptr)
        return false;
    else if (node->key == key)
        return true;
    return this->find(node->lchild, key) || this->find(node->rchild, key);

}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::inorderSuccessor (int key) const
{
    if (!this->find(key))
        throw runtime_error("Couldn't find item in tree");
    
    BTNode<ItemType> *succ = nullptr;
    this->inorderSuccessor(m_root, succ, key);
    ItemType ret;
    if (succ == nullptr)
        throw runtime_error("No inorder successor of item");
    ret = succ->item;
    succ = nullptr;
    return ret;
    
}

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderSuccessor (BTNode<ItemType> *root, BTNode<ItemType> *succ, int key) const
{
    if (root == nullptr) {
        // succ = nullptr;
        return;
    }

    if (root->key == key) {
        if (root->rchild) {
            succ = this->findMinNode(root->rchild);
            return;
        }
    } else if (key < root->key) {
        succ = root;
        this->inorderSuccessor(root->lchild, succ, key);
    } else {
        this->inorderSuccessor(root->rchild, succ, key);
    }
        
}

template <typename ItemType>
void BinarySearchTree<ItemType>::printLevelOrder () const
{
    for (int i = 0; i < this->height(m_root); i++) {
        this->printLevel(m_root, i);
    }
    cout << endl;
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

template <typename ItemType>
void BinarySearchTree<ItemType>::preorderPrint() const
{
    this->preorderPrint(m_root);
    cout << endl;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderPrint() const
{
    this->inorderPrint(m_root);
    cout << endl;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::postorderPrint() const
{
    this->postorderPrint(m_root);
    cout << endl;
}


template <typename ItemType>
void BinarySearchTree<ItemType>::preorderPrint(BTNode<ItemType> *node) const
{
    if (node == nullptr)
        return;

    cout << node->item << ", ";
    preorderPrint(node->lchild);
    preorderPrint(node->rchild);
}

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderPrint(BTNode<ItemType> *node) const
{
    if (node == nullptr)
        return;

    inorderPrint(node->lchild);
    cout << node->item << ", ";
    inorderPrint(node->rchild);
}

template <typename ItemType>
void BinarySearchTree<ItemType>::postorderPrint(BTNode<ItemType> *node) const
{
    if (node == nullptr)
        return;

    postorderPrint(node->lchild);
    postorderPrint(node->rchild);
    cout << node->item << ", ";
}

