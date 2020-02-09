#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define N 10

int main(int argc, char * argv[]) {
    int status;
    pid_t pid;
    for (int i = 0; i < N; ++i)
        if ((pid = fork()) == 0) {
            printf("child sleeping for 3 seconds...\n");
            sleep(3);
            exit(100 + i);
        }

    while ((pid = waitpid(-1, & status, 0)) > 0) {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        else
            printf("child %d terminated abnormally\n", pid);
    }

    if (errno != ECHILD) {
        fprintf(stderr, "waitpid error\n");
    }
    return 0;
}
