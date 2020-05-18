/*! -------------------------------------------------------------------------*\
|   ListIterator from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#pragma once

#include "GoFIterator.hpp"
#include <memory>

template<typename DataT>
GoFList;

/// \class  GoFListIterator
template<typename DataT>
class GoFListIterator : public GoFIterator<DataT> {
public:
    GoFListIterator(const std::unique_ptr<GoFList> list) : _gofList(std::move(list)) {}

private:
    std::unique_ptr<GoFList> _gofList;
};
