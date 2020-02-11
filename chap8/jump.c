#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf buf;
int error1 = 0;
int error2 = 1;

void foo();
void bar();

int main() {
    int ret_code;
    ret_code = setjmp(buf);
    printf("The line after setjmp(buf) with return code %d\n", ret_code); 
    if (ret_code == 0)
        foo();
    else if (ret_code == 1)
        printf("Detected an error1 condition in foo\n");
    else if (ret_code == 2)
        printf("Detected an error2 condition in foo\n");
    else 
        exit(255);
    
    return 0;
}


void foo() {
    if (error1)
        longjmp(buf, 1);

    bar();
}

void bar() {
    if (error2)
        longjmp(buf, 2);
}
