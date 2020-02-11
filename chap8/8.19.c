#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(2);
    } else {
        n = atoi(argv[1]);
    }
    for (int i = 0; i < n; ++i)
        fork();

    printf("Hello\n");
    return 0;
}
