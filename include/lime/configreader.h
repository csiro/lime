#ifndef LIME_CONFIGREADER_H
#define LIME_CONFIGREADER_H

/**
 *  Defines a object that handles locking a file for exclusive access
 */

#include <vector>

#include "lime/strutil.h"

namespace lime {

    class ConfigReader
    {
    public:
        /** Initialise reader with contents of a file.
            File should contain
            key <spaces> value
            pairs
        */
        ConfigReader(const char* filename);
        
        /** Initialise reader with a vector of strings
            Each string should be either
            key:value 
            or
            key=value
            Alternatively, they can come as two separate strings
            key=
            value
            or
            key:
            value
        */
        ConfigReader(std::vector<const char*>& configs);
        virtual ~ConfigReader();

        /** Get the value of an int, and store in val */
        void readInt (const char* name, int& val);
        /** Get the value of a long, and store in val */
        void readLong (const char* name, long& val);
        /** Get the value of a double, and store in val */
        void readDouble (const char* name, double& val);
        /** Get the value of a bool, and store in val */
        void readBool (const char* name, bool& val);
        /** Get the value of a string, and store in val.
            Updates val to point to a lime::strdup copy of the string.
            Make sure to delete [] the value at cleanup
        */
        void readString (const char* name, const char** val);
        /** Get the value of a string, and store in val.
            Updates val to point to a lime::strdup copy of the string.
        */
        void readString (const char* name, std::string val);
        /** Get the value of a time expressed as hh:mm[:ss] or as sss.
            Store in val as seconds */
        void readTime (const char* name, int& val);
        void readTime (const char* name, long& val);
        
        void close();

    protected:
        struct ConfigItem
        {
            const char* key;
            const char* val;
            
            ConfigItem (const char* key_, const char* val_) :
                key(lime::strdup (key_)),
                val(lime::strdup (val_))
            {
            }
            ~ConfigItem ()
            {
                delete [] key;
                delete [] val;
            }
        };
        typedef std::vector<ConfigItem*> ItemList;
        typedef ItemList::iterator ItemIter;
        const char* valFor(const char* key);

        const char* filename_;
        ItemList items_;
        bool* used_;
    };
}

#endif
