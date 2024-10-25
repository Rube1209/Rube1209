#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// 三点样条插值类
class CubicSpline {
public:
    struct SplineTuple {
        double a, b, c, d, x;
    };

    CubicSpline(const vector<double>& xs, const vector<double>& ys)
        : x(xs), y(ys), n(xs.size()), splines(n) {
        calculateSpline();
    }

    void calculateSpline() {
        vector<double> h(n - 1), alpha(n - 1), l(n), mu(n), z(n);
        vector<double> c(n), b(n), d(n);

        for (int i = 0; i < n - 1; i++) {
            h[i] = x[i + 1] - x[i];
            if (i > 0) {
                alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
            }
        }

        l[0] = 1.0; mu[0] = z[0] = 0.0;

        for (int i = 1; i < n - 1; i++) {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[n - 1] = 1; z[n - 1] = 0; c[n - 1] = 0;

        for (int j = n - 2; j >= 0; j--) {
            c[j] = z[j] - mu[j] * c[j + 1];
            b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
            d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        }

        for (int i = 0; i < n - 1; i++) {
            SplineTuple& spline = splines[i];
            spline.a = y[i];
            spline.b = b[i];
            spline.c = c[i];
            spline.d = d[i];
            spline.x = x[i];
        }
    }

    double eval(double xVal) const { // 加上 const
        if (xVal < x[0] || xVal > x[n - 1]) {
            cerr << "值超出插值范围。" << endl;
            return NAN; // 处理越界
        }

        int idx = 0;
        while (idx < n - 1 && xVal > x[idx + 1]) {
            idx++;
        }

        const SplineTuple& s = splines[idx]; // 使用 const 引用
        double diff = xVal - s.x; // 修正变量名
        return s.a + s.b * diff + s.c * pow(diff, 2) + s.d * pow(diff, 3); // 修正变量名
    }

private:
    int n;
    vector<double> x, y;
    vector<SplineTuple> splines;
};

// 预定义函数
double f(double x) {
    return sin(x); // 示例函数
}

// 使用三次样条插值的积分类
class Integral {
public:
    Integral(double (*func)(double), double a, double b, int n)
        : f(func), a(a), b(b), numIntervals(n) {}

    double compute() {
        vector<double> xValues(numIntervals + 1), yValues(numIntervals + 1);
        double h = (b - a) / numIntervals;

        for (int i = 0; i <= numIntervals; i++) {
            xValues[i] = a + i * h;
            yValues[i] = f(xValues[i]);
        }

        CubicSpline spline(xValues, yValues);
        double integrationValue = 0.0;

        for (int i = 0; i < numIntervals; i++) {
            double x0 = xValues[i];
            double x1 = xValues[i + 1];
            integrationValue += integrationSpline(spline, x0, x1);
        }

        return integrationValue;
    }

private:
    double (*f)(double); // 函数指针
    double a, b; // 积分限制
    int numIntervals; // 区间数

    double integrationSpline(const CubicSpline& spline, double x0, double x1) {
        double total = 0.0;
        const int subIntervals = 10;
        double h = (x1 - x0) / subIntervals;

        for (int i = 0; i < subIntervals; i++) {
            double xi = x0 + i * h;
            double xip1 = xi + h;
            double mi = spline.eval(xi);
            double mip1 = spline.eval(xip1);
            total += (mi + mip1) * h / 2.0; // 修正变量名
        }
        return total; // 修正返回值
    }
};

int main() {
    double a, b;
    int numIntervals;
    cout << "输入下限(a)：";
    cin >> a;
    cout << "输入上限(b)：";
    cin >> b;
    cout << "请输入间隔数：";
    cin >> numIntervals;

    Integral integral(f, a, b, numIntervals); // 修正调用
    double result = integral.compute();
    cout << "积分结果为：" << fixed << setprecision(16) << result << endl;

    return 0;
}
