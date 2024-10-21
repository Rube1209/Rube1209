#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 拼接两个字符串的函数
char* link(char A[], char B[]) {
    int m = strlen(A);
    int n = strlen(B);
    char *c = malloc(sizeof(char) * (m + n + 2));  // 额外空间用于存储空格和终止符
    if (c == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(c, A);
    strcat(c, " ");  // 添加空格
    strcat(c, B);
    return c;
}

int main() {
    char A[] = "hello";  // 使用字符串数组
    char B[] = "world";  // 使用字符串数组
    char *result = link(A, B);
    printf("%s\n", result);
    free(result);  // 释放内存
    return 0;
}
