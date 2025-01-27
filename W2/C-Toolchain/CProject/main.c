#include <stdio.h>

signed int add(const signed int a, const signed int b) {
    return a + b;
}

signed int subtract(const signed int a, const signed int b) {
    return a - b;
}

signed int multiply(const signed int a, const signed int b) {
    return a * b;
}

#define ZERO 0

int main() {
    signed int a, b;

    printf("Kies 2 getallen: ");
    scanf("%d", &a);
    scanf("%d", &b);

    const signed int additionResult = add(a, b);
    const signed int multiplicationResult = multiply(a, b);
    const signed int subtractionResult = subtract(additionResult, multiplicationResult);
    printf("Difference of addition and multiplication: %d\n", subtractionResult);
    return ZERO;
}
