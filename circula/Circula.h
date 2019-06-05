/*! -------------------------------------------------------------------------*\
|   Circular buffer after https://embedjournal.com/implementing-circular-buffer-embedded-c/
\*---------------------------------------------------------------------------*/
#ifndef CIRCULA_CIRCULA
#define CIRCULA_CIRCULA

#include <array>
#include <stdexcept>
#include <vector>

//! \class  Circula
//! \brief  Circular buffer, size specified at compile time
//! \note   Buffer of size N contains N+1 slots
template <typename DataT, std::size_t N>
class Circula
{
public:
    //!
    Circula()
        : m_head(0)
        , m_tail(0)
        , m_capacity(N+1)
    {
    }

    //!
    virtual ~Circula() = default;

    //! \fn     IsEmpty
    bool IsEmpty() const
    {
        return (m_head == m_tail);
    }

    std::size_t Capacity() const
    {
        return N;
    }

    //! \fn     Pop
    //! \brief  Values are popped from the buffer at the tail
    DataT Pop()
    {
        if (IsEmpty())
        {
            throw std::underflow_error("Buffer empty");
        }

        int next = m_tail + 1;

        // Wrap the tail
        if (next >= m_capacity)
        {
            next = 0;
        }

        // Pop from the tail, and advance the tail
        DataT data = m_buffer[m_tail];
        m_tail = next;

        return data;
    }

    //! \fn     Push
    //! \brief  Values are pushed onto the buffer at the head
    void Push(DataT data)
    {
        int next = m_head + 1;

        // Wrap the head
        if (next >= m_capacity)
        {
            next = 0;
        }

        // Definition: If head + 1 == tail, the buffer is full
        if (next == m_tail)
        {
            throw std::overflow_error("Buffer full");
        }

        // Push at the head, and advance the head
        m_buffer[m_head] = data;
        m_head = next;
    }

private:
    int m_head;
    int m_tail;
    DataT m_buffer[N+1];
    std::size_t m_capacity;

};

#endif // CIRCULA_CIRCULA
