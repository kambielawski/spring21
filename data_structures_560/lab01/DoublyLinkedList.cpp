template <typename ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList() : head(nullptr), tail(nullptr), m_length(0) {}

template <typename ItemType>
DoublyLinkedList<ItemType>::~DoublyLinkedList()
{
    while (m_length != 0)
    {
        this->deleteItem(this->getItemAtIndex(0));
    }
}

/* returns index if found, -1 if not found */
template <typename ItemType>
int DoublyLinkedList<ItemType>::find(ItemType value) const
{
    int index = 0;
    ListNode<ItemType> *temp = head;
    while (temp != nullptr)
    {
        if (temp->value == value)
        {
            temp = nullptr;
            return index;
        }
        index++;
        temp = temp->next;
    }
    temp = nullptr;
    return -1;
}

template <typename ItemType>
bool DoublyLinkedList<ItemType>::isEmpty() const
{
    return m_length == 0;
}

template <typename ItemType>
int DoublyLinkedList<ItemType>::length()
{
    return m_length;
}

template <typename ItemType>
void DoublyLinkedList<ItemType>::insertItem(ItemType value)
{
    ListNode<ItemType> *newNode = new ListNode<ItemType>;
    newNode->value = value;

    if (tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->prev = tail;
        tail->next = newNode; 
        tail = tail->next;
    }
    m_length++;
}

/* deletes first instance of value */
template <typename ItemType>
void DoublyLinkedList<ItemType>::deleteItem(ItemType value)
{
    ListNode<ItemType> *temp = head;
    while (temp != nullptr)
    {
        if (temp->value == value)
        {
            if (temp == head && temp == tail)
            {
                head = nullptr;
                tail = nullptr;
            } 
            else if (temp == head)
            {
                head = head->next;
                temp->next = nullptr;
            }
            else if (temp == tail)
            {
                tail = tail->prev;
                temp->prev = nullptr;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp->next = nullptr;
                temp->prev = nullptr;
            }

            delete temp;
            temp = nullptr;
            m_length--;
            return;
        }
        temp = temp->next;
    }
}

template <typename ItemType>
ItemType DoublyLinkedList<ItemType>::getItemAtIndex(int index)
{
    int count = 0;
    ItemType returnVal;
    ListNode<ItemType> *temp = head;
    while (count < index)
    {
        temp = temp->next; 
        count++;
    }
    returnVal = temp->value;
    temp = nullptr;
    return returnVal;
}
