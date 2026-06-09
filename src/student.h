#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大学生数
#define MAX_STUDENTS 100

// 学生信息结构体
typedef struct {
    int id;              // 学号
    char name[50];       // 姓名
    float score;         // 成绩
} Student;

// 学生表结构体
typedef struct {
    Student students[MAX_STUDENTS];
    int count;           // 当前学生数
} StudentTable;

// 函数声明

// 初始化学生表
void initTable(StudentTable *table);

// 添加学生信息
int addStudent(StudentTable *table, int id, const char *name, float score);

// 显示所有学生信息
void displayAll(const StudentTable *table);

// 显示单个学生信息
void displayStudent(const Student *student);

// 获取学生表大小
int getTableSize(const StudentTable *table);

// 获取指定索引的学生
Student* getStudent(StudentTable *table, int index);

// 复制学生表（用于排序操作）
void copyTable(const StudentTable *source, StudentTable *dest);

// 清空学生表
void clearTable(StudentTable *table);

#endif // STUDENT_H
