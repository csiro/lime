#pragma once

#include <map>
#include <string>
#include <vector>

namespace lime
{
    class Config;

    /** A class to read optsurations from file.
        This opts is free-format: any key and value is allowed
        (OptsReader demands keys are pre-declared)
     */
    class Opts 
    {
    public:
        /** Constructor. Initialises the reader with the contents of a file.
            @param filename name of the file to read
            @remarks the file should contain key <spaces> value pairs.
         */
        Opts (
            std::string description,
            const char* build_date = __DATE__,
            const char* build_time = __TIME__
        );
        void add_opt (
            const char* switch_str, std::string* str_switch,
            const char* help_str
        );
        void add_opt_filename (
            const char* switch_str, std::string* str_switch,
            const char* help_str
        );
        void add_opt (
            const char* switch_str, int* int_switch,
            const char* help_str
        );
        void add_opt (
            const char* switch_str, double* double_switch,
            const char* help_str
        );
        void add_opt (
            const char* switch_str, Config* config_switch,
            const char* help_str
        );
        // Bool options are flipped if switch-str is present
        void add_opt (
            const char* switch_str, bool* bool_switch,
            const char* help_str
        );

        void add_arg (
            const char* usage_str, std::string* str_ptr, const char* help_str
        );
        void add_optional_arg (
            const char* usage_str, std::string* str_ptr, const char* help_str
        );
        void add_arg (
            const char* usage_str, int* int_ptr, const char* help_str
        );
        void add_optional_arg (
            const char* usage_str, int* int_ptr, const char* help_str
        );
        void add_arg (
            const char* usage_str, double* double_ptr, const char* help_str
        );
        void add_optional_arg (
            const char* usage_str, double* double_ptr, const char* help_str
        );
            
        void usage (
            const char* cmd, const char* message1 = 0, const char* message2 = 0
        );
        void usage (const char* cmd, std::string msg);

        bool process (int argc, const char* argv[], Config* config = NULL);
        
    protected:
        enum ValType {STR, FILENAME, INT, BOOL, DBL, CONFIG};
        struct Entry
        {
            const char* switch_str;
            const char* help_str;
            ValType val_type;
            std::string* str_ptr;
            int* int_ptr;
            bool* bool_ptr;
            double* double_ptr;
            Config* config_ptr;

            Entry (
                const char* switch_str_,
                const char* help_str_,
                ValType val_type_,
                std::string* str_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(val_type_),
                str_ptr(str_ptr_),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(NULL)
            {
            }

            Entry (
                const char* switch_str_,
                const char* help_str_,
                int* int_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(INT),
                str_ptr(NULL),
                int_ptr(int_ptr_),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(NULL)
            {
            }

            Entry (
                const char* switch_str_,
                const char* help_str_,
                bool* bool_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(BOOL),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(bool_ptr_),
                double_ptr(NULL),
                config_ptr(NULL)
            {
            }

            Entry (
                const char* switch_str_,
                const char* help_str_,
                double* double_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(DBL),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(double_ptr_),
                config_ptr(NULL)
            {
            }

            Entry (
                const char* switch_str_,
                const char* help_str_,
                Config* config_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(CONFIG),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(config_ptr_)
            {
            }
        };

        std::string description_;
        const char* build_date_;
        const char* build_time_;
        std::vector<Entry> switches_;
        std::vector<Entry> args_;
        int optional_args_;
    };
}

