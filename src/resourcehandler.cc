
#include "lime/resourcehandler.h"
#include "lime/activeobject.h"

using namespace lime;

void
ResourceHandler::notifyIdle()
{
    if (queue_.size() > 0) {
        auto object = queue_.front();
        queue_.pop_front();
        object->wake();
    }
}
