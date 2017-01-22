/*! -------------------------------------------------------------------------*\
|   List from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#ifndef GOFLIST_GOFLIST_HPP
#define GOFLIST_GOFLIST_HPP

#include "Slinky.hpp"

#include <memory>

enum {
    DEFAULT_LIST_CAPACITY = 128
};

//! \class  GoFList
//! \brief  Implementation of GoF List
template<typename DataT>
class GoFList: public Slinky<DataT>
{
public:
    //! \fn
    GoFList(size_t size = DEFAULT_LIST_CAPACITY)
    : Slinky<DataT>()
    , m_list_size(size)
    {}

    //! \fn     Count
    std::size_t Count() const
    {
        return Slinky<DataT>::Size();
    }

    //! \fn     Top
    //! brief   GoF Stack Interface; returns top of stack
    DataT Top() const
    {
        return Slinky<DataT>::First();
    }

    //! \fn     Pop
    //! \brief  GoF Stack Interface; pops from stack
    DataT Pop()
    {
        DataT top = Slinky<DataT>::First();
        Slinky<DataT>::RemoveFirst();
        return top;
    }

    //! \fn     Push
    //! \brief  GoF Stack Interface; pushes onto stack
    void Push(const DataT& data)
    {
        Slinky<DataT>::Prepend(data);
    }

private:
    size_t                          m_list_size;
};


#endif //GOFLIST_GOFLIST_HPP
