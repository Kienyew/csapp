#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal %d received\n", sig);
}


int main() {
    signal(SIGTERM, handler);
    // sigset_t set;
    // sigaddset(&set, SIGTERM);
    // sigprocmask(SIG_BLOCK, &set, NULL);
    sleep(10); 
    return 0;
}
