/*!--------------------------------------------------------------------------*\
|   Binary Search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#ifndef BEASTIE_BEASTIE_HPP
#define BEASTIE_BEASTIE_HPP

#include <iostream>
#include <vector>

//! \class  BSTNode
template<typename DataT>
struct BSTNode
{
    BSTNode(DataT value)
    : key(value)
    , left_child(nullptr)
    , right_child(nullptr)
    {}

    ~BSTNode()
    {
        left_child = nullptr;
        right_child = nullptr;
    }

    DataT           key;
    BSTNode<DataT>* left_child;
    BSTNode<DataT>* right_child;
};

//! \class  Beastie
//! \brief  Canonical binary search tree implementation
//! \see    https://www.cs.rochester.edu/~gildea/csc282/slides/C12-bst.pdf
template<typename DataT>
class Beastie {
public:

    //! \fn
    Beastie()
    : m_root_node(nullptr)
    {}

    //! \fn
    void Clear()
    {
        DoClear(m_root_node);
        m_root_node = nullptr;
    }

    //! \fn     Depth
    int Depth()
    {
        int depth = 0;
        return Depth(m_root_node, depth);
    }

    BSTNode<DataT>* GetRoot()
    {
        return m_root_node;
    }

    std::vector<DataT> GetTree()
    {
        return m_tree;
    }

    //! \fn     Insert
    BSTNode<DataT>* Insert(DataT value)
    {
        if (m_root_node == nullptr) {
            m_root_node = new BSTNode<DataT>(value);
            return m_root_node;
        } else {
            return Insert(m_root_node, value);
        }
    }

    //! \fn     IsEmpty
    bool IsEmpty()
    {
        return (m_root_node == nullptr);
    }

    //! \fn     Search
    BSTNode<DataT>* Search(DataT key)
    {
        return Search(m_root_node, key);
    }

    //! \fn     TraverseInorder
    //! \brief  Inorder traversal: left-root-right
    //! \note   Use inorder to output nodes in a non-decreasing order
    void TraverseInorder(BSTNode<DataT>* root)
    {
        if (root == nullptr) {
            return;
        }

        if (root == m_root_node) {
            m_tree.clear();
        }

        TraverseInorder(root->left_child);
        Visit(root);
        TraverseInorder(root->right_child);
    }

    //! \fn     TraversePostorder
    //! \brief  Postorder traversal: left-right-root
    //! \note   Use postorder to delete the tree
    void TraversePostorder(BSTNode<DataT>* root)
    {
        if (root == nullptr) {
            return;
        }

        if (root == m_root_node) {
            m_tree.clear();
        }

        TraversePostorder(root->left_child);
        TraversePostorder(root->right_child);
        Visit(root);
    }

    //! \fn     TraversePreorder
    //! \brief  Preorder traversal: root-left-right
    //! \note   Use preorder to make a copy of the tree
    void TraversePreorder(BSTNode<DataT>* root)
    {
        if (root == nullptr) {
            return;
        }

        if (root == m_root_node) {
            m_tree.clear();
        }

        Visit(root);
        TraversePreorder(root->left_child);
        TraversePreorder(root->right_child);
    }

private:
    //! \fn     Depth
    int Depth(BSTNode<DataT>* root, int depth)
    {
        int left_depth = depth;
        int right_depth = depth;

        if (root->left_child != nullptr) {
            left_depth = Depth(root->left_child, depth + 1);
        }

        if (root->right_child != nullptr) {
            right_depth = Depth(root->right_child, depth + 1);
        }

        return (left_depth > right_depth) ? left_depth : right_depth;
    }

    //! \fn     DoClear
    void DoClear(BSTNode<DataT>* root)
    {
        if (root == nullptr) {
            return;
        }

        if (root == m_root_node) {
            m_tree.clear();
        }

        DoClear(root->left_child);
        DoClear(root->right_child);
        delete root;
    }

    //! \fn     Insert
    BSTNode<DataT>* Insert(BSTNode<DataT>* root, DataT value)
    {
        if (value < root->key) {
            if (root->left_child == nullptr) {
                root->left_child = new BSTNode<DataT>(value);
                return root->left_child;
            } else {
                Insert(root->left_child, value);
            }
        } else {
            if (root->right_child == nullptr) {
                root->right_child = new BSTNode<DataT>(value);
                return root->right_child;
            } else {
                Insert(root->right_child, value);
            }
        }
    }

    //! \fn     Search
    BSTNode<DataT>* Search(BSTNode<DataT>* root, DataT key)
    {
        if (root == nullptr) {
            return nullptr;
        }

        if (key == root->key) {
            return root;
        } else if (key < root->key) {
            return Search(root->left_child, key);
        } else {
            return Search(root->right_child, key);
        }
    }

    //! \fn     Visit
    void Visit(BSTNode<DataT>* root)
    {
        m_tree.push_back(root->key);
    }

    BSTNode<DataT>* m_root_node;
    std::vector<DataT> m_tree;
};

#endif //BEASTIE_BEASTIE_HPP
