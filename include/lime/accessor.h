#pragma once

#include <vector>
#include <map>

/**
 *  Defines a way of accessing values based on field names, or
 *  an enumeration of fields
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

        size_t indexFor (std::string name) {
            auto iter = map_.find(name);
            if (iter == map_.end()) {
                map_[name] = map_.size();
                return map_[name];
            }
            return iter->second;
        }

    private:
        std::vector<ValueType> val_;
        static std::map<std::string,size_t> map_;
    };
}
