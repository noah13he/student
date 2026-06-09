#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "search.h"
#include "sort.h"

// 函数声明
void printMenu();
void inputStudentInfo(StudentTable *table);
int getIntInput();
float getFloatInput();
void getStringInput(char *buffer, int size);

// 主菜单
void printMenu() {
    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║    学生信息管理系统            ║\n");
    printf("╚════════════════════════════════╝\n");
    printf("  1. 录入学生信息\n");
    printf("  2. 显示所有学生信息\n");
    printf("  3. 按学号查找（顺序查找）\n");
    printf("  4. 按学号查找（二分查找）\n");
    printf("  5. 按姓名查找（顺序查找）\n");
    printf("  6. 按学号升序排序（冒泡排序）\n");
    printf("  7. 按成绩降序排序（冒泡排序）\n");
    printf("  8. 按学号升序排序（快速排序）\n");
    printf("  9. 按成绩降序排序（快速排序）\n");
    printf("  10. 运行完整测试\n");
    printf("  0. 退出系统\n");
    printf("────────────────────────────────\n");
    printf("请选择操作 (0-10): ");
}

// 录入学生信息交互
void inputStudentInfo(StudentTable *table) {
    if (table == NULL) {
        return;
    }

    printf("\n========== 录入学生信息 ==========\n");
    
    int id;
    char name[50];
    float score;

    printf("请输入学号: ");
    id = getIntInput();

    printf("请输入姓名: ");
    getStringInput(name, sizeof(name));

    printf("请输入成绩 (0-100): ");
    score = getFloatInput();

    addStudent(table, id, name, score);
    printf("====================================\n\n");
}

// 获取整数输入
int getIntInput() {
    int num;
    char buffer[100];
    
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &num) == 1) {
            return num;
        }
        printf("输入错误，请输入有效的整数: ");
    }
}

// 获取浮点数输入
float getFloatInput() {
    float num;
    char buffer[100];
    
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &num) == 1) {
            return num;
        }
        printf("输入错误，请输入有效的浮点数: ");
    }
}

// 获取字符串输入
void getStringInput(char *buffer, int size) {
    fgets(buffer, size, stdin);
    // 移除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

// 测试函数
void runTests(StudentTable *table) {
    printf("\n");
    printf("╔════════════════════════════════╗\n");
    printf("║        运行完整测试            ║\n");
    printf("╚════════════════════════════════╝\n\n");

    // 清空现有数据
    clearTable(table);

    // 测试数据集1：基础测试
    printf("【测试集1 - 基础数据】\n");
    addStudent(table, 1001, "Alice", 85.5);
    addStudent(table, 1003, "Charlie", 92.0);
    addStudent(table, 1002, "Bob", 88.5);
    addStudent(table, 1005, "Eve", 78.0);
    addStudent(table, 1004, "David", 95.5);

    displayAll(table);

    // 测试查找功能
    printf("\n【查找功能测试】\n");
    printf("--- 顺序查找 ---\n");
    SearchResult result1 = sequentialSearchByID(table, 1002);
    displaySearchResult(&result1, table, "按学号顺序查找", 1002, NULL);

    printf("--- 二分查找（需先按学号排序）---\n");
    StudentTable sortedTable;
    initTable(&sortedTable);
    copyTable(table, &sortedTable);
    bubbleSortByID(&sortedTable);
    
    SearchResult result2 = binarySearchByID(&sortedTable, 1002);
    displaySearchResult(&result2, &sortedTable, "按学号二分查找", 1002, NULL);

    printf("--- 顺序查找按姓名 ---\n");
    SearchResult result3 = sequentialSearchByName(table, "Bob");
    displaySearchResult(&result3, table, "按姓名顺序查找", 0, "Bob");

    // 测试排序功能
    printf("\n【排序功能测试】\n");

    // 复制原表用于排序测试
    StudentTable testTable;
    initTable(&testTable);
    copyTable(table, &testTable);

    printf("--- 冒泡排序：按学号升序 ---\n");
    SortStats bubbleIDStats = bubbleSortByID(&testTable);
    displaySortResult(&testTable, "冒泡排序 - 学号升序", &bubbleIDStats);

    // 恢复原表
    copyTable(table, &testTable);

    printf("--- 冒泡排序：按成绩降序 ---\n");
    SortStats bubbleScoreStats = bubbleSortByScore(&testTable);
    displaySortResult(&testTable, "冒泡排序 - 成绩降序", &bubbleScoreStats);

    // 恢复原表
    copyTable(table, &testTable);

    printf("--- 快速排序：按学号升序 ---\n");
    SortStats quickIDStats = quickSortByID(&testTable);
    displaySortResult(&testTable, "快速排序 - 学号升序", &quickIDStats);

    // 恢复原表
    copyTable(table, &testTable);

    printf("--- 快速排序：按成绩降序 ---\n");
    SortStats quickScoreStats = quickSortByScore(&testTable);
    displaySortResult(&testTable, "快速排序 - 成绩降序", &quickScoreStats);

    printf("\n【排序算法比较】\n");
    printf("排序类型              | 比较次数 | 交换次数\n");
    printf("──────────────────────┼─────────┼─────────\n");
    printf("冒泡排序(学号升序)    | %-8d | %-8d\n", bubbleIDStats.comparisons, bubbleIDStats.swaps);
    printf("冒泡排序(成绩降序)    | %-8d | %-8d\n", bubbleScoreStats.comparisons, bubbleScoreStats.swaps);
    printf("快速排序(学号升序)    | %-8d | %-8d\n", quickIDStats.comparisons, quickIDStats.swaps);
    printf("快速排序(成绩降序)    | %-8d | %-8d\n", quickScoreStats.comparisons, quickScoreStats.swaps);

    printf("\n【测试完成】\n\n");
}

// 主函数
int main() {
    StudentTable table;
    initTable(&table);

    int choice;

    printf("\n╔════════════════════════════════╗\n");
    printf("║  欢迎使用学生信息管理系统      ║\n");
    printf("╚════════════════════════════════╝\n\n");

    while (1) {
        printMenu();
        choice = getIntInput();

        switch (choice) {
            case 1:
                // 录入学生信息
                inputStudentInfo(&table);
                break;

            case 2:
                // 显示所有学生信息
                displayAll(&table);
                break;

            case 3: {
                // 按学号查找（顺序查找）
                printf("\n请输入要查找的学号: ");
                int id = getIntInput();
                SearchResult result = sequentialSearchByID(&table, id);
                displaySearchResult(&result, &table, "按学号顺序查找", id, NULL);
                break;
            }

            case 4: {
                // 按学号查找（二分查找）
                if (table.count == 0) {
                    printf("\n系统中暂无学生信息\n\n");
                    break;
                }

                printf("\n注意：二分查找需要数据已按学号排序\n");
                printf("请输入要查找的学号: ");
                int id = getIntInput();

                // 创建排序副本
                StudentTable sortedTable;
                initTable(&sortedTable);
                copyTable(&table, &sortedTable);
                bubbleSortByID(&sortedTable);

                SearchResult result = binarySearchByID(&sortedTable, id);
                displaySearchResult(&result, &sortedTable, "按学号二分查找", id, NULL);
                break;
            }

            case 5: {
                // 按姓名查找（顺序查找）
                printf("\n请输入要查找的姓名: ");
                char name[50];
                getStringInput(name, sizeof(name));
                SearchResult result = sequentialSearchByName(&table, name);
                displaySearchResult(&result, &table, "按姓名顺序查找", 0, name);
                break;
            }

            case 6: {
                // 按学号升序排序（冒泡排序）
                if (table.count == 0) {
                    printf("\n系统中暂无学生信息\n\n");
                    break;
                }

                StudentTable testTable;
                copyTable(&table, &testTable);
                SortStats stats = bubbleSortByID(&testTable);
                displaySortResult(&testTable, "冒泡排序 - 学号升序", &stats);
                break;
            }

            case 7: {
                // 按成绩降序排序（冒泡排序）
                if (table.count == 0) {
                    printf("\n系统中暂无学生信息\n\n");
                    break;
                }

                StudentTable testTable;
                copyTable(&table, &testTable);
                SortStats stats = bubbleSortByScore(&testTable);
                displaySortResult(&testTable, "冒泡排序 - 成绩降序", &stats);
                break;
            }

            case 8: {
                // 按学号升序排序（快速排序）
                if (table.count == 0) {
                    printf("\n系统中暂无学生信息\n\n");
                    break;
                }

                StudentTable testTable;
                copyTable(&table, &testTable);
                SortStats stats = quickSortByID(&testTable);
                displaySortResult(&testTable, "快速排序 - 学号升序", &stats);
                break;
            }

            case 9: {
                // 按成绩降序排序（快速排序）
                if (table.count == 0) {
                    printf("\n系统中暂无学生信息\n\n");
                    break;
                }

                StudentTable testTable;
                copyTable(&table, &testTable);
                SortStats stats = quickSortByScore(&testTable);
                displaySortResult(&testTable, "快速排序 - 成绩降序", &stats);
                break;
            }

            case 10:
                // 运行测试
                runTests(&table);
                break;

            case 0:
                // 退出系统
                printf("\n感谢使用学生信息管理系统！再见！\n\n");
                return 0;

            default:
                printf("\n❌ 输入错误，请选择 0-10\n\n");
        }
    }

    return 0;
}
