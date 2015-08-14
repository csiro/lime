
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <20 Feb 2013 11:28:52>"

#include <cassert>

#include "lime/shortestpath.h"


using namespace std;
using namespace lime;

ShortestPath::ShortestPath () :
    frontier_(SPNodePtrCmp()),
    nodes_()
{
}

ShortestPath::~ShortestPath ()
{
    cleanup();
}

SPNode*
ShortestPath::findPathFrom (SPNode* from)
{
    nodes_.push_back (from);
    frontier_.insert (from);
    while (!frontier_.empty()) {
        SPNode* curr = popFirst();
        if (this->isGoal(curr))
            return curr;
        expand (curr);
    }
    // No path to goal
    return NULL;
}

SPNode* 
ShortestPath::popFirst()
{
    SPNode* node = *frontier_.begin();
    frontier_.erase (frontier_.begin());
    return node;
}

void
ShortestPath::expand(SPNode* node)
{
    for (
        SPNode* child = node->firstNeighbour();
        child != NULL;
        child = node->nextNeighbour()
    ) {
        child->setParent (node);
        frontier_.insert (child);
        nodes_.push_back (child);
    }
}

void
ShortestPath::cleanup ()
{
    for (
        std::list<SPNode*>::iterator iter = nodes_.begin();
        iter != nodes_.end();
        ++iter
    ) {
        delete *iter;
    }
    nodes_.clear();
}
