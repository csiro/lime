#pragma once

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
        virtual bool isGoal (SPNode* node) = 0;
        
        SPNode* findPathFrom (SPNode* from);
        SPNode* popFirst();
        void expand(SPNode* node);
        
        std::set <SPNode*,SPNodePtrCmp> frontier_;

        std::list<SPNode*> nodes_;
    };
}
    
    
