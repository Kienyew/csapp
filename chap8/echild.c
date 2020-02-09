#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    waitpid(-1, NULL, 0);
    if (errno == ECHILD) {
        printf("Normal, no child left\n");
    }
    return 0;
}
