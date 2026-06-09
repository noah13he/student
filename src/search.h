#ifndef SEARCH_H
#define SEARCH_H

#include "student.h"

// 查找结果结构体
typedef struct {
    int found;      // 是否找到（1找到，0未找到）
    int index;      // 找到的索引
    int comparisons; // 比较次数
} SearchResult;

// 查找函数声明

// 按学号顺序查找
SearchResult sequentialSearchByID(const StudentTable *table, int id);

// 按学号二分查找（需要先排序）
SearchResult binarySearchByID(const StudentTable *table, int id);

// 按姓名顺序查找
SearchResult sequentialSearchByName(const StudentTable *table, const char *name);

// 显示查找结果
void displaySearchResult(const SearchResult *result, const StudentTable *table, 
                         const char *method, int id, const char *name);

#endif // SEARCH_H
