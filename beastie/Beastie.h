/*!--------------------------------------------------------------------------*\
|   Binary search Tree TDD exercise
\*---------------------------------------------------------------------------*/
#pragma once
#include <iostream>
#include <map>
#include <vector>

/// \class  BSTNode
template<typename DataT>
struct BSTNode {
    explicit BSTNode(DataT key) : key(key), left(nullptr), right(nullptr) {}

    ~BSTNode() {
        left = nullptr;
        right = nullptr;
    }

    DataT key;
    BSTNode<DataT>* left;
    BSTNode<DataT>* right;
};

/// \class  Beastie
/// \brief  Canonical binary search tree implementation
/// \see    https://www.cs.rochester.edu/~gildea/csc282/slides/C12-bst.pdf
template<typename DataT>
class Beastie {
public:
    ///
    Beastie()
            : _rootNode(nullptr)

    {}

    ///
    Beastie(const Beastie& other) : _rootNode(nullptr), _numPaths(0) {
        copy(other);
    }

    ///
    Beastie& operator=(const Beastie& other) {
        if (&other != this) {
            clear();
            copy(other);
        }
    }

    /// Move constructor
    /// \see
    /// http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Beastie(Beastie&& other) : _rootNode(nullptr), _numPaths(0) {
        // Pilfer other's resources
        _rootNode = new BSTNode<DataT>(other._rootNode->key);
        _rootNode->left = other._rootNode->left;
        _rootNode->right = other._rootNode->right;

        // Reset other to default state
        other._rootNode = nullptr;
        other._numPaths = 0;
    }

    /// Move assignment operator
    /// \see
    /// http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Beastie& operator=(Beastie&& other) {
        if (&other != this) {
            // Release the current object's resources
            clear();

            // Pilfer other's resources
            _rootNode = new BSTNode<DataT>(other._rootNode->key);
            _rootNode->left = other._rootNode->left;
            _rootNode->right = other._rootNode->right;

            // Reset other to default state
            other._rootNode = nullptr;
            other._numPaths = 0;
        }

        return *this;
    }

    ///
    void clear() {
        doClear(_rootNode);
        _rootNode = nullptr;
    }

    ///
    void copy(const Beastie& other) {
        other.traversePreorder(other.getRoot());
        std::vector<DataT> contents{other.getTree()};
        for (auto node : contents) {
            insert(node);
        }
    }

    ///
    int depth() {
        int currentDepth = 0;
        return depth(_rootNode, currentDepth);
    }

    ///
    void findPaths() {
        std::vector<DataT> path_values;
        std::map<BSTNode<DataT>*, BSTNode<DataT>*> leaf_map;
        findPaths(_rootNode, path_values, leaf_map);
    }

    ///
    BSTNode<DataT>* getRoot() const {
        return _rootNode;
    }

    ///
    std::vector<DataT> getTree() const {
        return _tree;
    }

    ///
    BSTNode<DataT>* insert(DataT key) {
        if (_rootNode == nullptr) {
            _rootNode = new BSTNode<DataT>(key);
            return _rootNode;
        } else {
            return insert(_rootNode, key);
        }
    }

    ///
    bool isEmpty() {
        return (_rootNode == nullptr);
    }

    ///
    std::size_t numPaths() const {
        return _numPaths;
    }

    ///
    BSTNode<DataT>* search(DataT key) {
        return search(_rootNode, key);
    }

    ///
    /// \brief  Inorder traversal: left-root-right
    /// \note   Use inorder to output nodes in a non-decreasing order
    void traverseInorder(BSTNode<DataT>* root) const {
        if (root == nullptr) {
            return;
        }

        if (root == _rootNode) {
            _tree.clear();
        }

        traverseInorder(root->left);
        visit(root);
        traverseInorder(root->right);
    }

    ///
    /// \brief  Postorder traversal: left-right-root
    /// \note   Use postorder to delete the tree
    void traversePostorder(BSTNode<DataT>* root) const {
        if (root == nullptr) {
            return;
        }

        if (root == _rootNode) {
            _tree.clear();
        }

        traversePostorder(root->left);
        traversePostorder(root->right);
        visit(root);
    }

    ///
    /// \brief  Preorder traversal: root-left-right
    /// \note   Use preorder to make a copy of the tree
    void traversePreorder(BSTNode<DataT>* root) const {
        if (root == nullptr) {
            return;
        }

        if (root == _rootNode) {
            _tree.clear();
        }

        visit(root);
        traversePreorder(root->left);
        traversePreorder(root->right);
    }

private:
    ///
    int depth(BSTNode<DataT>* root, int currentDepth) {
        int leftDepth = currentDepth;
        int rightDepth = currentDepth;

        if (root->left != nullptr) {
            leftDepth = depth(root->left, currentDepth + 1);
        }

        if (root->right != nullptr) {
            rightDepth = depth(root->right, currentDepth + 1);
        }

        return (leftDepth > rightDepth) ? leftDepth : rightDepth;
    }

    ///
    void doClear(BSTNode<DataT>* root) {
        if (root == nullptr) {
            return;
        }

        if (root == _rootNode) {
            _tree.clear();
        }

        doClear(root->left);
        doClear(root->right);
        delete root;
    }

    ///
    void findPaths(
            BSTNode<DataT>* root,
            std::vector<DataT>& path_values,
            std::map<BSTNode<DataT>*, BSTNode<DataT>*>& leaf_map) {
        if (root == nullptr) {
            return;
        }

        path_values.push_back(root->key);

        bool is_leaf = (root->left == nullptr && root->right == nullptr);
        if (is_leaf) {
            if (leaf_map.find(root) == leaf_map.end()) {
                leaf_map.insert(std::pair<BSTNode<DataT>*, BSTNode<DataT>*>(root, root));
                ++_numPaths;
                std::cout << "Path found: ";
                for (auto path : path_values) {
                    std::cout << path << " ";
                }
                std::cout << std::endl;
            }
        }

        if (root->left != nullptr) {
            findPaths(root->left, path_values, leaf_map);
        }

        if (root->right != nullptr) {
            findPaths(root->right, path_values, leaf_map);
        }

        path_values.pop_back();
    }

    ///
    BSTNode<DataT>* insert(BSTNode<DataT>* root, DataT key) {
        if (key < root->key) {
            if (root->left == nullptr) {
                root->left = new BSTNode<DataT>(key);
                return root->left;
            } else {
                insert(root->left, key);
            }
        } else {
            if (root->right == nullptr) {
                root->right = new BSTNode<DataT>(key);
                return root->right;
            } else {
                insert(root->right, key);
            }
        }
    }

    ///
    BSTNode<DataT>* search(BSTNode<DataT>* root, DataT key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key == root->key) {
            return root;
        } else if (key < root->key) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }

    ///
    void visit(BSTNode<DataT>* root) const {
        _tree.push_back(root->key);
    }

    BSTNode<DataT>* _rootNode;
    mutable std::vector<DataT> _tree;
    mutable std::size_t _numPaths{0};
};
