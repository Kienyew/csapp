#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

extern char** environ;

int main(int argc, char* argv[], char* envp[]) {
    if (execve("/bin/ls", argv, environ) < 0) {
        fprintf(stderr, "Error while execve /bin/ls\n");
        exit(1);
    }

    return 0;
}
