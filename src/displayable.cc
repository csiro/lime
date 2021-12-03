
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <iostream>
#include "lime/displayable.h"

using namespace lime;

std::ostream& lime::operator<<(std::ostream& os, const Displayable& p)
{
    p.display(os);
    return os;
}
