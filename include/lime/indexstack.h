#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <list>

/**
   Maps a pointer to an index.
   Pointer type and index type are both templated
 */

namespace lime
{
    template <typename IDX_T>
    class IndexStack
    {
    public:
        /** Create the map.
            Also specify a value to use when an index is not found
        */
        IndexStack() :
            index_(0),
            list_()
        {}
        
        IDX_T index() const {return index_;}
        IDX_T operator()() const {return index_;}
        /** Lie about const, as this is often called in a 'const' context */
        void addIndex (IDX_T idx) const {
            auto nonconst = (IndexStack<IDX_T>*) this;
            nonconst->list_.push_front(index_);
            nonconst->index_ = idx;
        }
        /** Lie about const, as this is often called in a 'const' context */
        void popIndex () const {
            auto nonconst = (IndexStack<IDX_T>*) this;
            nonconst->index_ = list_.front();
            nonconst->list_.pop_front();
        }
        IDX_T operator==(const IndexStack<IDX_T>& other) const {
            return index_ == other.index_;
        }
        
    private:
        IDX_T index_;
        std::list<IDX_T> list_;
    };
}
