#ifndef LIME_DISPLAYABLE_H
#define LIME_DISPLAYABLE_H

#include <iostream>

namespace lime {
    
    /** Interface for displayable objects. Defines output operator based on 
        display method. 
     */
    class Displayable
    {
    public:
        
        /** Prints object on an output stream.
            @param os output stream to print to
         */
        virtual void display(std::ostream& os = std::cout) const = 0;
        
    };
    
    /** Output operator.
        @param os output stream to print to
        @param p displayable object
     */
    std::ostream& operator<<(std::ostream& os, const Displayable& d);

}

#endif
