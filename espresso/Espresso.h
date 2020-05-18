/*! -------------------------------------------------------------------------*\
|   Postfix expression tree
\*---------------------------------------------------------------------------*/
#pragma once

#include <set>
#include <stack>
#include <vector>

/// \struct ExprNode
struct ExprNode {
    ExprNode(char data) : data(data), left(nullptr), right(nullptr) {}

    ~ExprNode() {
        delete left;
        delete right;
    }

    char data;
    ExprNode* left;
    ExprNode* right;
};

/// \class  Espresso
class Espresso {
public:
    Espresso() = default;
    ~Espresso() = default;

    ///
    void addSymbol(char c) {
        if (!isOperator(c)) {
            auto operand{new ExprNode(c)};
            _expressionStack.push(operand);
        } else {
            auto operatory{new ExprNode(c)};

            operatory->right = _expressionStack.top();
            _expressionStack.pop();
            operatory->left = _expressionStack.top();
            _expressionStack.pop();

            _expressionStack.push(operatory);
        }
    }

    ///
    bool isEmpty() const {
        return (_expressionStack.empty());
    }

    ///
    std::vector<char> getTree() const {
        return _tree;
    }

    ///
    void traversePostorder() {
        if (!isEmpty()) {
            doTraversePostorder(_expressionStack.top());
        }
    }

    ///
    void traversePreorder() {
        if (!isEmpty()) {
            doTraversePreorder(_expressionStack.top());
        }
    }

private:
    void doTraversePostorder(ExprNode* root) {
        if (root == nullptr) {
            return;
        }

        if (root == _expressionStack.top()) {
            _tree.clear();
        }

        doTraversePostorder(root->left);
        doTraversePostorder(root->right);
        visit(root);
    }

    void doTraversePreorder(ExprNode* root) {
        if (root == nullptr) {
            return;
        }

        if (root == _expressionStack.top()) {
            _tree.clear();
        }

        visit(root);
        doTraversePostorder(root->left);
        doTraversePostorder(root->right);
    }

    void visit(ExprNode* node) {
        _tree.push_back(node->data);
    }

    bool isOperator(char c) {
        auto isop{_operators.find(c)};
        return (isop != _operators.end());
    }

    static std::set<char> _operators;

    std::stack<ExprNode*> _expressionStack;
    mutable std::vector<char> _tree;
};
