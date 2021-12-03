#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


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

