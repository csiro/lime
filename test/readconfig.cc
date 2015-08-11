
#include "lime/configreader.h"
#include "config.h"

using namespace std;
using namespace lime;

void
read (const char* filename, Config& config)
{
    ConfigReader reader (filename);

    reader.readInt ("anInt", config.anInt);
    reader.readDouble ("aDouble", config.aDouble);
    reader.readBool ("aBool", config.aBool);
    reader.readString ("aString", &config.aString);
    reader.readTime ("aTime", config.aTime);

    reader.close();
}

int
main ()
{
    Config config;

    read ("config", config);
    
    return 0;
}
