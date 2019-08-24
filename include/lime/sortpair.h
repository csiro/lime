#pragma once

/** Sort an array with int and double by the double */

#include <vector>
#include <assert.h>

namespace lime
{
    class SortPair
    {
    public:
        SortPair() : valKey_(), sorted_(false) {}
        
        void add (int val, double key) {
            assert(!sorted);
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
        
        int operator[](int i) const {return get(i);}
        int get (int i) const {
            return valKey_[i].val;
        }
        double getKey (int i) const {
            return valKey_[i].key;
        }

    private:
        struct ValKey
        {
            int val;
            double key;
            
            ValKey (int val_, int key_) : val(val_), key(key_) {}

            
            bool operator< (const ValKey& other) const {
                return key < other.key;
            }
        };
        
        std::vector<ValKey> valKey_;
        bool sorted_;
    };
} 
