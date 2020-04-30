#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




long int getsize(FILE* file) {
    fpos_t pos;
    fgetpos(file, &pos);
    fseek(file, 0, SEEK_END);
    long int end = ftell(file);
    fsetpos(file, &pos);
    return end;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "not enough arguments\n");
        fprintf(stderr, "Usage: %s PATH\n", argv[0]);
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");
    int fd = fileno(file);
    long int filesize = getsize(file);

    // void* mmap(void* start, size_t length, int prot, int flags, int fd, off_t offset);
    void* bufp = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    void* memp = mmap(NULL, filesize, PROT_WRITE, MAP_SHARED, fileno(stdout), 0);
    memcpy(memp, bufp, filesize);
    
}

