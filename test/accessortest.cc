

#include <iostream>

#include "lime/accessor.h"

using namespace lime;



enum ValType {ONE, TWO, THREE};

class Test : public Accessor
{
public:

    void doTest()
    {
        get<double>(THREE) = 1.2345;
        get<long>(TWO) = -10;
        get<unsigned long>(ONE) = 100;

        std::cout << "Values are: ONE " << get<unsigned long>(ONE) <<
            " TWO " << get<long>(TWO) <<
            " THREE " << get<double>(THREE) << std::endl;
    }
        
};


int main ()
{
    Test test;

    test.doTest();
    
}


    
