#pragma once

#include <iostream>

namespace lime {

    /** A resource in a simulation. Maintains a queue of ActiveObjects
        which are waiting for the resource. These will be woken when a
        resource is available
    */

    class ResourceHandler;
    
    class Resource 
    {
    public:

        /** Constructor. */
        Resource (ResourceHandler* handler) : handler_(handler) {}

        void notifyIdle();
        
    protected:
        ResourceHandler* handler_;
    };

}

