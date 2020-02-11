#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TFSLEEP 5


sigjmp_buf tfgets_buf;

void handler(int sig) {
    assert(sig == SIGALRM);
    siglongjmp(tfgets_buf, 1);
}

char* tfgets(char* s, int size, FILE* stream) {
    if (sigsetjmp(tfgets_buf, 1) == 0) {
        /* orignal location */ 
        signal(SIGALRM, handler);
        alarm(TFSLEEP);
        return fgets(s, size, stream);
    } else {
        /* jump back location */
        return NULL;
    }
}

int main(int argc, char* argv[]) {
    char buffer[256];
    if (tfgets(buffer, 256, stdin) != NULL)
        printf("tfgets() read '%s'\n", buffer);
    else
        printf("tfgets() time out\n");

    return 0;
}

