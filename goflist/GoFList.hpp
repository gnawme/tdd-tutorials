/*! -------------------------------------------------------------------------*\
|   List from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#pragma once
#include "Slinky.h"

#include <memory>

constexpr std::size_t DEFAULT_LIST_CAPACITY{128};

/// \class  GoFList
/// \brief  Implementation of GoF List
template<typename DataT>
class GoFList : public Slinky<DataT> {
public:
    ///
    GoFList(std::size_t size = DEFAULT_LIST_CAPACITY) : Slinky<DataT>(), _listSize(size) {}

    ///
    [[nodiscard]] std::size_t count() const {
        return Slinky<DataT>::size();
    }

    ///
    /// brief   GoF Stack Interface; returns top of stack
    [[nodiscard]] DataT Top() const {
        return Slinky<DataT>::first();
    }

    ///
    /// \brief  GoF Stack Interface; pops from stack
    DataT pop() {
        DataT top = Slinky<DataT>::first();
        Slinky<DataT>::removeFirst();
        return top;
    }

    ///
    /// \brief  GoF Stack Interface; pushes onto stack
    void push(const DataT& data) {
        Slinky<DataT>::prepend(data);
    }

private:
    std::size_t _listSize;
};
