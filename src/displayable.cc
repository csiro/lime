#include <iostream>
#include "lime/displayable.h"

using namespace lime;

std::ostream& lime::operator<<(std::ostream& os, const Displayable& p)
{
    p.display(os);
    return os;
}
