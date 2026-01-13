#include <stdio.h>

int sum(int n) {
    int i;
    int total = 0;
    for (i=1; i<=n; i++) {
        total += i;
    }
    return total;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", sum(n));    
}

