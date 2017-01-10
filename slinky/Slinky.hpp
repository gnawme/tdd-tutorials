/*! -------------------------------------------------------------------------*\
|   Singly-linked list after https://en.wikipedia.org/wiki/Linked_list
\*---------------------------------------------------------------------------*/
#ifndef SLINKY_SLINKY_HPP
#define SLINKY_SLINKY_HPP

#include <vector>

//! \struct ListNode
template<typename DataT>
struct ListNode
{
    ListNode()
    : next(nullptr)
    {}

    ListNode(DataT data)
    : data(data)
    , next(nullptr)
    {}

    DataT               data;
    ListNode<DataT>*    next;
};

//! \class Slinky
template<typename DataT>
class Slinky
{
public:
    Slinky()
    : m_head(new ListNode<DataT>)
    , m_size(0)
    {}

    ~Slinky()
    {
        delete m_head;
    }

    //! \fn     Clear
    //! \brief  Traverses the list and deletes all nodes
    void Clear()
    {
        if (!IsEmpty()) {
            ListNode<DataT> *it = m_head->next;
            while (it != nullptr) {
                ListNode<DataT> *temp = it->next;
                delete it;
                --m_size;

                it = temp;
            }
        }
    }

    //! \fn     Delete
    //! /brief  Deletes the node after the list head
    ListNode<DataT>* Delete()
    {
        if (!IsEmpty()) {
            ListNode<DataT>* temp = m_head->next->next;
            delete m_head->next;
            m_head->next = temp;

            --m_size;
        }
    }

    //! \fn     Delete
    //! \brief  Deletes the node after the given node
    ListNode<DataT>* Delete(ListNode<DataT>* node)
    {
        ListNode<DataT>* temp = node->next->next;
        delete node->next;
        node->next = temp;
        --m_size;
    }

    //! \fn     Insert
    //! \brief  Inserts new node after list head
    ListNode<DataT>* Insert(ListNode<DataT>* new_node)
    {
        new_node->next = m_head->next;
        m_head->next = new_node;
        ++m_size;

        return new_node;
    }


    //! \fn     Insert
    //! \brief  Inserts new node after given node
    ListNode<DataT>* Insert(ListNode<DataT>* node, ListNode<DataT>* new_node)
    {
        new_node->next = node->next;
        node->next = new_node;
        ++m_size;

        return new_node;
    }

    //! \fn     IsEmpty
    bool IsEmpty()
    {
        return m_head->next == nullptr;
    }

    //! \fn     PrintList
    std::vector<DataT> PrintList()
    {
        m_contents.clear();
        if (!IsEmpty()) {
            for (auto it = m_head->next; it != nullptr; it = it->next) {
                m_contents.push_back(it->data);
            }
        }

        return std::vector<DataT>(m_contents.begin(), m_contents.end());
    }

    //! \fn     ReverseList
    //! \brief  Interview practice problem
    void ReverseList()
    {
        if (!IsEmpty()) {
            ListNode<DataT>* tail = nullptr;
            ListNode<DataT>* previous = nullptr;
            ListNode<DataT>* node = m_head;

            while (node != nullptr) {
                ListNode<DataT>* next = node->next;

                if (next == nullptr) {
                    tail = node;
                }

                node->next = (previous == m_head) ? nullptr : previous;
                previous = node;
                node = next;
            }

            m_head->next = tail;
        }
    }

    //! \fn     Size
    std::size_t Size() const
    {
        return m_size;
    }

private:
    ListNode<DataT>*    m_head;
    std::size_t         m_size;
    std::vector<DataT>  m_contents;
};


#endif //SLINKY_SLINKY_HPP
