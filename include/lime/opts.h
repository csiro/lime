#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


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
            std::string help_str,
            const char* config_name = NULL
        );
        void add_opt_filename (
            const char* switch_str, std::string* str_switch,
            std::string help_str,
            const char* config_name = NULL
        );
        void add_opt (
            const char* switch_str, int* int_switch,
            std::string help_str,
            const char* config_name = NULL
        );
        void add_opt (
            const char* switch_str, double* double_switch,
            std::string help_str,
            const char* config_name = NULL
        );
        void add_opt (
            const char* switch_str, Config* config_switch,
            std::string help_str
        );
        // Bool options are flipped if switch-str is present
        void add_opt (
            const char* switch_str, bool* bool_switch,
            std::string help_str,
            const char* config_name = NULL
        );

        void add_arg(
            const char* usage_str, std::string* str_ptr, std::string help_str,
            const char* config_name = NULL
        );
        void add_optional_arg (
            const char* usage_str, std::string* str_ptr, std::string help_str,
            const char* config_name = NULL
        );
        void add_arg (
            const char* usage_str, int* int_ptr, std::string help_str,
            const char* config_name = NULL
        );
        void add_optional_arg (
            const char* usage_str, int* int_ptr, std::string help_str,
            const char* config_name = NULL
        );
        void add_arg (
            const char* usage_str, double* double_ptr, std::string help_str,
            const char* config_name = NULL
        );
        void add_optional_arg (
            const char* usage_str, double* double_ptr, std::string help_str,
            const char* config_name = NULL
        );
            
        void usage (
            const char* message1 = 0, const char* message2 = 0
        );
        void usage (std::string msg);

        bool process (int argc, const char* argv[], Config* config = NULL);
        
    protected:
        enum ValType {STR, FILENAME, INT, BOOL, DBL, CONFIG};
        struct Entry
        {
            const char* switch_str;
            std::string help_str;
            ValType val_type;
            std::string* str_ptr;
            int* int_ptr;
            bool* bool_ptr;
            double* double_ptr;
            Config* config_ptr;
            const char* config_name;

            Entry (
                const char* switch_str_,
                std::string help_str_,
                ValType val_type_,
                std::string* str_ptr_,
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(val_type_),
                str_ptr(str_ptr_),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(NULL),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                int* int_ptr_,
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(INT),
                str_ptr(NULL),
                int_ptr(int_ptr_),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(NULL),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                bool* bool_ptr_,
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(BOOL),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(bool_ptr_),
                double_ptr(NULL),
                config_ptr(NULL),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                double* double_ptr_,
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(DBL),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(double_ptr_),
                config_ptr(NULL),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                Config* config_ptr_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(CONFIG),
                str_ptr(NULL),
                int_ptr(NULL),
                bool_ptr(NULL),
                double_ptr(NULL),
                config_ptr(config_ptr_),
                config_name(NULL)
            {
            }
        };
        bool switch_exists (const char* switch_str);
        void do_config_defaults (Config* config);
        
        std::string description_;
        const char* build_date_;
        const char* build_time_;
        std::vector<Entry> switches_;
        std::vector<Entry> args_;
        int optional_args_;
        std::string cmd_;
        bool uses_config_;
    };
}

