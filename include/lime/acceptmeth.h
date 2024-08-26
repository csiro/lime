#pragma once

#include "lime/displayable.h"

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/

/**
 *  Base class for soluton accepters - e.g. hill-climbing and
 *  simulated annealing.
 *  Templated on the type of the objective
 */

namespace lime
{
    template <typename ObjType>
    class AcceptMeth : public Displayable
    {
    public:
        AcceptMeth () {}

        virtual void init (ObjType objVal, long numIters, int restarts) = 0;
        
        virtual bool accept (ObjType solCost, ObjType incumbCost) = 0;

        virtual void iter (long iter, ObjType objVal) = 0;
    };
}
