#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void pass() { }

unsigned int snooze(unsigned int secs) {
    unsigned int secleft = sleep(secs);
    printf("Slept for %lu for %lu seconds\n", secs - secleft, secs);
    return secleft;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, pass);
    if (argc != 2) {
        fprintf(stderr, "Usage: %s SECONDS\n", argv[0]);
        exit(1);
    } else {
        snooze(atoi(argv[1]));
    }
    return 0;
}
