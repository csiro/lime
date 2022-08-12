
#include <iostream>
#include <vector>

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

    cout << "   anInt: " << config.getInt ("anInt") <<
        " expect 1" << endl;
    cout << " aDouble: " << config.getDouble ("aDouble") <<
        " expect 1.5" << endl;
    cout << "   aBool: " << config.getBool ("aBool") <<
        " expect true " << endl;
    cout << " aString: " << config.getString ("aString") << "<" <<
        " expect hello" << endl;
    cout << "  spcStr: " << config.getString ("spcStr") << "<" <<
        " expect \"this is a multi token str\"" << endl;
    cout << "   aTime: " << config.getTime ("aTime") <<
        " expect 16220" << endl;
    cout << "NotThere: " << config.getInt ("NotThere", 100) <<
        " expect 100 " << endl;
    cout << "  defint: " << config.getInt ("defint", 100) << 
        " expect 20" << endl;
    cout << "  defdbl: " << config.getDouble ("defdbl", 100) << 
        " expect 5.555" << endl;

    cout << "Change anInt" << endl;
    config.addItem ("anInt", 2);
    cout << "   anInt: " << config.getInt ("anInt") <<  
        " expect 2" << endl;
    
    cout << "Change aDouble" << endl;
    config.addItem ("aDouble=3.333");
    cout << "   aDouble: " << config.getDouble ("aDouble") <<  
        " expect 3.333" << endl;

    vector<string> strvec;
    cout << "Str vec result " << config.getVector ("strvec", strvec) << endl;
    cout << "Str vec   vals";
    for (auto str : strvec) cout << " " << str; cout << "<" << endl;
    cout << "        expect this is a mostly comma separated list" << endl;
        
    vector<int> intvec;
    cout << "Int vec result " << config.getVector ("intvec", intvec) << endl;
    cout << "Int vec   vals";
    for (auto i : intvec) cout << " " << i; cout << endl;
    cout << "        expect 1 2 3 4 5 6 7 8 10 20 100" << endl;
        
    limeWarning ("Use default filename");
    LimeError::setFileName ("lime_error.log");

    limeWarning ("Using error file " << LimeError::fileName());
    limeWarning ("You have been warned");
    
    LimeError::setFileName ("/non/existant/name.log");
    limeWarning ("This to default name");
    
    LimeError::setFileName ("lime_error.log");
    limeWarning ("Back to " << LimeError::fileName());

    limeAssert (1);
    limeAssert2 (0, "Now I die");
}
