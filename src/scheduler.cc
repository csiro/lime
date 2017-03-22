#include <cassert>
#include <fstream>

#include "lime/error.h"
#include "lime/scheduler.h"
#include "lime/activeobject.h"
#include "lime/strutil.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

int Scheduler::size_ = 0;
ActiveObjectList* Scheduler::events_ = 0;
ActiveObjectList Scheduler::activeList_;
int Scheduler::currTime_ = 0;
bool Scheduler::suspend_ = false;
std::ofstream* Scheduler::logFile_ = NULL;

void
Scheduler::initialise(int eventQueueSize, std::string logFilename)
{
    size_ = eventQueueSize;
    currTime_ = 0;
    suspend_ = false;
    events_ = new std::list<ActiveObject*>[size_];
    if (logFilename.size() > 0) {
        logFile_ = new ofstream (logFilename);
    }
}

void
Scheduler::terminate()
{
    if (events_ != 0) {
        for (int i = 0; i < size_; i++)
            events_[i].clear();
        delete [] events_;
        events_ = 0;
        size_ = 0;
    }
    activeList_.clear();
    if (logFile_ != NULL) {
        logFile_->close();
        delete logFile_;
    }
}

/** Wake an object at the given time. If the object is already in-queue,
 *  this operation is linear in the number of process in the queue
 *  for that time, so use with care.
 */
void
Scheduler::schedule (int atTime, ActiveObject* obj)
{
    if (atTime < currTime_) 
        limeCrash (
            "ActiveObject " << *obj << " scheduled in past: " << atTime <<
            " < " << currTime_
        );
        
    // See if it is already queued
    if (obj->activeObjectState() == ActiveObject::IN_QUEUE) 
        remove (obj);
    else if (obj->activeObjectState() == ActiveObject::ACTIVE) 
        limeCrash ("Scheduler.schedule: Scheduled active object " << *obj);

    events_[atTime % size_].push_back (obj);
    obj->updateActiveObj (ActiveObject::IN_QUEUE, atTime);
}

/** Make an object permanently active */
void Scheduler::activate (ActiveObject* obj)
{
    if (obj->activeObjectState() == ActiveObject::ACTIVE)
        return;
    if (obj->activeObjectState() == ActiveObject::IN_QUEUE) 
        remove (obj);
        
    activeList_.push_back (obj);
    obj->updateActiveObj (ActiveObject::ACTIVE);
}

/** Make an object idle - i.e. unschedule/deactive the object.
 *  Can be scheduled or reactivated later.
 *  This operation is linear in the number of active/scheduled objects,
 *  so use with care.
 */
void
Scheduler::idlize (ActiveObject* obj)
{
    if (obj->activeObjectState() == ActiveObject::ACTIVE) 
        activeList_.remove (obj);
    else if (obj->activeObjectState() == ActiveObject::IN_QUEUE)
        remove (obj);
    obj->updateActiveObj (ActiveObject::IDLE);
}
 
/** This is the main routine that takes over and runs the simulation */
void
Scheduler::runSimulation(int startTime, int endTime)
{
    currTime_ = startTime;
    
    while (currTime_ <= endTime && !suspend_) {
        DEBUG (
            's', currTime_ <<
            " Active list has " << activeList_.size() << " elts"
        );
        // Run active list
        runList (activeList_, false, true);
        
        // Execute the list of scheduled jobs
        // Repeat in case some events have been 
        // added while we've been running
        DEBUG (
            's', currTime_ <<
            " Event list has " << events_[currTime_ % size_].size() << " elts"
        );
        int numRun = runList (events_[currTime_ % size_], true, false);
        while (numRun != 0) {
            DEBUG (
                's', currTime_ <<
                " Event list rerun has " <<
                events_[currTime_ % size_].size() << " elts"
            );
            numRun = runList (events_[currTime_ % size_], true, false);
        }
        currTime_++;
    }
    terminate();
}

/**
 *  Do the "run" method of each of the objects in the list
 *  Param isTimed says whether this is a standard timed queue,
 *  or the activated list.
 */
int
Scheduler::runList (ActiveObjectList& origList, bool isTimed, bool preserve)
{
    if (origList.size() == 0) // Nothing to run
        return 0;
    
    int numRun = 0;

    // Copy the list, to avoid invalidating iterators with insertions/deletions
    ActiveObjectList theList (origList);
    if (!preserve)
        origList.clear();
    
    while (!theList.empty()) {
        ActiveObject* obj = theList.front();
        theList.pop_front();
        
        // Make sure the wake time is curr time
        // (may just be hashed to the same bucket)
        if (isTimed && obj->wakeTime() != currTime_) {
            if (obj->wakeTime() < currTime_) 
                limeCrash ("Object left behind!");
            // Reschedule the object
            // Make idle so scheduler doesn't try to remove it 
            obj->setActiveObjState (ActiveObject::IDLE);
            schedule (obj->wakeTime(), obj);
        }
        else {
            if (isTimed) {
                // Removed from events, so now it is idle
                obj->updateActiveObj (ActiveObject::IDLE);
            }
            obj->run (currTime_);
            numRun++;
        }
    }
    return numRun;
}

void
Scheduler::remove (ActiveObject* obj)
{
    assert (obj->wakeTime() >= 0);
    if (size_ > 0)
        events_[obj->wakeTime() % size_].remove(obj);
}

void
Scheduler::display (ostream& out) 
{
    out << "Scheduler events:" << endl;
    for (int i = 0; i < size_; i++) {
        if (!events_[i].empty()) {
            out << "Time " << i;
            for (
                ActiveObjectIter iter = events_[i].begin();
                iter != events_[i].end();
                ++iter
            )
                out << " " << *(*iter);
            out << endl;
        }
    }
}

// ------------------------

ostream&
operator<< (ostream& out, const Scheduler& scheduler)
{
    scheduler.display (out);
    return out;
}
