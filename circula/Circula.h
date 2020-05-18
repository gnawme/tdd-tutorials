/*! -------------------------------------------------------------------------*\
|   Circular buffer after https://embedjournal.com/implementing-circular-buffer-embedded-c/
\*---------------------------------------------------------------------------*/
#pragma once

#include <array>
#include <stdexcept>
#include <vector>

/// \class  Circula
/// \brief  Circular buffer, size specified at compile time
/// \note   Buffer of size N contains N+1 slots
template<typename DataT, std::size_t N>
class Circula {
public:
    ///
    Circula() : _capacity(N + 1) {}

    ///
    virtual ~Circula() = default;

    ///
    [[nodiscard]] bool isEmpty() const {
        return (_head == _tail);
    }

    [[nodiscard]] std::size_t capacity() const {
        return N;
    }

    ///
    /// \brief  Values are popped from the buffer at the tail
    DataT pop() {
        if (isEmpty()) {
            throw std::underflow_error("Buffer empty");
        }

        int next{_tail + 1};

        // Wrap the tail
        if (next >= _capacity) {
            next = 0;
        }

        // pop from the tail, and advance the tail
        DataT data{_buffer[_tail]};
        _tail = next;

        return data;
    }

    ///
    /// \brief  Values are pushed onto the buffer at the head
    void push(DataT data) {
        int next{_head + 1};

        // Wrap the head
        if (next >= _capacity) {
            next = 0;
        }

        // Definition: If head + 1 == tail, the buffer is full
        if (next == _tail) {
            throw std::overflow_error("Buffer full");
        }

        // push at the head, and advance the head
        _buffer[_head] = data;
        _head = next;
    }

private:
    int _head{0};
    int _tail{0};
    DataT _buffer[N + 1];
    std::size_t _capacity;
};
