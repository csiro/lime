#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/** Sort an array with value and a numeric key by the key */

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

namespace lime
{
    template <typename V, typename K>
    class Sorter
    {
    public:
        Sorter() : valKey_(), sorted_(false) {}
        
        void add (V val, K key) {
            assert(!sorted_);
            valKey_.push_back (ValKey (val, key));
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
        
        V operator[](size_t i) const {return get(i);}
        V get (size_t i) const {
            return valKey_[i].val;
        }
        V getVal (size_t i) const {
            return valKey_[i].val;
        }
        K getKey (size_t i) const {
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
            V val;
            K key;
            
            ValKey (V val_, K key_) : val(val_), key(key_) {}

            
            bool operator< (const ValKey& other) const {
                return key < other.key;
            }
        };
        
        std::vector<ValKey> valKey_;
        bool sorted_;
    };
} 
