#include "helper.h"
#include "scope.h"
#include <stdio.h>

int Helper::method1() {
    return 5;
}

void Helper::method2(int param1, int param2) {
    printf("%d %d\n", foo(param1), foo(param2));
}