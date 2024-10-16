#include <stdio.h>

// 语言真假情况
void truth(int r, int *result) {
    switch (r) {
        case 0: result[0] = 1; result[1] = 1; break;  // 天使
        case 1: result[0] = 0; result[1] = 0; break;  // 魔鬼
        case 2: result[0] = 0; result[1] = 1; break;  // 村民 (假，真)
        case 3: result[0] = 1; result[1] = 0; break;  // 村民 (真，假)
    }
}

// 逻辑运算函数
int logic(int a, int b, char op) {
    if (op == '|') return a || b;
    if (op == '&') return a && b;
    if (op == '!') return !a;
    return -1; // 错误操作
}

// 角色打印函数
void printRole(int r) {
    switch (r) {
        case 0: printf("天使\n"); break;
        case 1: printf("魔鬼\n"); break;
        case 2: printf("村民\n"); break;
    }
}

int main() {
    int roles[3] = {0, 1, 2}; // 假设角色依次为A, B, C
    int result[2];
    int valid_combinations = 0;

    // 遍历所有角色组合，搜索可能的匹配
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) continue; // 避免同一个人
            for (int k = 0; k < 3; k++) {
                if (i == k || j == k) continue; // 避免同一个人

                // 假设 roles[i] 是天使，roles[j] 是魔鬼，roles[k] 是村民
                // A说：我是村民。C是魔鬼。
                truth(roles[2], result);
                int a1 = (roles[i] == 2) ? 1 : 0; // 我是村民
                int a2 = result[0]; // C是魔鬼

                // B说：我是天使。A是魔鬼。
                truth(roles[i], result);
                int b1 = (roles[j] == 0) ? 1 : 0; // 我是天使
                int b2 = result[0]; // A是魔鬼

                // C说：B是村民。A是天使。
                truth(roles[j], result);
                int c1 = (roles[k] == 2) ? 1 : 0; // B是村民
                int c2 = (roles[i] == 0) ? 1 : 0; // A是天使

                // 检查逻辑运算是否满足条件
                if (logic(a1, a2, '&') && logic(b1, b2, '&') && logic(c1, c2, '&')) {
                    printf("有效组合：A: ");
                    printRole(roles[i]);
                    printf("B: ");
                    printRole(roles[j]);
                    printf("C: ");
                    printRole(roles[k]);
                    valid_combinations++;
                }
            }
        }
    }

    if (valid_combinations == 0) {
        printf("没有找到有效的组合。\n");
    }

    return 0;
}

