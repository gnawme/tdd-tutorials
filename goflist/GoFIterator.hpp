/*! -------------------------------------------------------------------------*\
|   Iterator from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#pragma once

/// \class  GoFIterator
/// \brief  Abstract Iterator class
template<typename DataT>
class GoFIterator {
public:
    virtual ~GoFIterator();

    virtual void first() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual DataT CurrentItem() const = 0;
};
