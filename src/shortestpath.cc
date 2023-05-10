
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cassert>

#include "lime/shortestpath.h"


using namespace std;
using namespace lime;

ShortestPath::ShortestPath () :
    frontier_(SPNodeStarCmp()),
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
