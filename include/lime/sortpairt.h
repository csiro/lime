#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
   Templated version of 'SortPair'
   Sort an array with <template type> val and double sort-key by the double */

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

namespace lime
{
    template<typename ValType>
    class SortPairT
    {
    public:
        SortPairT() : valKey_(), sorted_(false) {}
        
        void add (ValType val, double key) {
            valKey_.push_back (ValKey (val, key));
            sorted_ = false;
        }
        
        void doSort() {
            std::sort (valKey_.begin(), valKey_.end());
            sorted_ = true;
        }
        void clear() {
            valKey_.clear();
            sorted_ = false;
        }

        size_t size() const {return valKey_.size();}
        
        ValType operator[](size_t i) {
            return get(i);
        }
        ValType get (size_t i) {
            return getVal(i);
        }
        ValType getVal (size_t i) {
            if (!sorted_)
                doSort();
            return valKey_[i].val;
        }
        double getKey (size_t i) {
            if (!sorted_)
                doSort();
            return valKey_[i].key;
        }

        void show (std::ostream& out, const char* indent = "") {
            for (auto vk : valKey_) {
                out << indent << "[" << vk.val << "," << vk.key <<"]" <<
                    std::endl;
            }
        }

    private:
        struct ValKey
        {
            ValType val;
            double key;
            
            ValKey (ValType val_, double key_) : val(val_), key(key_) {}

            
            bool operator< (const ValKey& other) const {
                return key < other.key;
            }
        };
        
        std::vector<ValKey> valKey_;
        bool sorted_;
    };
} 
