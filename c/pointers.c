#include <stdio.h>
#include <windows.h>
#include <string.h>

int global = 3;

void process(int* s) {
    int len = strlen(s);
    printf("%d\n", *s);
    *s = 0;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8); 

    char* name = "Brian Toone";
    *(name+7) = 0xF0;
    name[8] = 0x9F;
    name[9] = 0x98;
    *(name+10) = 0x88;
    printf("The memory address of name is: %p\n", name);
    printf("The value stored in name is: %s\n", name);
    
    int i=1;
    int j=2;
    double d = 3.9;
    printf("%d\n", (int) d);
    process(&i);
    process(&j);
    printf("%d %d\n", i, j);

    char a = 'A';
    unsigned char b = 66;
    unsigned char c = 0.25f;
    printf("%d %d %d\n", a, b, c);
    return 0;
}