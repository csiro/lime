#ifndef LIME_SPNODE_H
#define LIME_SPNODE_H

/**
   Abstract class for nodes in a shortest path search
*/

#include <iostream>

namespace lime {

    class SPNode
    {
    public:
        SPNode(int cost);
        virtual ~SPNode();
        
        int cost() const {return cost_;}
        void setCost (int cost) {cost_ = cost;}
        SPNode* parent() const {return parent_;}
        void setParent (SPNode* parent) {parent_ = parent;}

        virtual SPNode* firstNeighbour() = 0;
        virtual SPNode* nextNeighbour() = 0;   
        virtual bool isLessThan(const SPNode* other) const = 0;

    protected:
        int cost_;
        lime::SPNode* parent_;
    };

    struct SPNodePtrCmp
    {
        bool operator() (const SPNode* a, const SPNode* b) const {
            if (a->cost() == b->cost())
                return a->isLessThan(b);
            return a->cost() < b->cost();
        }
    };
}

#endif
