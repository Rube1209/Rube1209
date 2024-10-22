#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void f(int n) {
    double r1 = (1 + sqrt(5)) / 2;
    double r2 = (1 - sqrt(5)) / 2;
    double *a = (double *)malloc(n * sizeof(double));

    if (a == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        a[i] = (pow(r1, i + 1) - pow(r2, i + 1)) / sqrt(5);
        printf("a[%d] = %f\n", i + 1, a[i]);
    }

    free(a);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    f(n);
    return 0;
}
