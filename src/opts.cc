
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cctype>

#include <lime/opts.h>
#include "lime/config.h"
#include <lime/error.h>
#include <lime/debug.h>

/** Give acccess to a config file */

using namespace lime;
using namespace std;

Opts::Opts (
    std::string description,
    const char* build_date, const char* build_time
) :
    description_(description),
    switches_(),
    args_(),
    optional_args_(0),
    build_date_(build_date),
    build_time_(build_time),
    cmd_("<cmd>"),
    uses_config_(false)
{
}

bool
Opts::switch_exists (const char* switch_str)
{
    for (auto& sw : switches_) 
        if (strcmp (sw.switch_str, switch_str) == 0)
            return true;
    return false;
}

void
Opts::add_opt (
    const char* switch_str, std::string* str_ptr,
    std::string help_str,
    const char* config_name
)
{
    if (switch_exists (switch_str))
        limeCrash (
            "Config error: Switch already exists: " <<
            switch_str << ": " << help_str
        );
    switches_.push_back (
        Entry (switch_str, help_str, STR, str_ptr, config_name)
    );
}

void
Opts::add_opt_filename (
    const char* switch_str, std::string* str_ptr,
    std::string help_str,
    const char* config_name
)
{
    if (switch_exists (switch_str))
        limeCrash (
            "Config error: Switch already exists: " << 
            switch_str << ": " << help_str
        );
    switches_.push_back (
        Entry (switch_str, help_str, FILENAME, str_ptr, config_name)
    );
}

void
Opts::add_opt (
    const char* switch_str, int* int_ptr, std::string help_str,
    const char* config_name
)
{
    if (switch_exists (switch_str))
        limeCrash (
            "Config error: Switch already exists: " << 
            switch_str << ": " << help_str
        );
    switches_.push_back (Entry (switch_str, help_str, int_ptr, config_name));
}

void
Opts::add_opt (
    const char* switch_str, bool* bool_ptr, BoolArgType arg_type,
    std::string help_str,
    const char* config_name
)
{
    if (switch_exists (switch_str))
        limeCrash (
            "Config error: Switch already exists: " << 
            switch_str << ": " << help_str
        );
    if (arg_type == TAKES_ARG) 
        switches_.push_back (
            Entry (switch_str, help_str, bool_ptr, true, config_name)
        );
    else
        switches_.push_back (
            Entry (switch_str, help_str, bool_ptr, false, config_name)
        );
}

void
Opts::add_opt (
    const char* switch_str, double* double_ptr,
    std::string help_str,
    const char* config_name
)
{
    if (switch_exists (switch_str))
        limeCrash (
            "Config error: Switch already exists: " << 
            switch_str << ": " << help_str
        );
    switches_.push_back (Entry (switch_str, help_str, double_ptr, config_name));
}

void
Opts::add_opt (
    const char* switch_str, Config* config_ptr,
    std::string help_str
)
{
    if (switch_exists (switch_str))
        limeCrash ("Config error: Switch already exists: " << help_str);
    switches_.push_back (Entry (switch_str, help_str, config_ptr));
}

void
Opts::add_arg (
    const char* usage_str, std::string* str_ptr, std::string help_str,
    const char* config_name
)
{
    if (optional_args_ > 0)
        limeCrash (
            "Config error: Adding optional args after non-optional: " <<
            help_str
        );
    
    args_.push_back (Entry (usage_str, help_str, STR, str_ptr, config_name));
}

void
Opts::add_optional_arg (
    const char* usage_str, std::string* str_ptr, std::string help_str,
    const char* config_name
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, STR, str_ptr, config_name));
}

void
Opts::add_arg (
    const char* usage_str, int* int_ptr, std::string help_str,
    const char* config_name
)
{
    if (optional_args_ > 0)
        limeCrash (
            "Config error: Adding optional args after non-optional: " <<
            help_str
        );
    
    args_.push_back (Entry (usage_str, help_str, int_ptr, config_name));
}

void
Opts::add_optional_arg (
    const char* usage_str, int* int_ptr, std::string help_str,
    const char* config_name
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, int_ptr, config_name));
}

void
Opts::add_arg (
    const char* usage_str, double* double_ptr, std::string help_str,
    const char* config_name
)
{
    if (optional_args_ > 0)
        limeCrash (
            "Config error: Adding optional args after non-optional: " <<
            help_str
        );
    
    args_.push_back (Entry (usage_str, help_str, double_ptr, config_name));
}
            
void
Opts::add_optional_arg (
    const char* usage_str, double* double_ptr, std::string help_str,
    const char* config_name
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, double_ptr, config_name));
}

void
Opts::usage (
    const char* message1, const char* message2
)
{
    if (message1)
        cerr << message1;
    if (message2)
        cerr << " " << message2;
    if (message1 || message2)
        cerr << endl;
    cerr << "Usage: " << cmd_;
    for (auto& sw : switches_) {
        cerr << " [" << sw.switch_str;
        switch (sw.val_type) {
        case STR:
            cerr << " str]";
            break;
        case FILENAME:
        case CONFIG:
            cerr << " fn]";
            break;
        case INT:
        case DBL:
            cerr << " #]";
            break;
        case BOOL:
            cerr << "]";
            break;
        case BOOL_W_ARG:
            cerr << " t/f]";
            break;
        default:
            cerr << "Unknown val type: " << sw.val_type << endl;
        }
    }
    size_t first_optional = args_.size() - optional_args_;
    int arg_len = 0;
    for (size_t i = 0; i < args_.size(); i++) {
        auto& ar = args_[i];
        cerr << " ";
        if (i >= first_optional)
            cerr << "[";
        cerr << ar.switch_str;
        if (i >= first_optional)
            cerr << "]";
        if (strlen(ar.switch_str) > arg_len)
            arg_len = strlen(ar.switch_str);
    }
    cerr << endl;
    cerr << description_;
    cerr << endl << "  Switches: " << endl;
    for (auto& sw : switches_) {
        cerr << "    " << sw.switch_str << ": " << sw.help_str << " [";
        switch (sw.val_type) {
        case STR:
        case FILENAME:
            cerr << *sw.str_ptr;
            break;
        case INT:
            cerr << *sw.int_ptr;
            break;
        case DBL:
            cerr << *sw.double_ptr;
            break;
        case BOOL:
        case BOOL_W_ARG:
            cerr << (*sw.bool_ptr ? "true" : "false");
            break;
        case CONFIG:
            break;
        }
        cerr << "]";
        if (sw.config_name != NULL) 
            cerr << "  (config '" << sw.config_name << "')";
        cerr << endl;
    }
    cerr << "  Args: " << endl;
    for (size_t i = 0; i < args_.size(); i++) {
        auto& ar = args_[i];
        cerr << "    " << std::right << setw(arg_len) << ar.switch_str <<
            ": " << ar.help_str;
        if (i >= first_optional) {
            cerr << " [";
            switch (ar.val_type) {
            case STR:
            case FILENAME:
                cerr << *ar.str_ptr;
                break;
            case INT:
                cerr << *ar.int_ptr;
                break;
            case DBL:
                cerr << *ar.double_ptr;
                break;
            case BOOL:
            case BOOL_W_ARG:
                cerr << (*ar.bool_ptr ? "true" : "false");
                break;
            }
            cerr << "]";
        }
        if (ar.config_name != NULL) 
            cerr << "  (config '" << ar.config_name << "')";
        
        cerr << endl;
    }
    cerr << endl;
    if (uses_config_) {
        cerr << "Use <config-name>:<value> on cmd line to set config values" <<
            endl;
        cerr << "Use -- to toggle config name parsing" << endl;
        cerr << endl;
    }
    cerr << "This build: " << build_date_ << " " << build_time_ << endl;
    cerr << endl;
}
            
void
Opts::usage (string msg)
{
    usage (msg.c_str());
}

void
Opts::do_config_defaults (Config* config)
{
    if (config == NULL)
        return;
    // Do switches
    for (auto& sw : switches_)  {
        if (sw.config_name != NULL) {
            switch (sw.val_type) {
            case STR:
            case FILENAME:
                *(sw.str_ptr) =
                    config->getString (sw.config_name, *(sw.str_ptr));
                break;
            case INT:
                *(sw.int_ptr) =
                    config->getInt (sw.config_name, *(sw.int_ptr));
                break;
            case DBL:
                *(sw.double_ptr) =
                    config->getDouble (sw.config_name, *(sw.double_ptr));
                break;
            case BOOL:
            case BOOL_W_ARG:
                *(sw.bool_ptr) =
                    config->getBool (sw.config_name, *(sw.bool_ptr));
                break;
            }
        }
    }

    // Do args
    for (auto ar :args_) {
        if (ar.config_name != NULL) {
            switch (ar.val_type) {
            case STR:
            case FILENAME:
                *ar.str_ptr = 
                    config->getString (ar.config_name, *(ar.str_ptr));
                break;
            case INT:
                *ar.int_ptr = 
                    config->getInt (ar.config_name, *(ar.int_ptr));
                break;
            case DBL:
                *ar.double_ptr = 
                    config->getDouble (ar.config_name, *(ar.double_ptr));
                break;
            }
        }
    }
}
    
bool
Opts::process (int argc, const char* argv[], Config* config)
{
    cmd_ = argv[0];
    uses_config_ = (config != NULL);
    size_t upto_arg = 0;
    // Use "--" to switch off config parsing
    bool look_for_config = true;
    for (int upto = 1; upto < argc; upto++) {
        if (*argv[upto] == '-' && strlen(argv[upto]) > 1) {
            bool found = false;
            for (auto& sw : switches_)  {
                if (!strcmp (argv[upto], sw.switch_str)) {
                    found = true;
                    if (sw.val_type != BOOL && upto >= argc-1) {
                        usage ("No value for switch ", sw.switch_str);
                        return false;
                    }
                    switch (sw.val_type) {
                    case STR:
                    case FILENAME:
                        *(sw.str_ptr) = argv[++upto];
                        break;
                    case INT:
                        *sw.int_ptr = atoi (argv[++upto]);
                        break;
                    case DBL:
                        *sw.double_ptr = atof (argv[++upto]);
                        break;
                    case BOOL: 
                        // Set true if on of 0, t or T
                        *sw.bool_ptr = !(*sw.bool_ptr);
                        break;
                    case BOOL_W_ARG: {
                        auto val = argv[++upto];
                        // Set true if on of 0, t or T
                        *sw.bool_ptr = (strchr ("1tT", *val) != NULL);
                    }
                        break;
                    case CONFIG:
                        sw.config_ptr->read (argv[++upto]);
                        do_config_defaults (sw.config_ptr);
                        break;
                    }
                }
                if (sw.config_name != NULL && config != NULL) {
                    config->addItem (sw.config_name, argv[upto]);
                }
            }
            if (!found) {
                if (!strcmp (argv[upto], "--")) {
                    // Toggle looking for '='/':' (e.g in filenames)
                    look_for_config = !look_for_config;
                }
                else if (
                    !strcmp (argv[upto], "-?") ||
                    !strcmp (argv[upto], "-help") ||
                    !strcmp (argv[upto], "--help")
                ) {
                    usage ();
                    return false;
                }
                else {
                    usage ("Unrecognised option: ", argv[upto]);
                    return false;
                }
            }
        }
        else if (
            look_for_config &&
            (
                strchr (argv[upto], '=') != NULL ||
                strchr (argv[upto], ':') != NULL
            )
        ) {
            if (config != NULL) {
                config->addItem (string(argv[upto]));
                //  Parse the value now
                Config tmp;
                tmp.addItem (string(argv[upto]));
                do_config_defaults (&tmp);
            }
            else {
                usage ("No config items recognized: ", argv[upto]);
                return false;
            }
        }
        else if (upto_arg < args_.size()) {
            auto& ar = args_[upto_arg++];
            switch (ar.val_type) {
            case STR:
            case FILENAME:
                *ar.str_ptr = argv[upto];
                break;
            case INT:
                *ar.int_ptr = atoi (argv[upto]);
                break;
            case DBL:
                *ar.double_ptr = atof (argv[upto]);
                break;
            }
        }
        else {
            usage ("Too many args: ", argv[upto]);
            return false;
        }
    }

    // Set up config
    if (config != NULL) {
        for (auto& sw : switches_)  {
            if (sw.config_name !=  NULL) {
                switch (sw.val_type) {
                case STR:
                case FILENAME:
                    config->addItem (sw.config_name, *(sw.str_ptr));
                    break;
                case INT:
                    config->addItem (sw.config_name, *(sw.int_ptr));
                    break;
                case DBL:
                    config->addItem (sw.config_name, *(sw.double_ptr));
                    break;
                case BOOL:
                case BOOL_W_ARG:
                    config->addItem (sw.config_name, *(sw.bool_ptr));
                    break;
                }
            }
        }
    }
    // See if all required argshave values
    size_t reqd_args = args_.size() - optional_args_;
    bool missing = false;
    for (size_t k = 0; k < reqd_args; k++) {
        auto& ar = args_[k];
        switch (ar.val_type) {
        case STR:
        case FILENAME:
            if (ar.str_ptr->length() == 0)
                missing = true;
            break;
        case INT:
        case DBL:
            if (upto_arg <= k)
                missing = true;
            break;
        }
    }
    if (missing) {
        usage (to_string (reqd_args) + " args required");
        return false;
    }
    return true;    
}

