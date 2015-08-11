
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <20 Feb 2013 11:29:07>"

#include <assert.h>

#include "lime/constants.h"
#include "lime/spnode.h"

using namespace std;
using namespace lime;

SPNode::SPNode (int cost) :
    cost_(cost),
    parent_(NULL)
{
}

SPNode::~SPNode ()
{
}
