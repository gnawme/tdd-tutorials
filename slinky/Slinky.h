/*! -------------------------------------------------------------------------*\
|   Singly-linked list after https://en.wikipedia.org/wiki/Linked_list
\*---------------------------------------------------------------------------*/
#pragma once

#include <stdexcept>
#include <vector>

/// \struct ListNode
template<typename DataT>
struct ListNode {
    ListNode() : next(nullptr) {}

    ListNode(DataT data) : data(std::move(data)), next(nullptr) {}

    DataT data;
    ListNode<DataT>* next;
};

/// \class Slinky
template<typename DataT>
class Slinky {
public:
    ///
    Slinky()
            : _head(new ListNode<DataT>)

    {}

    ///
    Slinky(const Slinky& other) : _head(new ListNode<DataT>), _listSize(0) {
        copy(other);
    }

    ///
    Slinky& operator=(const Slinky& other) {
        if (&other != this) {
            clear();
            copy(other);
        }

        return *this;
    }

    /// Move constructor
    /// \see
    /// http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Slinky(Slinky&& other) : _head(new ListNode<DataT>), _listSize(other._listSize) {
        // Pilfer other's resources
        _head->next = other.Head();
        _listSize = other._listSize;

        // Reset other to default state
        other._head->next = nullptr;
        other._listSize = 0;
    }

    /// Move assignment operator
    /// \see
    /// http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/
    Slinky& operator=(Slinky&& other) {
        if (&other != this) {
            // Release the current object's resources
            clear();

            // Pilfer other's resources
            _head->next = other.Head();
            _listSize = other._listSize;

            // Reset other to default state
            other._head->next = nullptr;
            other._listSize = 0;
        }

        return *this;
    }

    ///
    virtual ~Slinky() {
        clear();
        delete _head;
    }

    ///
    /// brief   Appends a value to the list's end
    void append(const DataT& data) {
        if (_head->next == nullptr) {
            append(_head, data);
            return;
        } else {
            auto node{_head->next};
            for (node; node != nullptr; node = node->next) {
                if (node->next == nullptr) {
                    append(node, data);
                    return;
                }
            }
        }
    }

    ///
    /// \brief  Traverses the list and deletes all nodes
    void clear() {
        if (!isEmpty()) {
            ListNode<DataT>* it{_head->next};
            while (it != nullptr) {
                ListNode<DataT>* temp{it->next};
                delete it;
                it = temp;
            }
        }

        _head->next = nullptr;
        _listSize = 0;
    }

    ///
    /// /brief  Deletes the node after the list head
    ListNode<DataT>* deleteNode() {
        if (!isEmpty()) {
            ListNode<DataT>* temp{_head->next->next};
            delete _head->next;
            _head->next = temp;

            --_listSize;
        }
    }

    ///
    /// \brief  Deletes the given node
    ListNode<DataT>* deleteNode(ListNode<DataT>* target) {
        if (!isEmpty()) {
            for (auto node = _head->next, prev = _head; node != nullptr;
                 prev = prev->next, node = node->next) {
                if (node == target) {
                    ListNode<DataT>* temp = node->next;
                    prev->next = temp;
                    delete node;
                    --_listSize;
                }
            }
        }
    }

    ///
    /// \brief  Returns the first object in the list
    [[nodiscard]] DataT first() const {
        if (!isEmpty()) {
            return _head->next->data;
        } else {
            throw std::out_of_range("Slinky::first: list is empty");
        }
    }

    ///
    /// \brief  Returns the object at the given index
    [[nodiscard]] DataT get(std::size_t index) const {
        if (index > _listSize) {
            throw std::out_of_range("Slinky::get(): index is out of range");
        }

        std::size_t where = 0;
        for (ListNode<DataT>* node = _head->next; node != nullptr; node = node->next) {
            if (where == index) {
                return node->data;
            }

            ++where;
        }
    }

    ///
    /// \brief  Gets the first node of the list
    ListNode<DataT>* Head() {
        return _head->next;
    }

    ///
    /// \brief  Inserts new node after list head
    ListNode<DataT>* insert(ListNode<DataT>* newNode) {
        newNode->next = _head->next;
        _head->next = newNode;
        ++_listSize;

        return newNode;
    }

    ///
    /// \brief  Inserts new node after given node
    ListNode<DataT>* insert(ListNode<DataT>* node, ListNode<DataT>* newNode) {
        newNode->next = node->next;
        node->next = newNode;
        ++_listSize;

        return newNode;
    }

    ///
    [[nodiscard]] bool isEmpty() const {
        return _head->next == nullptr;
    }

    ///
    /// \brief  Returns the last object in the list
    [[nodiscard]] DataT Last() const {
        if (!isEmpty()) {
            auto node = _head->next;
            for (node; node != nullptr; node = node->next) {
                if (node->next == nullptr) {
                    return node->data;
                }
            }
        } else {
            throw std::out_of_range("Slinky::Last: list is empty");
        }
    }

    ///
    void prepend(const DataT& data) {
        if (_head->next == nullptr) {
            _head->next = new ListNode<DataT>(data);
            ++_listSize;
        } else {
            ListNode<DataT>* temp = _head->next;
            _head->next = new ListNode<DataT>(data);
            _head->next->next = temp;
            ++_listSize;
        }
    }

    ///
    std::vector<DataT> _printList() {
        _contents.clear();
        if (!isEmpty()) {
            for (auto it = _head->next; it != nullptr; it = it->next) {
                _contents.push_back(it->data);
            }
        }

        return std::vector<DataT>(_contents.begin(), _contents.end());
    }

    ///
    /// \brief  Removes the given object from the list
    void Remove(const DataT& data) {
        if (!isEmpty()) {
            for (auto node = _head->next; node != nullptr; node = node->next) {
                if (node->data == data) {
                    deleteNode(node);
                }
            }
        }
    }

    ///
    /// \brief  Removes all objects from the list
    void RemoveAll() {
        clear();
    }

    ///
    /// \brief  Removes the first object from the list
    void removeFirst() {
        deleteNode();
    }

    ///
    /// \brief  Removes the last object from the list
    void removeLast() {
        if (!isEmpty()) {
            for (auto node = _head->next; node != nullptr; node = node->next) {
                if (node->next == nullptr) {
                    deleteNode(node);
                }
            }
        }
    }

    ///
    /// \brief  Recursive list reversal
    void reverse() {
        if (!isEmpty()) {
            auto newHead{_doReverse(_head->next, _head)};
            // Terminate new tail, point to new head
            _head->next->next = nullptr;
            _head->next = newHead;
        }
    }

    ///
    /// \brief  Interview practice problem
    void reverseList() {
        if (!isEmpty()) {
            ListNode<DataT>* tail{nullptr};
            ListNode<DataT>* previous{nullptr};

            auto node{_head};

            while (node != nullptr) {
                auto next{node->next};

                // We've reached the end of the list; store the tail
                if (next == nullptr) {
                    tail = node;
                }

                // If it's not the first node,
                // reverse its next pointer to its predecessor
                node->next = (previous == _head) ? nullptr : previous;

                // Move along
                previous = node;
                node = next;
            }

            _head->next = tail;
        }
    }

    ///
    ListNode<DataT>* search(const DataT& data) {
        return _doSearch(_head->next, data);
    }

    ///
    [[nodiscard]] std::size_t size() const {
        return _listSize;
    }

private:
    ///
    /// \brief  Effects the append operation
    void append(ListNode<DataT>* current, const DataT& data) {
        auto newnode{new ListNode<DataT>(data)};
        current->next = newnode;
        ++_listSize;
        return;
    }

    ///
    void copy(const Slinky& other) {
        for (auto i = 0; i < other.size(); ++i) {
            append(other.get(i));
        }
    }

    ///
    void copy(Slinky& other) {
        for (auto i = 0; i < other.size(); ++i) {
            append(other.get(i));
        }
    }

    ///
    ListNode<DataT>* _doReverse(ListNode<DataT>* current, ListNode<DataT>* previous) {
        auto temp{current};
        if (temp->next == nullptr) {
            // At end of list, start reversing links
            temp->next = previous;
            return temp;
        } else {
            temp = _doReverse(current->next, current);
            current->next = previous;
            return temp;
        }
    }

    ///
    ListNode<DataT>* _doSearch(ListNode<DataT>* node, const DataT& data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data == data) {
            return node;
        } else {
            return _doSearch(node->next, data);
        }
    }

    ListNode<DataT>* _head;
    std::size_t _listSize{0};
    std::vector<DataT> _contents;
};
