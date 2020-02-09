#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
    printf("Command line arguments:\n");
    for (int i = 0; i < argc; ++i)
        printf("\targv[%d]: %s\n", i, argv[i]); 

    printf("\n");

    printf("Environment variables:\n");
    for (char** e = &envp[0]; *e != NULL; ++e)
        printf("\tenvp[%d]: %s\n", e - &envp[0], *e);
    return 0;
}
