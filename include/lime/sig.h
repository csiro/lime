
#include <execinfo.h>
#include <signal.h>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>


namespace lime
{
    void print_stack_trace()
    {
        void* buffer[256];
        int nptrs = backtrace(buffer, sizeof(buffer) / sizeof(buffer[0]));
        char** strings = backtrace_symbols(buffer, nptrs);
        if (strings != NULL) {
            for (int i = 0; i < nptrs; i++) {
                printf("%s\n", strings[i]);
            }
            free(strings);
        }
        else {
            perror("backtrace_symbols");
        }
    }

    void sig_handler (int sig_num) {
        std::cout << "Interrupt signal (" << sig_num << ") received.\n";
        
        print_stack_trace();
        
        std::exit(sig_num);
    }
    
    
    void install_sighandler()
    {
        std::signal(SIGINT, sig_handler);
    }
}
