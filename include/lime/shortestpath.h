#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <set>
#include <list>

#include "lime/spnode.h"

namespace lime {

    class ShortestPath
    {
    public:
        ShortestPath ();
        virtual ~ShortestPath();

        void cleanup();
        
    protected:
        virtual bool isGoal (SPNode* node) {return false;}
        
        SPNode* findPathFrom (SPNode* from);
        SPNode* popFirst();
        void expand(SPNode* node);
        
        std::set <SPNode*,SPNodeStarCmp> frontier_;

        std::list<SPNode*> nodes_;
    };
}
    
    
