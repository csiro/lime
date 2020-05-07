
#include <iostream>

#include "lime/config.h"
#include "lime/error.h"

using namespace std;
using namespace lime;

/*
#include "lime/configreader.h"
#include "config.h"

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
*/

/* Test new Config reader */
using namespace std;
using namespace std;

int
main ()
{
    Config config;

    config.setDefaults ({"defInt=20","defDbl=5.555"});
        
    config.read ("config");

    cout << "   anInt: " << config.getInt ("anInt") << endl;
    cout << " aDouble: " << config.getDouble ("aDouble") << endl;
    cout << "   aBool: " << config.getBool ("aBool") << endl;
    cout << " aString: " << config.getString ("aString") << endl;
    cout << "   aTime: " << config.getTime ("aTime") << endl;
    cout << "NotThere: " << config.getInt ("NotThere", 100) << endl;
    cout << "  defint: " << config.getInt ("defint", 100) << endl;
    cout << "  defdbl: " << config.getDouble ("defdbl", 100) << endl;

    cout << "Change anInt" << endl;
    config.addItem ("anInt", 2);
    cout << "   anInt: " << config.getInt ("anInt") << endl;
    
    cout << "Change aDouble" << endl;
    config.addItem ("aDouble=3.333");
    cout << "   aDouble: " << config.getDouble ("aDouble") << endl;

    limeWarning ("Use default filename");
    LimeError::setFileName ("lime_error.log");

    limeWarning ("Using error file " << LimeError::fileName());
    limeWarning ("You have been warned");
    
    LimeError::setFileName ("/non/existant/name.log");
    limeWarning ("This to default name");
    
    LimeError::setFileName ("lime_error.log");
    limeWarning ("Back to " << LimeError::fileName());

    limeCrash ("Now I die");
}
