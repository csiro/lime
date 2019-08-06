#pragma once

#include <vector>

#include "lime/strutil.h"

namespace lime
{

    /** A class to read configurations from the command line. */
    class ConfigReader
    {
    public:
        
        /** Constructor. Initialises the reader with the contents of a file.
            @param filename name of the file to read
            @remarks the file should contain key <spaces> value pairs.
         */
        ConfigReader(const char* filename);
        
        /** Constructor. Initialises the reader with a vector of strings.
            @param configs vector of strings
            @remarks each string should be either key:value or key=value,
                     alternatively they can come as two separate strings
                     of the form:
                         key=
                         value
                     or
                         key:
                         value
         */
        ConfigReader(std::vector<const char*>& configs);
        
        /** (Virtual) destructor. */
        virtual ~ConfigReader();

        /** Get the value of an int, and store it in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readInt (const char* name, int& val) const;
        
        /** Get the value of a long, and store it in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readLong (const char* name, long& val) const;
        
        /** Get the value of a double, and store it in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readDouble (const char* name, double& val) const;
        
        /** Get the value of a bool, and store it in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readBool (const char* name, bool& val) const;
        
        /** Get the value of a string, and store it in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
            @remarks Updates val to point to a lime::strdup copy of the string.
                     Make sure to delete [] the value at cleanup.
         */
        void readString (const char* name, const char** val) const;
        
        /** Get the value of a string, and store in val.
            Updates val to point to a lime::strdup copy of the string.
        */
        void readString (const char* name, std::string val);
        
        /** Get the value of a time expressed as hh:mm[:ss] or as sss, and store
            in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readTime (const char* name, int& val);
        
        /** Get the value of a time expressed as hh:mm[:ss] or as sss, and store
            in the passed reference.
            @param name name of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        void readTime (const char* name, long& val);
        
        /** Close configuration reader.
            @remarks complain if some configuration was not used.
         */
        void close();

    protected:
        
        /** A struct representing a single configuration item. */
        struct ConfigItem
        {
            /** Constructor. Stores a copy of the key and value as strings.
                @param key key (string)
                @param value value (as string)
                @remarks makes copies of the strings, delete in the destructor.
             */
            ConfigItem (const char* key_, const char* val_) :
                key(lime::strdup (key_)),
                val(lime::strdup (val_))
            { }
            
            /** Destructor. */
            ~ConfigItem ()
            {
                delete [] key;
                delete [] val;
            }
            
            /** Key (string). */
            const char* key;
            
            /** Value (as string). */
            const char* val;
        };
        
        /** Get the original value of a configuration (string).
            @param key name of the configuration to retrieve
         */
        const char* valFor(const char* key) const;

        /** Name of the file where the configurations were read from. */
        const char* filename_;
        
        /** List of (const) configuration items. */
        std::vector<const ConfigItem*> items_;
        
        /** Whether a configuration item was used or not. */
        bool* used_;
    };
}

