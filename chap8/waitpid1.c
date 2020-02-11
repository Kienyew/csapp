#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#define N 5

char* ro = "READ_ONLY_SEGMENT";

int main() {
    int status;
    pid_t pid;
    for (int i = 0; i < N; ++i) {
        if ((pid = fork()) == 0) {
            *ro = '\0'; /* Intentionally write to .rodata */
            exit(100 + i);
        }
    }
   
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child terminated normally with exit_status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            char buffer[256];
            sprintf(buffer, "Child %d terminated by signal %d", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), buffer);
        }
    }

    return 0;
}
