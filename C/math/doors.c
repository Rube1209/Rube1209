
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 模拟更改门后的结果
int simulateChange(int N) {
    int winCount = 0;
    for (int i = 0; i < N; i++) {
        int carDoor = rand() % 3;  // 汽车在三扇门的随机位置
        int playerChoice = rand() % 3; // 玩家随机选择一扇门
        int openedGoatDoor;
        
        // 主持人打开一扇有山羊的门
        do {
            openedGoatDoor = rand() % 3;
        } while (openedGoatDoor == carDoor || openedGoatDoor == playerChoice);
        
        // 玩家选择更改门后的结果
        int changedChoice;
        do {
            changedChoice = rand() % 3;
        } while (changedChoice == playerChoice || changedChoice == openedGoatDoor);
        
        // 检查玩家是否赢得汽车
        if (changedChoice == carDoor) {
            winCount++;
        }
    }
    return winCount;
}

// 模拟不更改门后的结果
int simulateNoChange(int N) {
    int winCount = 0;
    for (int i = 0; i < N; i++) {
        int carDoor = rand() % 3;  // 汽车在三扇门的随机位置
        int playerChoice = rand() % 3; // 玩家随机选择一扇门

        // 不更改选择，直接检查是否赢得汽车
        if (playerChoice == carDoor) {
            winCount++;
        }
    }
    return winCount;
}

int main() {
    srand(time(NULL));  // 初始化随机数种子
    int N = 10000;  // 设置模拟次数

    // 模拟更改门的情况
    int winsWithChange = simulateChange(N);
    // 模拟不更改门的情况
    int winsWithoutChange = simulateNoChange(N);

    // 计算概率
    double probWithChange = (double)winsWithChange / N;
    double probWithoutChange = (double)winsWithoutChange / N;

    // 输出结果
    printf("After %d simulations:\n", N);
    printf("Winning probability with changing the door: %lf\n", probWithChange);
    printf("Winning probability without changing the door: %lf\n", probWithoutChange);

    return 0;
}
