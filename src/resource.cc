
#include "lime/resource.h"
#include "lime/resourcehandler.h"

using namespace lime;

void
Resource::notifyIdle()
{
    handler_->notifyIdle ();
}
