#pragma once

/**
 *  Hill-climbing accept method
 */

#include "lime/acceptmeth.h"

namespace lime
{
    template <typename ObjType>
    class HillClimb : public  AcceptMeth<ObjType>
    {
    public:
        HillClimb () : AcceptMeth<ObjType>() {}

        void init (ObjType objVal, long numIters, int restarts) override {}
        
        bool accept (ObjType solCost, ObjType incumbCost) override {
            return solCost < incumbCost;
        }
        void iter (long iter, ObjType objVal) override {};
    };
}
