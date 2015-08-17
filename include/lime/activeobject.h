#ifndef LIME_ACTIVEOBJECT_H
#define LIME_ACTIVEOBJECT_H

#include <iostream>

namespace lime {

    /** A class representing active objects in a simulation. Active objects can
        by in state ACTIVE, in which case they wake every time unit. Otherwise
        they wake when scheduled. If IDLE, they are not currently scheduled to
        wake. Objects are scheduled for wake-up using wakeAt or wakeAfter. The
        virtual method 'run' is called when the object wakes.
    */
    class ActiveObject
    {
    public:

        /** An enum defining the possible states of an active object. */
        enum State {
            IDLE,
            IN_QUEUE,
            ACTIVE
        };

        /** Constructor. */
        ActiveObject();

        /** Destructor. */
        virtual ~ActiveObject();

        /** Returns the wake time.
            @remark only sensible if State == IN_QUEUE.
         */
        int wakeTime() const { return wakeTime_; }

        /** Returns activation state. */
        const State& activeObjectState() const { return state_; }

        /** Set object to wake at every time step. */
        void activate ();

        /** Set object to wake now. */
        void wake () { wakeAfter (0); }

        /** @copydoc Scheduler::idlize() */
        void idlize ();

        /** Schedule object to wake at a given time.
            @param atTime time step at which the object will be awaken.
         */
        void wakeAt (int atTime);

        /** Reschedule after an elapsed time */
        void wakeAfter (int deltaS);

        /** Set state and wake time ** only Scheduler may call this ** */
        void updateActiveObj (State state, int wakeTime = -1)
        {
            state_ = state;
            wakeTime_ = wakeTime;
        }
        /** Set state (used by Scheduler).
            @param state new state of the object.
         */
        void setActiveObjState (State state) { state_ = state; }

        /** Virtual display method.
            @param os the stream onto which this object must be "displayed".
         */
        virtual void display (std::ostream& os) const = 0;

        /** Virtual procedure run when the object is woken.
            @param currTime the current time step.
         */
        virtual void run (int currTime) = 0;

    protected:

        /** Activation state. */
        State state_;

        /** When will I wake again (-1 if not set). */
        int wakeTime_;
    };

    std::ostream& operator<< (std::ostream&, const ActiveObject&);

}

#endif
