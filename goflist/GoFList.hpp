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
class GoFList
{
public:
    //! \fn
    GoFList(size_t size = DEFAULT_LIST_CAPACITY)
    : m_slist(new Slinky<DataT>())
    , m_list_size(size)
    {}

    //! \fn     Append
    void Append(const DataT& data)
    {
        m_slist->Append(data);
    }

    //! \fn     Count
    size_t Count() const
    {
        return m_slist->Size();
    }

private:
    std::unique_ptr<Slinky<DataT>>  m_slist;
    size_t                          m_list_size;
};


#endif //GOFLIST_GOFLIST_HPP
