/*! -------------------------------------------------------------------------*\
|   Singly-linked list after https://en.wikipedia.org/wiki/Linked_list
\*---------------------------------------------------------------------------*/
#ifndef SLINKY_SLINKY_HPP
#define SLINKY_SLINKY_HPP

#include <stdexcept>
#include <vector>

//! \struct ListNode
template <typename DataT>
struct ListNode
{
    ListNode()
        : next(nullptr)
    {
    }

    ListNode(DataT data)
        : data(std::move(data))
        , next(nullptr)
    {
    }

    DataT data;
    ListNode<DataT>* next;
};

//! \class Slinky
template <typename DataT>
class Slinky
{
public:
    //!
    Slinky()
        : m_head(new ListNode<DataT>)
        , m_size(0)
    {
    }

    //!
    Slinky(const Slinky& other)
        : m_head(new ListNode<DataT>)
        , m_size(0)
    {
        Copy(other);
    }

    //!
    Slinky& operator=(const Slinky& other)
    {
        if (&other != this)
        {
            Clear();
            Copy(other);
        }

        return *this;
    }

    //! Move constructor
    //! \see
    //! http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Slinky(Slinky&& other)
        : m_head(new ListNode<DataT>)
        , m_size(other.m_size)
    {
        // Pilfer other's resources
        m_head->next = other.Head();
        m_size       = other.m_size;

        // Reset other to default state
        other.m_head->next = nullptr;
        other.m_size       = 0;
    }

    //! Move assignment operator
    //! \see
    //! http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Slinky& operator=(Slinky&& other)
    {
        if (&other != this)
        {
            // Release the current object's resources
            Clear();

            // Pilfer other's resources
            m_head->next = other.Head();
            m_size       = other.m_size;

            // Reset other to default state
            other.m_head->next = nullptr;
            other.m_size       = 0;
        }

        return *this;
    }

    //!
    virtual ~Slinky()
    {
        Clear();
        delete m_head;
    }

    //! \fn     Append
    //! brief   Appends a value to the list's end
    void Append(const DataT& data)
    {
        if (m_head->next == nullptr)
        {
            Append(m_head, data);
            return;
        }
        else
        {
            auto node = m_head->next;
            for (node; node != nullptr; node = node->next)
            {
                if (node->next == nullptr)
                {
                    Append(node, data);
                    return;
                }
            }
        }
    }

    //! \fn     Clear
    //! \brief  Traverses the list and deletes all nodes
    void Clear()
    {
        if (!IsEmpty())
        {
            ListNode<DataT>* it = m_head->next;
            while (it != nullptr)
            {
                ListNode<DataT>* temp = it->next;
                delete it;
                it = temp;
            }
        }

        m_head->next = nullptr;
        m_size       = 0;
    }

    //! \fn     Delete
    //! /brief  Deletes the node after the list head
    ListNode<DataT>* Delete()
    {
        if (!IsEmpty())
        {
            ListNode<DataT>* temp = m_head->next->next;
            delete m_head->next;
            m_head->next = temp;

            --m_size;
        }
    }

    //! \fn     Delete
    //! \brief  Deletes the given node
    ListNode<DataT>* Delete(ListNode<DataT>* target)
    {
        if (!IsEmpty())
        {
            for (auto node = m_head->next, prev = m_head; node != nullptr;
                 prev = prev->next, node = node->next)
            {
                if (node == target)
                {
                    ListNode<DataT>* temp = node->next;
                    prev->next            = temp;
                    delete node;
                    --m_size;
                }
            }
        }
    }

    //! \fn     First
    //! \brief  Returns the first object in the list
    DataT First() const
    {
        if (!IsEmpty())
        {
            return m_head->next->data;
        }
        else
        {
            throw std::out_of_range("Slinky::First: list is empty");
        }
    }

    //! \fn     Get
    //! \brief  Returns the object at the given index
    DataT Get(std::size_t index) const
    {
        if (index > m_size)
        {
            throw std::out_of_range("Slinky::Get(): index is out of range");
        }

        std::size_t where = 0;
        for (ListNode<DataT>* node = m_head->next; node != nullptr; node = node->next)
        {
            if (where == index)
            {
                return node->data;
            }

            ++where;
        }
    }

    //! \fn     Head
    //! \brief  Gets the first node of the list
    ListNode<DataT>* Head()
    {
        return m_head->next;
    }

    //! \fn     Insert
    //! \brief  Inserts new node after list head
    ListNode<DataT>* Insert(ListNode<DataT>* new_node)
    {
        new_node->next = m_head->next;
        m_head->next   = new_node;
        ++m_size;

        return new_node;
    }

    //! \fn     Insert
    //! \brief  Inserts new node after given node
    ListNode<DataT>* Insert(ListNode<DataT>* node, ListNode<DataT>* new_node)
    {
        new_node->next = node->next;
        node->next     = new_node;
        ++m_size;

        return new_node;
    }

    //! \fn     IsEmpty
    bool IsEmpty() const
    {
        return m_head->next == nullptr;
    }

    //! \fn     Last
    //! \brief  Returns the last object in the list
    DataT Last() const
    {
        if (!IsEmpty())
        {
            auto node = m_head->next;
            for (node; node != nullptr; node = node->next)
            {
                if (node->next == nullptr)
                {
                    return node->data;
                }
            }
        }
        else
        {
            throw std::out_of_range("Slinky::Last: list is empty");
        }
    }

    //! \tn     Prepend
    void Prepend(const DataT& data)
    {
        if (m_head->next == nullptr)
        {
            m_head->next = new ListNode<DataT>(data);
            ++m_size;
        }
        else
        {
            ListNode<DataT>* temp = m_head->next;
            m_head->next          = new ListNode<DataT>(data);
            m_head->next->next    = temp;
            ++m_size;
        }
    }

    //! \fn     PrintList
    std::vector<DataT> PrintList()
    {
        m_contents.clear();
        if (!IsEmpty())
        {
            for (auto it = m_head->next; it != nullptr; it = it->next)
            {
                m_contents.push_back(it->data);
            }
        }

        return std::vector<DataT>(m_contents.begin(), m_contents.end());
    }

    //! \fn     Remove
    //! \brief  Removes the given object from the list
    void Remove(const DataT& data)
    {
        if (!IsEmpty())
        {
            for (auto node = m_head->next; node != nullptr; node = node->next)
            {
                if (node->data == data)
                {
                    Delete(node);
                }
            }
        }
    }

    //! \fn     RemoveAll
    //! \brief  Removes all objects from the list
    void RemoveAll()
    {
        Clear();
    }

    //! \fn     RemoveFirst
    //! \brief  Removes the first object from the list
    void RemoveFirst()
    {
        Delete();
    }

    //! \fn     RemoveLast
    //! \brief  Removes the last object from the list
    void RemoveLast()
    {
        if (!IsEmpty())
        {
            for (auto node = m_head->next; node != nullptr; node = node->next)
            {
                if (node->next == nullptr)
                {
                    Delete(node);
                }
            }
        }
    }

    //! \fn     Reverse
    //! \brief  Recursive list reversal
    void Reverse()
    {
        if (!IsEmpty())
        {
            ListNode<DataT>* new_head = DoReverse(m_head->next, m_head);
            // Terminate new tail, point to new head
            m_head->next->next = nullptr;
            m_head->next       = new_head;
        }
    }

    //! \fn     ReverseList
    //! \brief  Interview practice problem
    void ReverseList()
    {
        if (!IsEmpty())
        {
            ListNode<DataT>* tail     = nullptr;
            ListNode<DataT>* previous = nullptr;

            ListNode<DataT>* node = m_head;

            while (node != nullptr)
            {
                ListNode<DataT>* next = node->next;

                // We've reached the end of the list; store the tail
                if (next == nullptr)
                {
                    tail = node;
                }

                // If it's not the first node,
                // reverse its next pointer to its predecessor
                node->next = (previous == m_head) ? nullptr : previous;

                // Move along
                previous = node;
                node     = next;
            }

            m_head->next = tail;
        }
    }

    //! \fn     Search
    ListNode<DataT>* Search(const DataT& data)
    {
        return DoSearch(m_head->next, data);
    }

    //! \fn     Size
    std::size_t Size() const
    {
        return m_size;
    }

private:
    //! \fn     Append
    //! \brief  Effects the Append operation
    void Append(ListNode<DataT>* current, const DataT& data)
    {
        auto newnode  = new ListNode<DataT>(data);
        current->next = newnode;
        ++m_size;
        return;
    }

    //! \fn     Copy
    void Copy(const Slinky& other)
    {
        for (auto i = 0; i < other.Size(); ++i)
        {
            Append(other.Get(i));
        }
    }

    //! \fn     Copy
    void Copy(Slinky& other)
    {
        for (auto i = 0; i < other.Size(); ++i)
        {
            Append(other.Get(i));
        }
    }

    //! \fn     DoReverse
    ListNode<DataT>* DoReverse(ListNode<DataT>* current, ListNode<DataT>* previous)
    {
        ListNode<DataT>* temp = current;
        if (temp->next == nullptr)
        {
            // At end of list, start reversing links
            temp->next = previous;
            return temp;
        }
        else
        {
            temp          = DoReverse(current->next, current);
            current->next = previous;
            return temp;
        }
    }

    //! \fn     DoSearch
    ListNode<DataT>* DoSearch(ListNode<DataT>* node, const DataT& data)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->data == data)
        {
            return node;
        }
        else
        {
            return DoSearch(node->next, data);
        }
    }

    ListNode<DataT>* m_head;
    std::size_t m_size;
    std::vector<DataT> m_contents;
};

#endif // SLINKY_SLINKY_HPP
