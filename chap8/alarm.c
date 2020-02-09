#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void handler(int sig) {
    static int beeps = 0;
    printf("Beep\n");
    if (++beeps < 5) {
        alarm(1);
    } else {
        printf("Boom!\n");
        exit(0);
    }
}

int main() {
    alarm(5);
    alarm(1);
    signal(SIGALRM, handler);
    while (true) {}
    return 0;
}

