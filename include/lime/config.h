#pragma once

#include <map>
#include <vector>
#include <memory>

#include "lime/displayable.h"

namespace lime
{

    /** A class to read configurations from file.
        This config is free-format: any key and value is allowed
        (ConfigReader demands keys are pre-declared)
     */
    class Config : public Displayable
    {
    public:
        
        /** Constructor. Initialises the reader with the contents of a file.
            @param filename name of the file to read
            @remarks the file should contain key <spaces> value pairs.
         */
        Config ();
        Config (std::string filename);
        Config (const Config& other);
        
        void read (std::string filename);
        void read (const char* filename) {read (std::string(filename));}
        
        void setDefaults (std::vector<std::string> defaults);
        
        void addItem (std::string key, std::string val);
        void addItem (const char* key, const char* val);
        void addItem (std::string key, int val);
        void addItem (std::string key, long val);
        void addItem (std::string key, double val);
        void addItem (std::string key, unsigned long val);
        void addItem (std::string key, std::vector<int> val);
        void addItem (std::string key, std::vector<long> val);
        void addItem (std::string key, std::vector<unsigned long> val);
        void addItem (std::string key, std::vector<double> val);

        // addItem with disambiguated args
        void addString(std::string key, std::string val);
        void addInt (std::string key, int val);
        void addLong (std::string key, long val);
        void addDouble (std::string key, double val);
        void addULong (std::string key, unsigned long val);
        
        /** Add items in the form "key=val" or "key:val" */
        void addItem (std::string keyVal);
        
        /** Get the value of an int */
        int getInt (std::string key, int defaultVal = 0);
        int getInt (const char* key, int defaultVal = 0);
        
        /** Get the value of a long */
        long getLong (std::string key, long defaultVal = 0);
        long getLong (const char* key, long defaultVal = 0);
        
        /** Get the value of a double */
        double getDouble (std::string key, double defaultVal = 0.0);
        double getDouble (const char* key, double defaultVal = 0.0);
        
        /** Get the value of a unsigned */
        unsigned long getUnsigned (
            std::string key, unsigned long defaultVal = 0
        );
        unsigned long getUnsigned (
            const char* key, unsigned long defaultVal = 0
        );
        
        /** Get the value of a bool, and store it in the passed reference.
            @param key key of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        bool getBool (std::string key, bool defaultVal = false);
        bool getBool (const char* key, bool defaultVal = false);
        
        /** Get the value of a string, and store it in the passed reference.
            @param key key of the configuration to retrieve
            @param val reference to the location where the value must be read
            @remarks Updates val to point to a lime::strdup copy of the string.
                     Make sure to delete [] the value at cleanup.
         */
        std::string getString (
            std::string key, std::string defaultVal = std::string("")
        );
        std::string getString (
            const char* key, std::string defaultVal = std::string("")
        );
        /** Get the value of a time expressed as hh:mm[:ss] or as sss, and store
            in the passed reference.
            @param key key of the configuration to retrieve
            @param val reference to the location where the value must be read
         */
        int getTime (std::string key, int defaultVal = 0);
        int getTime (const char* key, int defaultVal = 0);

        bool getVector (std::string key, std::vector<std::string> vec);
        bool getVector (std::string key, std::vector<int> vec);
        bool getVector (std::string key, std::vector<long> vec);
        bool getVector (std::string key, std::vector<unsigned long> vec);
        bool getVector (std::string key, std::vector<double> vec);
        
        std::string show (const char* sep = " ") const;
        
        void display(std::ostream& os = std::cout) const override
        {
            os << show();
        }
        
    protected:
        std::string valFor(std::string key) const;
        
        using KeyMap = std::map<std::string,std::string>;
        
        /** Name of the file where the configurations were read from. */
        std::string filename_;

        KeyMap map_;
    };

    using ConfigPtr = std::shared_ptr<Config>;
}

