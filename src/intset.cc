
#include <assert.h>
#include <algorithm>

#include "lime/intset.h"

#include "lime/debug.h"

using namespace std;
using namespace lime;

IntSet::IntSet () :
    minValue_(0),
    maxValue_(0),
    size_(0),
    count_(0),
    values_(0)
{
}

IntSet::IntSet (long min, long max) :
    minValue_(min),
    maxValue_(max),
    size_(max - min + 1),
    count_(max - min + 1),
    values_(size_, true)
{
}

IntSet::IntSet (const IntSet& other) :
    minValue_(other.minValue_),
    maxValue_(other.maxValue_),
    size_(other.size_),
    count_(other.count_),
    values_(other.values_)
{
}

/** Initialise the variable to the given domain */
void
IntSet::initialise (long lb, long ub)
{
    if (values_.size() <= 1) {
        minValue_ = lb;
        maxValue_ = ub;
        size_ = ub - lb + 1;
        values_.resize(size_);
    }
    assert (lb >= minValue_ && ub <= maxValue_);
    if (lb > minValue_)
        values_.set (0, lb - minValue_ - 1, false);
    values_.set (lb - minValue_, ub - minValue_ + 1, true);
    if (ub < maxValue_)
        values_.set (ub - minValue_ + 1, size_, false);
    count_ = ub - lb + 1;
}

long
IntSet::min() const
{
    for (long i = 0; i < size_; i++)
        if (values_[i])
            return i + minValue_;
    assert(false);
    return 0;
}

long
IntSet::max() const
{
    for (long i = size_ - 1; i >= 0; i--)
        if (values_[i])
            return i + minValue_;
    assert(false);
    return 0;
}

void
IntSet::remove (long from, long to)
{
    if (to < minValue_ || from > maxValue_)
        return;
    if (from < minValue_)
        from = minValue_;
    if (to > maxValue_)
        to = maxValue_;
    
    for (long i = from - minValue_; i <= to - minValue_; i++) {
        if (values_[i]) {
            values_[i] = false;
            --count_;
        }
        DEBUG ('E', "Var " << *this << " remove val " << i + minValue_);
    }
}

void
IntSet::remove (long val)
{
    if (val < minValue_ || val > maxValue_)
        return;
    
    if (values_[val - minValue_]) {
        values_[val - minValue_] = false;
        --count_;
        assert (count_ >= 0);
        DEBUG ('E', "Var " << *this << " remove val " << val);
    }
}

void
IntSet::setValue (long value)
{
    assert (minValue_ <= value && value <= maxValue_);
    if (!values_[value - minValue_]) {
        DEBUG ('A', "Assigning invalid value " << value << " to " << *this);
        assert(false);
    }
    if (count_ > 1) {
        DEBUG ('E', "      Assigning value " << value << " to " << *this);
        count_ = 1;
        values_.set (0, size_, false);
        values_[value - minValue_] = true;
    }
}

void
IntSet::copy (const IntSet* other)
{
    minValue_ = other->minValue_;
    maxValue_ = other->maxValue_;
    size_ = other->size_;
    count_ = other->count_;
    values_.copy (other->values_);
}

IntSet&
IntSet::operator=(IntSet& other)
{
    minValue_ = other.minValue_;
    maxValue_ = other.maxValue_;
    size_ = other.size_;
    count_ = other.count_;
    values_ = other.values_;
    return *this;
}

void
IntSet::display (std::ostream& out) const
{
    if (isEmpty())
        out << "[]";
    else if (isBound())
        out << "[" << min() << "](1)";
    else  {
        out << "[";
        const char* sep = "";
        for (long i = 0; i < size_; i++) {
            if (values_[i]) {
                out << sep << i + minValue_;
                sep = ",";
            }
        }
        out << "](" << count_ << ")";
    }
}

// ------------------------

IntSetIter::IntSetIter(const IntSet* intSet) :
    intSet_(intSet),
    nextVal_(intSet->minValue())
{
    advance();
}

bool
IntSetIter::hasNext() const
{
    return (nextVal_ <= intSet_->maxValue());
}

long
IntSetIter::next()
{
    long retVal = nextVal_;
    nextVal_++;
    advance();
    return retVal;
}


void
IntSetIter::advance()
{
    while (
        nextVal_ <= intSet_->maxValue() &&
        !intSet_->contains(nextVal_)
    )
        nextVal_++;
}

