#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int mysystem(const char* command) {
    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        int ret;
        if ((ret = execl("/bin/sh", "/bin/sh", "-c", command, NULL)) < 0) {
            fprintf(stderr, "execve() error; errno=%d\n", errno);
            exit(-1);
        }
        exit(ret);
    }

    if (waitpid(pid, &status, 0) != pid) {
        fprintf(stderr, "waitpid() error; errno=%d\n", errno);
    }

    return WEXITSTATUS(status);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s COMMAND\n", argv[0]);
        exit(1);
    }

    // printf("executing `/bin/sh -c '%s'`...\n", argv[1]);
    int ret = mysystem(argv[1]);
    // printf("mysystem(%s) returned %d\n", argv[1], ret);
    return ret;
}