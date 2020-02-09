#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

void handler(int sig) {
    pid_t pid;
    printf("Inside Handler\n");
    while ((pid = waitpid(-1, NULL, 0)) > 0) {
        printf("Handler reaped child %d\n", (int)pid);
    }
    sleep(2);
    return;
}

int main() {
    signal(SIGCHLD, handler);
    for (int i = 0; i < 3; ++i) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            printf("Hello from child %d\n", (int)getpid());
            sleep(i);
            return 0;
        }
    }

    while (true) {
        printf("Parent continuing execution\n");
    }
}
