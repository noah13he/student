#ifndef SORT_H
#define SORT_H

#include "student.h"

// 排序统计结构体
typedef struct {
    int comparisons;  // 比较次数
    int swaps;        // 交换次数
} SortStats;

// 排序函数声明

// 冒泡排序 - 按学号升序
SortStats bubbleSortByID(StudentTable *table);

// 冒泡排序 - 按成绩降序
SortStats bubbleSortByScore(StudentTable *table);

// 快速排序 - 按学号升序
SortStats quickSortByID(StudentTable *table);

// 快速排序 - 按成绩降序
SortStats quickSortByScore(StudentTable *table);

// 显示排序结果
void displaySortResult(const StudentTable *table, const char *method, const SortStats *stats);

#endif // SORT_H
