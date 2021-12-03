
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/


#include "lime/resourcehandler.h"
#include "lime/activeobject.h"

using namespace lime;

void
ResourceHandler::notifyIdle(Resource* resource)
{
    for (auto iter = queue_.begin(); iter != queue_.end(); ++iter) {
        auto object = *iter;
        if (object->isCompatible (resource)) {
            queue_.erase (iter);
            object->wake();
            break;
        }
    }
}
