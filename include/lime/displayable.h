#pragma once

#include <iostream>
#include <string>

namespace lime {
    
    /** Interface for displayable objects. Defines output operator based on 
        display method. 
     */
    class Displayable
    {
    public:

        /** Override one of the two following methods */
        virtual std::string name() const {return std::string("");}
        
        /** Prints object on an output stream.
            Can be overridden to print more detail.
            @param os output stream to print to
         */
        virtual void display(std::ostream& os = std::cout) const
        {
            os << name();
        }
        
    };
    
    /** Output operator.
        @param os output stream to print to
        @param p displayable object
     */
    std::ostream& operator<<(std::ostream& os, const Displayable& d);

}

