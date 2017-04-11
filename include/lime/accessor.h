#pragma once

#include <vector>

/**
 *  Defines a way of accessing values based on an enumuermaion of the fields
 */

namespace lime {

    union ValueType {
        long longVal;
        unsigned long ulongVal;
        double doubleVal;
        
        operator long&() {return longVal;}
        operator unsigned long&() {return ulongVal;}
        operator double&() {return doubleVal;}
    };

    template<typename T>
    class Accessor
    {
    public:
        template<typename X>
        X& get(T field) {
            if (field >= val_.size())
                val_.resize(field + 1);
            return (X&) val_[field];
        }

    private:
        std::vector<ValueType> val_;
    };
}
