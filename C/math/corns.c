#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int corn() {
    int r1, r2;
    int n = 0, N = 0;
    do {
        N++;
        r1 = rand() % 2;
        r2 = rand() % 2;
        if (r1 == 0 && r2 == 0 && n < 3) {
            n++;
        } else {
            n = 0;
        }
    } while (n < 3);
    return N;
}

double average(int n) {
    int sum = 0;
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        a[i] = corn();
        sum += a[i];
    }
    free(a);
    return (double)sum / n;
}

int main() {
    srand(time(NULL));
    int n = 100;
    printf("%lf\n", average(n));
    return 0;
}
