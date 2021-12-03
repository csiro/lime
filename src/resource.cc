
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/


#include "lime/resource.h"
#include "lime/resourcehandler.h"

using namespace lime;

void
Resource::notifyIdle()
{
    handler_->notifyIdle (this);
}
