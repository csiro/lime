#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <list>

/** Simulation scheduler

    Initialise using
      Scheduler::initialise(size)
    where size is the length of the event queue. Suggest around
    100,000. Events will wrap around if necessary. 

    Run using
      runSimulation (start, end)

    Easiest to schedule events using calls from active objects.
*/

namespace lime {

    class ActiveObject;
    typedef std::list<ActiveObject*> ActiveObjectList;
    typedef std::list<ActiveObject*>::iterator ActiveObjectIter;

    class Scheduler
    {
    public:
        /** Initialise the simulation. Must be called first */
        static void initialise(
            int eventQueueSize, std::ofstream* logFile = NULL
        );

        /** Schedule the object to be run at a particular time */
        static void schedule (int atTime, ActiveObject* obj);

        /** Make an object permanently active */
        static void activate (ActiveObject* obj);

        /** Make an object idle - i.e. unschedule/deactive the object.
         *  Can be scheduled or reactivated later.
         */
        static void idlize (ActiveObject* obj);

        /** Return the current time in the simulation */
        static int currTime() {return currTime_;}

        static size_t numEvents (int time) {return events_[time % size_].size();}

        /** This is the main routine that takes over and runs the simulation */
        static void runSimulation(int startTime, int endTime);

        static std::ofstream* logFile() {return logFile_;}
        
        /** Prematurely suspend the simulation */
        static void suspend() {suspend_ = true;}

        static void display (std::ostream& os = std::cout);
    
    protected:
        /** Terminate the simulation*/
        static void terminate();
        /** Run all the jobs in the list */
        static int runList (
            ActiveObjectList& list, bool isTimed, bool preserve
        );
        static void remove (ActiveObject* obj);
    
    
        /** The size of the event queue */
        static int size_;
    
        /** The event lists. Maintained as a circular list. */
        static ActiveObjectList* events_;
    
        /** The list of (permanently) active objects. */
        static ActiveObjectList activeList_;

        /** The current time of the simulation */
        static int currTime_;
    
        /** A flag to prematurely suspend the simulation */
        static bool suspend_;

        static std::ofstream* logFile_;

    private:
        Scheduler() {}
        virtual ~Scheduler() {}
    };

#define SIMLOG(X) {if (Scheduler::logFile() != NULL) {*Scheduler::logFile() << Scheduler::currTime() << " " << X << std::endl;}}

} // namespace

