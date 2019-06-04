/*! -------------------------------------------------------------------------*\
|   Postfix expression tree
\*---------------------------------------------------------------------------*/
#ifndef ESPRESSO_ESPRESSO_HPP
#define ESPRESSO_ESPRESSO_HPP

#include <set>
#include <stack>
#include <vector>

namespace
{
}

//! /struct ExprNode
struct ExprNode
{
    ExprNode(char data)
        : data(data)
        , left(nullptr)
        , right(nullptr)
    {
    }

    ~ExprNode()
    {
        delete left;
        delete right;
    }

    char data;
    ExprNode* left;
    ExprNode* right;
};

//! \class  Espresso
class Espresso
{
public:
    Espresso()  = default;
    ~Espresso() = default;

    //! \fn     AddSymbol
    void AddSymbol(char c)
    {
        if (!IsOperator(c))
        {
            auto operand = new ExprNode(c);
            m_expr_stack.push(operand);
        }
        else
        {
            auto operatory = new ExprNode(c);

            operatory->right = m_expr_stack.top();
            m_expr_stack.pop();
            operatory->left = m_expr_stack.top();
            m_expr_stack.pop();

            m_expr_stack.push(operatory);
        }
    }

    //! \fn     IsEmpty
    bool IsEmpty() const
    {
        return (m_expr_stack.empty());
    }

    //! \fn     GetTree
    std::vector<char> GetTree() const
    {
        return m_tree;
    }

    //! \fn     TraversePostorder
    void TraversePostorder()
    {
        if (!IsEmpty())
        {
            DoTraversePostorder(m_expr_stack.top());
        }
    }

    //! \fn     TraversePreorder
    void TraversePreorder()
    {
        if (!IsEmpty())
        {
            DoTraversePreorder(m_expr_stack.top());
        }
    }

private:
    void DoTraversePostorder(ExprNode* root)
    {
        if (root == nullptr)
        {
            return;
        }

        if (root == m_expr_stack.top())
        {
            m_tree.clear();
        }

        DoTraversePostorder(root->left);
        DoTraversePostorder(root->right);
        Visit(root);
    }

    void DoTraversePreorder(ExprNode* root)
    {
        if (root == nullptr)
        {
            return;
        }

        if (root == m_expr_stack.top())
        {
            m_tree.clear();
        }

        Visit(root);
        DoTraversePostorder(root->left);
        DoTraversePostorder(root->right);
    }

    void Visit(ExprNode* node)
    {
        m_tree.push_back(node->data);
    }

    bool IsOperator(char c)
    {
        auto isop = m_operators.find(c);
        return (isop != m_operators.end());
    }

    static std::set<char> m_operators;

    std::stack<ExprNode*> m_expr_stack;
    mutable std::vector<char> m_tree;
};

#endif // ESPRESSO_ESPRESSO_HPP
