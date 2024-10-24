#include <stdio.h>

#include <math.h>

// 定义函数 y(x)
double y(double x) {
    return sqrt(1 - x * x);
}

// 定义辛普森公式模块
double L(double a, double b) {
    double c = (a + b) / 2;
    return (b - a) * (y(a) + 4 * y(c) + y(b)) / 6;
}

// 定义积分模块
double integral(double a, double b) {
    double sum = 0;
    int N = 10000000;
    double dx = (b - a) / N;

    // 计算积分
    for (int i = 0; i < N; i++) {
        double x0 = a + i * dx;
        double x1 = a + (i + 1) * dx;
        sum += L(x0, x1);
    }

    return sum;
}

int main() {
    double result = integral(0, 1); // 示例区间
    printf("Integral result = %.15f\n", 4*result);
    return 0;
}
