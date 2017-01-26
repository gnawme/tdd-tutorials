/*! -------------------------------------------------------------------------*\
|   Iterator from Design Patterns (Gang of Four) Foundation Classes
\*---------------------------------------------------------------------------*/
#ifndef GOFLIST_GOFITERATOR_HPP
#define GOFLIST_GOFITERATOR_HPP

//! \class  GoFIterator
//! \brief  Abstract Iterator class
template<typename DataT>
class GoFIterator
{
public:
    virtual ~GoFIterator();

    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual DataT CurrentItem() const = 0;
};

#endif //GOFLIST_GOFITERATOR_HPP
