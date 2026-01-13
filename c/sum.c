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

