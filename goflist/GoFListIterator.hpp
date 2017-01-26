/*! -------------------------------------------------------------------------*\
|   ListIterator from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#ifndef GOFLIST_GOFLISTITERATOR_HPP
#define GOFLIST_GOFLISTITERATOR_HPP

#include "GoFIterator.hpp"
#include <memory>

template<typename DataT> GoFList;

//! \class  GoFListIterator
template<typename DataT>
class GoFListIterator: public GoFIterator<DataT>
{
public:
    GoFListIterator(const std::unique_ptr<GoFList> list)
    : m_goflist(std::move(list))
    {}

private:
    std::unique_ptr<GoFList>    m_goflist;
};

#endif //GOFLIST_GOFLISTITERATOR_HPP
