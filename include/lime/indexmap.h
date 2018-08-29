#pragma once

#include <map>

/**
   Maps a pointer to an index.
   Pointer type and index type are both templated
 */

namespace lime
{
    template <class T, typename IDX_T>
    class IndexMap
    {
    public:
        /** Create the map.
            Also specify a value to use when an index is not found
        */
        IndexMap(IDX_T notFoundIndex = 9999999999) :
            map_(),
            notFoundIndex_(notFoundIndex)
        {}
        
        void addIndex (const T* ptr, IDX_T idx) {
            map_[ptr] = idx;
        }
        /** Return the index associated with the pointer.
            If we have not seen the pointer, return the 'notFoud' index
        */
        IDX_T indexOf (const T* ptr) const {
            auto it = map_.find (ptr);
            if (it == map_.end())
                return notFoundIndex_;
            return it->second;
        }
        
        bool hasIndex (const T* ptr) const {
            auto it = map_.find (ptr);
            return (it != map_.end());
        }

        IDX_T operator[] (const T* ptr) const {
            return indexOf (ptr);
        }
        
    private:
        std::map<const T*,unsigned long> map_;
        IDX_T notFoundIndex_;
    };
}
