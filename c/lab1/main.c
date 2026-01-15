#include <stdio.h>

/*
 * C Imperative Paradigm Lab
 * Parts 1–4 are implemented in this file.
 *
 * Do NOT change function signatures.
 */

/* ===== Part 2 ===== */
int sum_to(int n) {
    // TODO: implement using a for loop and mutable local state
    return 0;
}

/* ===== Part 3 ===== */
double avg_1_to_n(int n) {
    // TODO: call sum_to(n)
    // HINT: cast to double to avoid integer division
    return 0.0;
}

/* ===== Part 4 ===== */
void increment_bad(int x) {
    x++;
}

void increment(int *x) {
    // TODO: fix using a pointer
}

int main() {

    /* ===== Part 1 ===== */
    printf("--- Part 1: State and Sequence ---\n");

    int x = 2;
    x = x + 3;
    x = x * 4;
    printf("x=%d\n", x);

    // TODO: swap the last two assignments above and re-run


    /* ===== Part 2 ===== */
    printf("\n--- Part 2: Control Flow ---\n");
    printf("sum_to(5) = %d (expected 15)\n", sum_to(5));
    printf("sum_to(1) = %d (expected 1)\n", sum_to(1));


    /* ===== Part 3 ===== */
    printf("\n--- Part 3: Functions as Procedures ---\n");
    printf("avg_1_to_n(5) = %.1f (expected 3.0)\n", avg_1_to_n(5));


    /* ===== Part 4 ===== */
    printf("\n--- Part 4: Pass-by-Value vs Pointers ---\n");

    int a = 5;
    increment_bad(a);
    printf("after increment_bad: a=%d (expected 5)\n", a);

    increment(&a);
    printf("after increment:     a=%d (expected 6)\n", a);

    return 0;
}
