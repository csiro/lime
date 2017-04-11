#pragma once

#include <vector>

/**
 *  Defines a way of accessing values based on an enumuermaion of the fields
 */

namespace lime
{
  class Accessor
  {
  public:

    union ValueType
    {
      long longVal;
      unsigned long ulongVal;
      double doubleVal;

      operator long&() {return longVal;}
      operator unsigned long&() {return ulongVal;}
      operator double&() {return doubleVal;}
    };

    template<typename T>
    T& get(const std::vector<ValueType>::size_type& field)
    {
      if (field >= val_.size())
        val_.resize(field + 1);
      return (T&) val_[field];
    }

  private:
    std::vector<ValueType> val_;
  };
}
