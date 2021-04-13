
template <typename ItemType>
LeftistHeap<ItemType>::LeftistHeap() : m_root(nullptr), m_size(0), m_side_heap_root(nullptr)
{
    
}


template <typename ItemType>
LeftistHeap<ItemType>::LeftistHeap(Node<ItemType> *node) : m_root(node), m_size(0)
{
        
}


template <typename ItemType>
LeftistHeap<ItemType>::~LeftistHeap()
{
    delete m_root;
}


template <typename ItemType>
Node<ItemType>* LeftistHeap<ItemType>::merge(Node<ItemType> *a, Node<ItemType> *b)
{
    /* return base cases */
    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    /* swap labels if root of a > root of b */
    if (a->key > b->key) {
        Node<ItemType> *temp = a;
        a = b;
        b = temp;
        temp = nullptr;
    }

    /* if we don't have a left child, just set b to it and return */
    /* this is because if we don't have a lchild, we don't have a rchild (by leftist heap property) */
    if (a->lchild == nullptr) {
        a->lchild = b;
        return a;
    } 

    /* set right child of a to merger of b and right subtree of a */
    a->rchild = this->merge(a->rchild, b);

    /* swap if ranks are backward */
    if (a->rchild->rank > a->lchild->rank)
        this->swapChildren(a);

    /* update rank of a */
    a->rank = a->rchild->rank + 1;
    
    return a;
}


template <typename ItemType>
void LeftistHeap<ItemType>::insert(ItemType item, int key)
{
    Node<ItemType> *new_item = new Node<ItemType>;
    new_item->item = item;
    new_item->key = key;
    new_item->lchild = nullptr;
    new_item->rchild = nullptr;
    new_item->rank = 1;

    /* insert by concatentation */
    m_root = this->merge(m_root, new_item);
}


template <typename ItemType>
ItemType LeftistHeap<ItemType>::deleteMin() 
{
    if (m_root == nullptr)
        throw runtime_error("Can't delete min of empty tree\n");

    int ret = m_root->item;

    Node<ItemType> *left = m_root->lchild;
    Node<ItemType> *right = m_root->rchild;

    m_root->lchild = nullptr;
    m_root->rchild = nullptr;
    delete m_root;

    m_root = this->merge(left, right);

    return ret;
}


template <typename ItemType>
ItemType LeftistHeap<ItemType>::findMin() const
{
    if (m_root == nullptr)
        throw runtime_error("Can't find min of empty tree\n");

    return m_root->item;
}


template <typename ItemType>
Node<ItemType>* LeftistHeap<ItemType>::getRoot() const
{
    return m_root;
}


template <typename ItemType>
void LeftistHeap<ItemType>::swapChildren(Node<ItemType> *h)
{
    Node<ItemType> *temp = h->lchild;
    h->lchild = h->rchild;
    h->rchild = temp;

    temp = nullptr;
}


template <typename ItemType>
bool LeftistHeap<ItemType>::isEmpty() const
{
    return m_size == 0;
}


template <typename ItemType>
void LeftistHeap<ItemType>::inorderTraversal() const
{
    if (m_root == nullptr)
        return;

    this->inorderTraversal(m_root);
    cout << "\n";
}


template <typename ItemType>
int LeftistHeap<ItemType>::getDepth(Node<ItemType> *node, int level) const
{
    if (node == nullptr)
        return 0;
    int left_depth = getDepth(node->lchild, level+1);
    int right_depth = getDepth(node->rchild, level+1);
    if (left_depth > right_depth)
        return left_depth + 1;
    else
        return right_depth + 1;
}


template <typename ItemType>
void LeftistHeap<ItemType>::levelOrderTraversal() const
{
    int depth = this->getDepth(m_root, 0);
    for (int i = 0; i < depth; i++) {
        this->levelOrderTraversal(m_root, i, 0);
        cout << endl;
    }
}


template <typename ItemType>
void LeftistHeap<ItemType>::levelOrderTraversal(Node<ItemType> *node, int level, int count) const
{
    if (node == nullptr)
        return;
    else if (level == count)
        cout << node->item << ", ";
    else {
        levelOrderTraversal(node->lchild, level, count+1);
        levelOrderTraversal(node->rchild, level, count+1);
    }
}


template <typename ItemType>
void LeftistHeap<ItemType>::inorderTraversal(Node<ItemType> *node) const
{
    if (node == nullptr) return;

    inorderTraversal(node->lchild);
    cout << node->item << ", ";
    inorderTraversal(node->rchild);
}


template <typename ItemType>
void LeftistHeap<ItemType>::insertSideHeap(int key, ItemType item)
{
    Node<ItemType> *new_item = new Node<ItemType>;
    new_item->item = item;
    new_item->key = key;
    new_item->lchild = nullptr;
    new_item->rchild = nullptr;
    new_item->rank = 1;

    m_side_heap_root = this->merge(m_side_heap_root, new_item);
}


template <typename ItemType>
void LeftistHeap<ItemType>::mergeSideHeap()
{
    m_root = this->merge(m_root, m_side_heap_root);
    m_side_heap_root = nullptr;
}








