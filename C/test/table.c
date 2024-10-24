#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int f() {
    return rand() % 5; // 随机生成 0 到 4 之间的整数
}

const char* f1(int i) {
    switch(i) {
        case 0: return "Raining";
        case 1: return "Sunny";
        case 2: return "Cloudy";
        case 3: return "Windy";
        case 4: return "Snowy";
        default: return "Unknown weather"; // 处理无效输入
    }
}

const char* date(int i) {
    switch(i) {
        case 0: return "Monday";
        case 1: return "Tuesday";
        case 2: return "Wednesday";
        case 3: return "Thursday";
        case 4: return "Friday";
        case 5: return "Saturday";
        case 6: return "Sunday";
        default: return "Invalid day"; // 处理无效输入
    }
}

int main() {
    srand(time(NULL)); // 初始化随机数生成器

    // 打印表头
    printf("+----------------------+-----------+\n");
    printf("| Date                 | Weather   |\n");
    printf("+----------------------+-----------+\n");

    // 打印一周的天气
    for (int i = 0; i < 7; i++) {
        printf("| %-20s | %-9s |\n", date(i), f1(f())); // 使用随机天气
    }

    // 打印表尾
    printf("+----------------------+-----------+\n");

    return 0;
}
