
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 拼接两个字符串的函数
char* link(const char* A, const char* B) {
    size_t m = strlen(A);
    size_t n = strlen(B);
    char *c = malloc(sizeof(char) * (m + n + 2));  // 额外空间用于空格和终止符
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
    char* composition = malloc(1);  // 初始化为空字符串
    if (composition == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    composition[0] = '\0';  // 确保字符串起始为空

    char input[500];  // 用于存储整行输入
    while (1) {
        printf("请输入句子（用逗号分隔，句号换行，输入 'exit' 结束）：");
        fgets(input, sizeof(input), stdin);  // 获取整行输入

        // 检查是否输入 'exit'
        if (strcmp(input, "exit\n") == 0) {
            break;  // 如果输入 "exit"，结束循环
        }

        // 使用逗号作为分隔符分割句子
        char* token = strtok(input, ",");
        while (token != NULL) {
            // 去掉前后的空格
            while (*token == ' ') token++;
            size_t len = strlen(token);
            while (len > 0 && (token[len - 1] == ' ' || token[len - 1] == '\n')) {
                token[--len] = '\0';
            }

            // 拼接句子
            char* temp = link(composition, token);
            free(composition);  // 释放之前的字符串内存
            composition = temp; // 更新为新拼接的字符串

            token = strtok(NULL, ",");  // 获取下一个句子
        }

        // 替换句号为换行
        char* period = strchr(composition, '.');
        while (period != NULL) {
            *period = '\n';  // 将句号替换为换行符
            period = strchr(period + 1, '.');  // 找到下一个句号
        }
    }

    printf("完整的句子是：\n%s\n", composition);
    free(composition);  // 释放最终的字符串内存

    return 0;
}
