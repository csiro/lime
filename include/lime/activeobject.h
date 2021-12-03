#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>

#include "lime/scheduler.h"
#include "lime/displayable.h"

namespace lime {
    
    class Resource;

    /** A class representing active objects in a simulation. Active objects can
        by in state ACTIVE, in which case they wake every time unit. Otherwise
        they wake when scheduled. If IDLE, they are not currently scheduled to
        wake. Objects are scheduled for wake-up using wakeAt or wakeAfter. The
        virtual method 'run' is called when the object wakes.
    */
    class ActiveObject : public Displayable
    {
    public:

        /** An enum defining the possible states of an active object. */
        enum AOState {
            IDLE,
            IN_QUEUE,
            ACTIVE
        };

        /** Constructor. */
        ActiveObject() : state_(IDLE), wakeTime_(-1) { }

        /** Destructor. */
        virtual ~ActiveObject()
        {
            idlize();
        }
        
        /** Set object to wake at every time step. */
        void activate ()
        {
            Scheduler::activate (this);
        }

        /** Returns the wake time.
            @remark only sensible if State == IN_QUEUE.
         */
        int wakeTime() const { return wakeTime_; }

        /** Returns activation state. */
        const AOState& activeObjectState() const { return state_; }

        /** Set object to wake now. */
        void wake () { wakeAfter (0); }

        /** @copydoc Scheduler::idlize() */
        void idlize ()
        {
            Scheduler::idlize (this);
        }

        /** Schedule object to wake at a given time.
            @param atTime time step at which the object will be awaken.
         */
        void wakeAt (int atTime)
        {
            Scheduler::schedule (atTime, this);
        }

        /** Reschedule after an elapsed time */
        void wakeAfter (int deltaS)
        {
            Scheduler::schedule (Scheduler::currTime() + deltaS, this);
        }

        /** Set state and wake time ** only Scheduler may call this ** */
        void updateActiveObj (AOState state, int wakeTime = -1)
        {
            state_ = state;
            wakeTime_ = wakeTime;
        }
        /** Set state (used by Scheduler).
            @param state new state of the object.
         */
        void setActiveObjState (AOState state) { state_ = state; }

        /** Virtual procedure run when the object is woken.
            @param currTime the current time step.
         */
        virtual void run (int currTime) = 0;

        /** For use with Resources. Override if some ActiveObjects are not
            compatible with some Resources
        */
        virtual bool isCompatible (Resource* resource) {return true;}
        
        /** @copydoc Displayable::display(std::ostream&) */
        void display (std::ostream& os = std::cout) const override = 0;

    protected:

        /** Activation state. */
        AOState state_;

        /** When will I wake again (-1 if not set). */
        int wakeTime_;
    };

}

