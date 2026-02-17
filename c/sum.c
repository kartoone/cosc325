/*
  From VS Code terminal:
    git fetch upstream
    git pull upstream/main
    
  If you get any errors you may also need to do:
    git merge upstream/main
*/

#include <stdio.h>
#include <stdlib.h>

int globalcount = 0;

int mymax(int length, int numbers[]) {
    static int count = 0;
    count = count + 1;
    globalcount++;
    int themax = numbers[0];
    for (int i = 0; i<length; i++) {
        if (numbers[i]>themax) {
            themax = numbers[i];
        }
    }
    printf("you have called mymax %d time(s) ... it's memory address is still %p\n", count, &count);
    return themax;
}

int max_r(int length, int numbers[]) {
    globalcount++;
    if (length==1) {
        return numbers[0];
    }
    int themax = numbers[0];
    int tailmax = max_r(length-1,&numbers[1]);
    if (themax < tailmax)
        themax = tailmax;
    return themax;
}

int factorial(int n) {
    static int result = 1;
    if (n>1) {
        result = n * factorial(n-1);
    }
    return result;
}

int sum(int n) {
    int i;
    printf("mem address of i in sum: %p\n", &i);
    int total = 0;
    printf("mem address of total in sum: %p\n", &total);
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
    return a;
}

int main(int argc, char* argv[]) {
    int n;
    scanf("%d", &n);
    printf("factorial(%d)=%d\n", n, factorial(n));    
    // java equivalent: int numbers[] = new int[10];
    int* numbers = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        numbers[i] = i; // shortcut array access notation
        *(numbers+i*sizeof(int)) = i; // the long way via pointer arithmetic
    }
    printf("numbers is stored on the stack (probably right next to n) let's find out\n");
    printf("address of n = %p\n", &n);
    printf("stack address of numbers = %p\n", &numbers);
    printf("heap address of numbers = %p\n", numbers);
    printf("here are all the numbers:\n");
    for (int i=0; i<n; i++) {
        printf("numbers[%d]=%d\n",i,numbers[i]);
    }
    printf("and your max is:\n");
    printf("  via a loop: %d\n", mymax(n, numbers));
    printf("  via a loop: %d\n", mymax(n, numbers));
    printf("  via a loop: %d\n", max_r(n, numbers));
    printf(" this is how many times mymax and max_r got called: %d courtesy of globalcount located here %p\n", globalcount, &globalcount);

    foo();
}

