#include "sort.h"

// 辅助函数：交换两个学生
static void swapStudent(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// 冒泡排序 - 按学号升序
SortStats bubbleSortByID(StudentTable *table) {
    SortStats stats = {0, 0};
    
    if (table == NULL || table->count <= 1) {
        return stats;
    }

    for (int i = 0; i < table->count - 1; i++) {
        for (int j = 0; j < table->count - i - 1; j++) {
            stats.comparisons++;
            if (table->students[j].id > table->students[j + 1].id) {
                swapStudent(&table->students[j], &table->students[j + 1]);
                stats.swaps++;
            }
        }
    }
    
    return stats;
}

// 冒泡排序 - 按成绩降序
SortStats bubbleSortByScore(StudentTable *table) {
    SortStats stats = {0, 0};
    
    if (table == NULL || table->count <= 1) {
        return stats;
    }

    for (int i = 0; i < table->count - 1; i++) {
        for (int j = 0; j < table->count - i - 1; j++) {
            stats.comparisons++;
            if (table->students[j].score < table->students[j + 1].score) {
                swapStudent(&table->students[j], &table->students[j + 1]);
                stats.swaps++;
            }
        }
    }
    
    return stats;
}

// 快速排序 - 按学号升序（辅助函数）
static int partitionByID(StudentTable *table, int low, int high, SortStats *stats) {
    int pivot = table->students[high].id;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats->comparisons++;
        if (table->students[j].id < pivot) {
            i++;
            swapStudent(&table->students[i], &table->students[j]);
            stats->swaps++;
        }
    }
    
    swapStudent(&table->students[i + 1], &table->students[high]);
    stats->swaps++;
    return i + 1;
}

// 快速排序 - 按学号升序（递归函数）
static void quickSortByIDHelper(StudentTable *table, int low, int high, SortStats *stats) {
    if (low < high) {
        int pi = partitionByID(table, low, high, stats);
        quickSortByIDHelper(table, low, pi - 1, stats);
        quickSortByIDHelper(table, pi + 1, high, stats);
    }
}

// 快速排序 - 按学号升序
SortStats quickSortByID(StudentTable *table) {
    SortStats stats = {0, 0};
    
    if (table == NULL || table->count <= 1) {
        return stats;
    }

    quickSortByIDHelper(table, 0, table->count - 1, &stats);
    return stats;
}

// 快速排序 - 按成绩降序（辅助函数）
static int partitionByScore(StudentTable *table, int low, int high, SortStats *stats) {
    float pivot = table->students[high].score;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats->comparisons++;
        if (table->students[j].score > pivot) {
            i++;
            swapStudent(&table->students[i], &table->students[j]);
            stats->swaps++;
        }
    }
    
    swapStudent(&table->students[i + 1], &table->students[high]);
    stats->swaps++;
    return i + 1;
}

// 快速排序 - 按成绩降序（递归函数）
static void quickSortByScoreHelper(StudentTable *table, int low, int high, SortStats *stats) {
    if (low < high) {
        int pi = partitionByScore(table, low, high, stats);
        quickSortByScoreHelper(table, low, pi - 1, stats);
        quickSortByScoreHelper(table, pi + 1, high, stats);
    }
}

// 快速排序 - 按成绩降序
SortStats quickSortByScore(StudentTable *table) {
    SortStats stats = {0, 0};
    
    if (table == NULL || table->count <= 1) {
        return stats;
    }

    quickSortByScoreHelper(table, 0, table->count - 1, &stats);
    return stats;
}

// 显示排序结果
void displaySortResult(const StudentTable *table, const char *method, const SortStats *stats) {
    if (table == NULL || method == NULL || stats == NULL) return;

    printf("\n【%s】\n", method);
    printf("比较次数: %d, 交换次数: %d\n", stats->comparisons, stats->swaps);
    printf("┌────────┬──────────────┬────────────┐\n");
    printf("│  学号  │    姓名      │    成绩    │\n");
    printf("├────────┼──────────────┼────────────┤\n");

    for (int i = 0; i < table->count; i++) {
        printf("│ %6d │ %-12s │ %10.2f │\n", 
               table->students[i].id, 
               table->students[i].name, 
               table->students[i].score);
    }
    printf("└────────┴──────────────┴────────────┘\n\n");
}
