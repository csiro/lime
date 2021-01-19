#include <string>
#include <iostream>
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
    build_time_(build_time)
{
}

void
Opts::add_opt (
    const char* switch_str, std::string* str_ptr,
    const char* help_str
)
{
    switches_.push_back (Entry (switch_str, help_str, STR, str_ptr));
}

void
Opts::add_opt_filename (
    const char* switch_str, std::string* str_ptr,
    const char* help_str
)
{
    switches_.push_back (Entry (switch_str, help_str, FILENAME, str_ptr));
}

void
Opts::add_opt (const char* switch_str, int* int_ptr, const char* help_str)
{
    switches_.push_back (Entry (switch_str, help_str, int_ptr));
}

void
Opts::add_opt (
    const char* switch_str, bool* bool_ptr,
    const char* help_str
)
{
    switches_.push_back (Entry (switch_str, help_str, bool_ptr));
}

void
Opts::add_opt (
    const char* switch_str, double* double_ptr,
    const char* help_str
)
{
    switches_.push_back (Entry (switch_str, help_str, double_ptr));
}

void
Opts::add_opt (
    const char* switch_str, Config* config_ptr,
    const char* help_str
)
{
    switches_.push_back (Entry (switch_str, help_str, config_ptr));
}

void
Opts::add_arg (
    const char* usage_str, std::string* str_ptr, const char* help_str
)
{
    if (optional_args_ > 0)
        limeCrash ("Adding optional args after non-optional: " << help_str);
    
    args_.push_back (Entry (usage_str, help_str, STR, str_ptr));
}

void
Opts::add_optional_arg (
    const char* usage_str, std::string* str_ptr, const char* help_str
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, STR, str_ptr));
}

void
Opts::add_arg (
    const char* usage_str, int* int_ptr, const char* help_str
)
{
    if (optional_args_ > 0)
        limeCrash ("Adding optional args after non-optional: " << help_str);
    
    args_.push_back (Entry (usage_str, help_str, int_ptr));
}

void
Opts::add_optional_arg (
    const char* usage_str, int* int_ptr, const char* help_str
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, int_ptr));
}

void
Opts::add_arg (
    const char* usage_str, double* double_ptr, const char* help_str
)
{
    if (optional_args_ > 0)
        limeCrash ("Adding optional args after non-optional: " << help_str);
    
    args_.push_back (Entry (usage_str, help_str, double_ptr));
}
            
void
Opts::add_optional_arg (
    const char* usage_str, double* double_ptr, const char* help_str
)
{
    optional_args_++;
    args_.push_back (Entry (usage_str, help_str, double_ptr));
}

void
Opts::usage (
    const char* cmd, const char* message1, const char* message2
)
{
    if (message1)
        cerr << message1;
    if (message2)
        cerr << " " << message2;
    if (message1 || message2)
        cerr << endl;
    cerr << "Usage: " << cmd;
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
        default:
            cerr << "Unknown val type: " << sw.val_type << endl;
        }
    }
    size_t first_optional = args_.size() - optional_args_;
    for (size_t i = 0; i < args_.size(); i++) {
        auto& ar = args_[i];
        cerr << " ";
        if (i >= first_optional)
            cerr << "[";
        cerr << ar.switch_str;
        if (i >= first_optional)
            cerr << "]";
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
            cerr << *sw.bool_ptr;
            break;
        case CONFIG:
            break;
        }
        cerr << "]" << endl;
    }
    cerr << "  Args: " << endl;
    for (size_t i = 0; i < args_.size(); i++) {
        auto& ar = args_[i];
        cerr << "    " << ar.switch_str << ": " << ar.help_str;
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
                cerr << *ar.bool_ptr;
                break;
            }
            cerr << "]";
        }
        cerr << endl;
    }
    cerr << endl;
    cerr << "This build: " << build_date_ << " " << build_time_ << endl;
    cerr << endl;
}
            
bool
Opts::process (int argc, const char* argv[], Config* config)
{
    size_t upto_arg = 0;
    for (int upto = 1; upto < argc; upto++) {
        if (*argv[upto] == '-') {
            bool found = false;
            for (auto& sw : switches_)  {
                if (!strcmp (argv[upto], sw.switch_str)) {
                    found = true;
                    if (sw.val_type != BOOL && upto >= argc-1) {
                        usage (argv[0], "No value for switch ", sw.switch_str);
                        return false;
                    }
                    switch (sw.val_type) {
                    case STR:
                    case FILENAME:
                        *sw.str_ptr = argv[++upto];
                        break;
                    case INT:
                        *sw.int_ptr = atoi (argv[++upto]);
                        break;
                    case DBL:
                        *sw.double_ptr = atof (argv[++upto]);
                        break;
                    case BOOL:
                        *sw.bool_ptr = !*sw.bool_ptr;
                        break;
                    case CONFIG:
                        sw.config_ptr->read (argv[++upto]);
                        break;
                    }
                }
            }
            if (!found) {
                if (
                    !strcmp (argv[upto], "-?") ||
                    !strcmp (argv[upto], "-help") ||
                    !strcmp (argv[upto], "--help")
                ) {
                    usage (argv[0]);
                    return false;
                }
                usage (argv[0], "Unrecognised option: ", argv[upto]);
                return false;
            }
        }
        else if (
            strchr (argv[upto], '=') != NULL ||
            strchr (argv[upto], ':') != NULL
        ) {
            if (config != NULL)
                config->addItem (string(argv[upto]));
            else {
                usage (argv[0], "No config items recognized: ", argv[upto]);
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
            usage (argv[0], "Too many args: ", argv[upto]);
            return false;
        }
    }
    size_t reqd_args = args_.size() - optional_args_;
    if (upto_arg < reqd_args) {
        string msg = to_string (reqd_args) + " args required";
        usage (argv[0], msg.c_str());
        return false;
    }

    return true;    
}

