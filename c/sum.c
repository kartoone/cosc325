/*
  From VS Code terminal:
    git fetch upstream
    git pull upstream/main
    
  If you get any errors you may also need to do:
    git merge upstream/main
*/

#include <stdio.h>

int sum(int n) {
    int i;
    int total = 0;
    printf("mem address of i in sum: %p\n", &i);
    printf("value of i before loop: %d\n", i);
    for (i=1; i<=n; i++) {
        total += i;
    }
    printf("value of i after loop: %d\n", i);

    return total;
}

long foo() {
    int a;
    a = 5;
    printf("sum from foo: %d\n", sum(a));\
    return 7;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("sum from main: %d\n", sum(n));    
    foo();
}

