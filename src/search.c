#include "search.h"

// 按学号顺序查找
SearchResult sequentialSearchByID(const StudentTable *table, int id) {
    SearchResult result = {0, -1, 0};
    
    if (table == NULL || table->count == 0) {
        return result;
    }

    for (int i = 0; i < table->count; i++) {
        result.comparisons++;
        if (table->students[i].id == id) {
            result.found = 1;
            result.index = i;
            return result;
        }
    }
    
    return result;
}

// 按学号二分查找（需要先排序）
SearchResult binarySearchByID(const StudentTable *table, int id) {
    SearchResult result = {0, -1, 0};
    
    if (table == NULL || table->count == 0) {
        return result;
    }

    int left = 0, right = table->count - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        result.comparisons++;
        
        if (table->students[mid].id == id) {
            result.found = 1;
            result.index = mid;
            return result;
        } else if (table->students[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// 按姓名顺序查找
SearchResult sequentialSearchByName(const StudentTable *table, const char *name) {
    SearchResult result = {0, -1, 0};
    
    if (table == NULL || table->count == 0 || name == NULL) {
        return result;
    }

    for (int i = 0; i < table->count; i++) {
        result.comparisons++;
        if (strcmp(table->students[i].name, name) == 0) {
            result.found = 1;
            result.index = i;
            return result;
        }
    }
    
    return result;
}

// 显示查找结果
void displaySearchResult(const SearchResult *result, const StudentTable *table, 
                         const char *method, int id, const char *name) {
    if (result == NULL) return;

    printf("\n【%s结果】\n", method);
    printf("比较次数: %d\n", result->comparisons);

    if (result->found) {
        printf("✓ 查找成功！\n");
        Student *student = &table->students[result->index];
        printf("┌─────────────────────────┐\n");
        printf("│ 学号: %-6d            │\n", student->id);
        printf("│ 姓名: %-15s     │\n", student->name);
        printf("│ 成绩: %-6.2f            │\n", student->score);
        printf("└─────────────────────────┘\n");
    } else {
        if (id > 0) {
            printf("❌ 查找失败：不存在学号为 %d 的学生\n", id);
        } else {
            printf("❌ 查找失败：不存在姓名为 %s 的学生\n", name ? name : "");
        }
    }
    printf("\n");
}
