#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
 *  Records the domain of an integer variable using vector of bools
 */

#include <iostream>
#include <set>
#include <vector>
#include <cstring>
#include <memory>

#include "lime/displayable.h"

namespace lime
{
    class BoolArray
    {
    public:
        BoolArray (size_t size, bool defaultVal = true) :
            arr_ (0),
            size_(size)
        {
            if (size > 0) {
                arr_ = new bool [size];
                std::fill (arr_, arr_ + size, defaultVal);
            }
        }
        BoolArray (const BoolArray& other) :
            arr_ (0),
            size_(0)
        {
            copy (other);
        }
        virtual ~BoolArray () {
            if (arr_ != 0)
                delete [] arr_;
        }
        size_t size() const {return size_;}
        void resize (size_t size, bool defaultVal = true) {
            if (size > size_) {
                if (size_ > 0)
                    delete [] arr_;
                arr_ = new bool [size];
                std::fill (arr_, arr_ + size, defaultVal);
            }
            size_ = size;
        }
        void copy (const BoolArray& other) {
            if (other.size_ > size_) {
                if (size_ > 0)
                    delete [] arr_;
                arr_ = new bool [other.size_];
            }
            size_ = other.size_;
            std::memcpy  (arr_, other.arr_, sizeof(bool) * size_);
        }
        BoolArray& operator=(const BoolArray& other) {
            if (this != &other) 
                copy (other);
            return *this;
        }
        const bool& operator[](int idx) const {
            return arr_[idx];
        }
        bool& operator[](int idx) {
            return arr_[idx];
        }
        void set (size_t begin, size_t end, bool value) {
            std::fill (arr_ + begin, arr_ + end, value);
        }

    private:
        bool* arr_;
        size_t size_;
    };
        
    class IntSet;
    class IntSetIter
    {
    public:
        IntSetIter(const IntSet* intSet);

        bool hasNext() const;
        long next();
        
    private:
        void advance();
        
        const IntSet* intSet_;
        long nextVal_;
    };

    class IntSet : public lime::Displayable
    {
    public:
        /** Empty constructor for intset */
        IntSet();
        /** Create a intset with bounds*/
        IntSet(long min, long max);
        /** Copy constructor */
        IntSet(const IntSet& other);

        /** Initialise the set to the given domain */
        void initialise (long lb, long ub);
        /** How many elements in the domain? */
        size_t size() const {return count_;}
        /** Is the domain empty */
        bool isEmpty() const {return count_ == 0;}
        /** Is the variable bound to a single value */
        bool isBound() const {return count_ == 1;}
        /** Get the value of the variable.
         * Action undefined if the variable is not bound
         */
        long value() const {return min();}
    
        bool contains(long val) const {return values_[val - minValue_];}
    
        /** The bottom of the legal range */
        long min() const;
        /** The top of the legal range */
        long max() const;
    
        /** Remove a value from the domain */
        void remove (long val);
    
        /** Remove a range of values from the domain.
         *  Removed values includes from and to
         */
        void remove (long from, long to);

        /** Set the values in the domain */
        void setValues (std::set<long> values);
        /** Bind to a single value */
        void setValue (long value);
        /** Copy the other var. */
        void copy (const IntSet* other);

        IntSet& operator=(const IntSet& other) {
            minValue_ = other.minValue_;
            maxValue_ = other.maxValue_;
            size_ = other.size_;
            count_ = other.count_;
            values_.copy (other.values_);
            return *this;
        }

        /* Note, does not copy saved values */
        IntSet& operator=(IntSet& other);

        IntSetIter iterator() {return IntSetIter (this);}

        long minValue() const {return minValue_;}
        long maxValue() const {return maxValue_;}

        void display (std::ostream&) const override;
    
    private:
        /** The smallest value allowed */
        long minValue_;
        /** The largetst value allowed */
        long maxValue_;
        
        /** Number of elements, for convenience */
        long size_;

        /** The number of values set */
        size_t count_;

        /** Bool array - is value included?
            vector<bool> is way too slow
         */
        BoolArray values_;

        /** Saved values for store/restore */
        std::vector<std::shared_ptr<BoolArray>> saveValues_;
        std::vector<size_t> saveCount_;
    };

}
