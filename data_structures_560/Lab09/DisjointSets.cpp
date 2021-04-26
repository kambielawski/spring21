template <typename ItemType>
DisjointSets<ItemType>::DisjointSets()
{

}

template <typename ItemType>
DisjointSets<ItemType>::~DisjointSets()
{
    delete [] disjoint_sets;
    disjoint_sets = nullptr;
}

template <typename ItemType>
void DisjointSets<ItemType>::makeSet(ItemType* item_arr, int size)
{
    num_items = size;
    disjoint_sets = new DSNode<ItemType>[size];
    for (int i = 0; i < size; i++) {
        disjoint_sets[i].item = item_arr[i];
        disjoint_sets[i].key = i;
        disjoint_sets[i].rank = 0;
        disjoint_sets[i].parent = nullptr;
    }
}

template <typename ItemType>
DSNode<ItemType>* DisjointSets<ItemType>::find(ItemType item)
{
    for (int i = 0; i < num_items; i++) {
        if (disjoint_sets[i].item == item) {
            return this->getRepresentativeElement(&disjoint_sets[i]);
        }
    }

    return nullptr;
}

template <typename ItemType>
ItemType DisjointSets<ItemType>::findItem(ItemType item)
{
    DSNode<ItemType>* node = this->find(item);

    if (node == nullptr)
        throw runtime_error("Couldn't find item in disjoint sets\n");

    return node->item;
}

template <typename ItemType>
DSNode<ItemType>* DisjointSets<ItemType>::getRepresentativeElement(DSNode<ItemType>* node)
{
    DSNode<ItemType>* temp = node;
    while (temp->parent != nullptr) {
        temp = temp->parent;
    }

    return temp;
}

template <typename ItemType>
void DisjointSets<ItemType>::printPath(ItemType item) const
{
    DSNode<ItemType> *node = nullptr;
    for (int i = 0; i < num_items; i++) {
        if (disjoint_sets[i].item == item)
            node = &disjoint_sets[i]; 
    }

    if (node == nullptr)
        throw runtime_error("Couldn't find item in disjoint sets\n");

    DSNode<ItemType> *temp = node;
    cout << "The path for element " << item << " is: ";
    cout << temp->item;
    while (temp->parent != nullptr) {
        cout << "->" << temp->parent->item;
        temp = temp->parent;
    }
    cout << endl;

    node = nullptr;
}

template <typename ItemType>
void DisjointSets<ItemType>::pathCompression(ItemType item)
{
    DSNode<ItemType> *temp = nullptr;
    DSNode<ItemType> *temp2 = nullptr;

    /* Find element in array */
    for (int i = 0; i < num_items; i++) {
        if (disjoint_sets[i].item == item)
            temp = &disjoint_sets[i]; 
    }

    if (temp == nullptr)
        throw runtime_error("Couldn't find item\n");

    /* Get item at root */
    DSNode<ItemType> *representative_element = this->getRepresentativeElement(temp);

    /* Compress path */
    while (temp->parent->item != representative_element->item) {
        temp2 = temp->parent;
        temp->parent = representative_element;
        temp = temp2;
    }

    representative_element = nullptr;
    temp = nullptr;
    temp2 = nullptr;
}

template <typename ItemType>
void DisjointSets<ItemType>::unionByRank(ItemType item1, ItemType item2)
{
    DSNode<ItemType>* node1 = nullptr;
    DSNode<ItemType>* node2 = nullptr;

    /* Get pointers to nodes for items */
    for (int i = 0; i < num_items; i++) {
        if (disjoint_sets[i].item == item1)
            node1 = &disjoint_sets[i];
        if (disjoint_sets[i].item == item2)
            node2 = &disjoint_sets[i];
    }

    if (node1 == nullptr || node2 == nullptr)
        throw runtime_error("Couldn't find at least one of the elements specified\n");

    /* Grab the representative elements */
    node1 = this->getRepresentativeElement(node1);
    node2 = this->getRepresentativeElement(node2);

    /* Assign new parents and ranks accordingly */
    if ((node1->rank) < (node2->rank)) {
        node1->parent = node2;
    } else if (node1->rank == node2->rank) {
        if (node1->item < node2->item) {
            node1->parent = node2;
            node2->rank++;
        } else {
            node2->parent = node1;
            node1->rank++;
        }
    } else {
        node2->parent = node1;
    }

    node1 = nullptr;
    node2 = nullptr;
}

template <typename ItemType>
void DisjointSets<ItemType>::printSets() const
{
    for (int i = 0; i < num_items; i++)
        cout << disjoint_sets[i].item << endl;
}
