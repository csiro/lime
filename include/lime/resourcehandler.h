#pragma once

#include <iostream>
#include <list>

namespace lime {

    /** A resource handler for a group of resources.
        Queues processes waiting for the resource, and wakes them
        when one becomes idle.
    */

    class ActiveObject;
    class Resource;

    class ResourceHandler 
    {
    public:

        /** Constructor. */
        ResourceHandler () : queue_() {}

        void notifyIdle(Resource* resource);
        size_t numInQueue() const {return queue_.size();}
        void addToQueue (ActiveObject* object) {queue_.push_back (object);}
        
    protected:
        std::list<ActiveObject*> queue_;
    };

}

