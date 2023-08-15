
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

/** 
 *  A biased choice between ValTypes
*/

#include <assert.h>

#include "lime/biaschoice.h"
#include "lime/numutil.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

/** Remove the choice with the given val
    (for selection without replacement)
*/
void
BiasChoiceT::removeChoice (ValType target)

ValType
BiasChoiceT::choose () 

ValType
BiasChoiceT::inverseChoose () 




void
BiasChoiceT::display (ostream& out) const
{
}

// ------------------------

ostream&
operator<< (ostream& out, const BiasChoiceT& choice)
{
    choice.display (out);
    return out;
}
