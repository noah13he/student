#include "student.h"

// 初始化学生表
void initTable(StudentTable *table) {
    if (table == NULL) return;
    table->count = 0;
}

// 添加学生信息
int addStudent(StudentTable *table, int id, const char *name, float score) {
    if (table == NULL || table->count >= MAX_STUDENTS) {
        printf("❌ 添加失败：学生表已满或表为空\n");
        return 0;
    }

    Student *student = &table->students[table->count];
    student->id = id;
    strncpy(student->name, name, MAX_NAME_LEN - 1);
    student->name[MAX_NAME_LEN - 1] = '\0';
    student->score = score;
    
    table->count++;
    printf("✓ 学生信息添加成功！\n");
    return 1;
}

// 显示所有学生信息
void displayAll(const StudentTable *table) {
    if (table == NULL || table->count == 0) {
        printf("\n系统中暂无学生信息\n\n");
        return;
    }

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        学生信息列表（共%d人）         ║\n", table->count);
    printf("╚════════════════════════════════════════╝\n");
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

// 显示单个学生信息
void displayStudent(const Student *student) {
    if (student == NULL) return;
    printf("学号: %d, 姓名: %s, 成绩: %.2f\n", 
           student->id, student->name, student->score);
}

// 获取学生表大小
int getTableSize(const StudentTable *table) {
    if (table == NULL) return 0;
    return table->count;
}

// 获取指定索引的学生
Student* getStudent(StudentTable *table, int index) {
    if (table == NULL || index < 0 || index >= table->count) {
        return NULL;
    }
    return &table->students[index];
}

// 复制学生表
void copyTable(const StudentTable *source, StudentTable *dest) {
    if (source == NULL || dest == NULL) return;
    
    dest->count = source->count;
    for (int i = 0; i < source->count; i++) {
        dest->students[i] = source->students[i];
    }
}

// 清空学生表
void clearTable(StudentTable *table) {
    if (table == NULL) return;
    table->count = 0;
}
