#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdbool.h>

sigjmp_buf buf;
void handler(int sig) {
   siglongjmp(buf, 0); 
}

int main() {
    signal(SIGINT, handler);
    if (sigsetjmp(buf, 1) == 0) {
        printf("Staring\n");
    } else {
        printf("Restarting...\n");
    } 
    while (true) {
        printf("main loop...\n");
        usleep(500000);
    }
    return 0;
}
