#ifndef LIME_ACTIVEOBJECT_H
#define LIME_ACTIVEOBJECT_H

#include <iostream>

/** Active objects in a simulation.

    Active objects can by in state ACTIVE, in which case they wake
    every time unit. Otherwise they wake when scheduled. If IDLE, they
    are not currently scheduled to wake.

    The virtual method 'run' is called when the object wakes.

    Schedule wake-up using wakeAt or wakeAfter

*/
    

namespace lime {
    
    class ActiveObject
    {
    public:
        enum State {IDLE, IN_QUEUE, ACTIVE};

        ActiveObject();
        virtual ~ActiveObject();

        // Wake time. Note: only sensible if State == IN_QUEUE
        int wakeTime() const {return wakeTime_;}
        State activeObjectState() const {return state_;}
    
        /** 
         *  This procedure is called when the object is woken.
         *  Procedure is passed the current time.
         */
        virtual void run (int currTime) = 0;
    
        /** Wake at every time step */
        void activate ();

        /** Wake now */
        void wake () {wakeAfter (0);}
    
        /** Idlize this. See Scheduler for more details */
        void idlize ();
    
        /** Reschedule at given time */
        void wakeAt (int atTime);
    
        /** Reschedule after an elapsed time */
        void wakeAfter (int deltaS);

        /** Set state and wake time ** only Scheduler may call this ** */
        void updateActiveObj (State state, int wakeTime = -1) {
            state_ = state;
            wakeTime_ = wakeTime;
        }
        /** Set state ** only Scheduler may call this ** */
        void setActiveObjState (State state) {state_ = state;}
    
        virtual void display (std::ostream&) const = 0;
    
    protected:
        /** When do I wake next? or -1 if no wake set */
        State state_;

        /** When will I wake again */
        int wakeTime_;
    };

    std::ostream& operator<< (std::ostream&, const ActiveObject&);

} // namespace

#endif
