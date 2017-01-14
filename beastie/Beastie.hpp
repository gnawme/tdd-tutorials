/*!--------------------------------------------------------------------------*\
|   Binary Search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#ifndef BEASTIE_BEASTIE_HPP
#define BEASTIE_BEASTIE_HPP

#include <iostream>

//! \class  BSTNode
template<typename DataT>
struct BSTNode
{
    BSTNode(DataT value)
    : data(value)
    , left_child(nullptr)
    , right_child(nullptr)
    {}

    DataT           data;
    BSTNode<DataT>* left_child;
    BSTNode<DataT>* right_child;
};

//! \class  Beastie
//! \brief  Canonical binary search tree implementation
template<typename DataT>
class Beastie {
public:

    //! \fn
    Beastie()
    : m_root_node(nullptr)
    {}

    //! \fn     Insert
    BSTNode<DataT>* Insert(DataT value) {
        if (m_root_node == nullptr) {
            m_root_node = GetNewNode(value);
            return m_root_node;
        } else {
            BSTNode<DataT>* current = m_root_node;
            BSTNode<DataT>* parent = nullptr;

            do {
                if (value == current->data) {
                    break;
                } else if (value < current->data) {
                    parent = current;
                    current = current->left_child;
                } else if (value > current->data){
                    parent = current;
                    current = current->right_child;
                }

                if (current == nullptr) {
                    current = GetNewNode(value);
                    return current;
                }
            } while(true);
        }
    }

    //! \fn     IsEmpty
    bool IsEmpty()
    {
        return (m_root_node == nullptr);
    }

private:
    //! \fn     GetNewNode
    BSTNode<DataT>* GetNewNode(DataT value)
    {
        return new BSTNode<DataT>(value);
    }

    BSTNode<DataT>* m_root_node;
};

#endif //BEASTIE_BEASTIE_HPP
