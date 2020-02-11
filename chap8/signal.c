#include <signal.h>
#include <stdio.h>
#include <stdbool.h>

void handler(int sig) {
    printf("SIGGGGGGGGGGG\n");
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handler);
    while(true) { }
    return 0;
}
