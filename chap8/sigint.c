#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void interrupt_handler(int sig) {
    printf("interrupt_handler received SIGNAL: %d\n", sig);
}

int main() {
    signal(SIGINT, interrupt_handler);
    sleep(3);
    sleep(4);
    return 0;
}
