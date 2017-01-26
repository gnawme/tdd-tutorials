/*!--------------------------------------------------------------------------*\
|   Binary Search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#ifndef BEASTIE_BEASTIE_HPP
#define BEASTIE_BEASTIE_HPP

#include <iostream>
#include <map>
#include <vector>

//! \class  BSTNode
template<typename DataT>
struct BSTNode
{
    BSTNode(DataT value)
    : key(value)
    , left(nullptr)
    , right(nullptr)
    {}

    ~BSTNode()
    {
        left = nullptr;
        right = nullptr;
    }

    DataT           key;
    BSTNode<DataT>* left;
    BSTNode<DataT>* right;
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
    , m_num_paths(0)
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

    //! \fn     FindPaths
    void FindPaths()
    {
        std::vector<DataT> path_values;
        std::map<BSTNode<DataT>*, BSTNode<DataT>*> leaf_map;
        FindPaths(m_root_node, path_values, leaf_map);
    }

    //! \fn     GetRoot
    BSTNode<DataT>* GetRoot() const
    {
        return m_root_node;
    }

    //! \fn     GetTree
    std::vector<DataT> GetTree() const
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

    //! \fn     NumPaths
    std::size_t NumPaths() const
    {
        return m_num_paths;
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

        TraverseInorder(root->left);
        Visit(root);
        TraverseInorder(root->right);
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

        TraversePostorder(root->left);
        TraversePostorder(root->right);
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
        TraversePreorder(root->left);
        TraversePreorder(root->right);
    }

private:
    //! \fn     Depth
    int Depth(BSTNode<DataT>* root, int depth)
    {
        int left_depth = depth;
        int right_depth = depth;

        if (root->left != nullptr) {
            left_depth = Depth(root->left, depth + 1);
        }

        if (root->right != nullptr) {
            right_depth = Depth(root->right, depth + 1);
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

        DoClear(root->left);
        DoClear(root->right);
        delete root;
    }

    //! \fn     FindPaths
    void FindPaths(BSTNode<DataT>* root, std::vector<DataT>& path_values, std::map<BSTNode<DataT>*, BSTNode<DataT>*>& leaf_map)
    {
        if (root == nullptr) {
            return;
        }

        path_values.push_back(root->key);

        bool is_leaf = (root->left == nullptr && root->right == nullptr);
        if (is_leaf) {
            if (leaf_map.find(root) == leaf_map.end()) {
                leaf_map.insert(std::pair<BSTNode<DataT>*, BSTNode<DataT>*>(root, root));
                ++m_num_paths;
                std::cout << "Path found: ";
                for (auto path : path_values) {
                    std::cout << path << " ";
                }
                std::cout << std::endl;
            }
        }

        if (root->left != nullptr) {
            FindPaths(root->left, path_values, leaf_map);
        }

        if (root->right != nullptr) {
            FindPaths(root->right, path_values, leaf_map);
        }

        path_values.pop_back();
    }

    //! \fn     Insert
    BSTNode<DataT>* Insert(BSTNode<DataT>* root, DataT value)
    {
        if (value < root->key) {
            if (root->left == nullptr) {
                root->left = new BSTNode<DataT>(value);
                return root->left;
            } else {
                Insert(root->left, value);
            }
        } else {
            if (root->right == nullptr) {
                root->right = new BSTNode<DataT>(value);
                return root->right;
            } else {
                Insert(root->right, value);
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
            return Search(root->left, key);
        } else {
            return Search(root->right, key);
        }
    }

    //! \fn     Visit
    void Visit(BSTNode<DataT>* root)
    {
        m_tree.push_back(root->key);
    }

    BSTNode<DataT>* m_root_node;
    std::vector<DataT> m_tree;
    std::size_t m_num_paths;
};

#endif //BEASTIE_BEASTIE_HPP
