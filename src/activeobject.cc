
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <22 May 2013 12:02:14>"

#include <assert.h>

#include "lime/activeobject.h"
#include "lime/scheduler.h"

using namespace std;
using namespace lime;

ActiveObject::ActiveObject () :
    state_(IDLE),
    wakeTime_(-1)
{
}

ActiveObject::~ActiveObject ()
{
    idlize();
}

void
ActiveObject::activate ()
{
    Scheduler::activate (this);
}

/** Idlize this. See Scheduler for more details */
void
ActiveObject::idlize () {
    Scheduler::idlize (this);
}

void
ActiveObject::wakeAt (int atTime)
{
    Scheduler::schedule (atTime, this);
}

void
ActiveObject::wakeAfter (int deltaS)
{
    Scheduler::schedule (Scheduler::currTime() + deltaS, this);
}

// ------------------------

ostream&
lime::operator<< (ostream& out, const ActiveObject& activeObject)
{
    activeObject.display (out);
    return out;
}
