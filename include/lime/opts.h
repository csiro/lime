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
        enum BoolArgType {SWITCH, TAKES_ARG};
        
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
            const char* config_name = nullptr
        );
        void add_opt_filename (
            const char* switch_str, std::string* str_switch,
            std::string help_str,
            const char* config_name = nullptr
        );
        void add_opt_filename (
            const char* switch_str, std::vector<std::string>* strvec_ptr,
            std::string help_str,
            const char* config_name = nullptr
        );
        void add_opt (
            const char* switch_str, int* int_switch,
            std::string help_str,
            const char* config_name = nullptr
        );
        void add_opt (
            const char* switch_str, double* double_switch,
            std::string help_str,
            const char* config_name = nullptr
        );
        void add_opt (
            const char* switch_str, Config* config_switch,
            std::string help_str
        );
        // Bool options are either flipped if switch-str is present,
        // or take an arg
        void add_opt (
            const char* switch_str, bool* bool_switch, BoolArgType arg_type,
            std::string help_str,
            const char* config_name = nullptr
        );
        // Default for bool is to flip if switch-str is present
        void add_opt (
            const char* switch_str, bool* bool_switch, 
            std::string help_str,
            const char* config_name = nullptr
        )  {
            add_opt (
                switch_str, bool_switch, SWITCH, 
                help_str,
                config_name
            );
        }

        void add_arg(
            const char* usage_str, std::string* str_ptr, std::string help_str,
            const char* config_name = nullptr
        );
        void add_optional_arg (
            const char* usage_str, std::string* str_ptr, std::string help_str,
            const char* config_name = nullptr
        );
        void add_arg(
            const char* usage_str, std::vector<std::string>* strvec_ptr,
            std::string help_str, const char* config_name = nullptr
        );
        void add_arg (
            const char* usage_str, int* int_ptr, std::string help_str,
            const char* config_name = nullptr
        );
        void add_optional_arg (
            const char* usage_str, int* int_ptr, std::string help_str,
            const char* config_name = nullptr
        );
        void add_arg (
            const char* usage_str, double* double_ptr, std::string help_str,
            const char* config_name = nullptr
        );
        void add_optional_arg (
            const char* usage_str, double* double_ptr, std::string help_str,
            const char* config_name = nullptr
        );
            
        void usage (
            const char* message1 = 0, const char* message2 = 0
        );
        void usage (std::string msg);

        bool process (int argc, const char* argv[], Config* config = nullptr);
        
    protected:
        enum ValType {
            STR, STR_VEC, FILENAME, FILENAME_VEC, INT, BOOL, BOOL_W_ARG, DBL, CONFIG
        };
        struct Entry
        {
            const char* switch_str;
            std::string help_str;
            ValType val_type;
            std::string* str_ptr;
            std::vector<std::string>* strvec_ptr;
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
                strvec_ptr(nullptr),
                int_ptr(nullptr),
                bool_ptr(nullptr),
                double_ptr(nullptr),
                config_ptr(nullptr),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                ValType val_type_,
                std::vector<std::string>* strvec_ptr_,
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(val_type_),
                str_ptr(nullptr),
                strvec_ptr(strvec_ptr_),
                int_ptr(nullptr),
                bool_ptr(nullptr),
                double_ptr(nullptr),
                config_ptr(nullptr),
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
                str_ptr(nullptr),
                strvec_ptr(nullptr),
                int_ptr(int_ptr_),
                bool_ptr(nullptr),
                double_ptr(nullptr),
                config_ptr(nullptr),
                config_name(config_name_)
            {
            }

            Entry (
                const char* switch_str_,
                std::string help_str_,
                bool* bool_ptr_,
                bool takes_arg, 
                const char* config_name_
            ) :
                switch_str(switch_str_),
                help_str(help_str_),
                val_type(takes_arg  ? BOOL_W_ARG : BOOL),
                str_ptr(nullptr),
                strvec_ptr(nullptr),
                int_ptr(nullptr),
                bool_ptr(bool_ptr_),
                double_ptr(nullptr),
                config_ptr(nullptr),
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
                str_ptr(nullptr),
                strvec_ptr(nullptr),
                int_ptr(nullptr),
                bool_ptr(nullptr),
                double_ptr(double_ptr_),
                config_ptr(nullptr),
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
                str_ptr(nullptr),
                strvec_ptr(nullptr),
                int_ptr(nullptr),
                bool_ptr(nullptr),
                double_ptr(nullptr),
                config_ptr(config_ptr_),
                config_name(nullptr)
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

