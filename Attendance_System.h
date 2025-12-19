#ifndef ATTENDANCE_SYSTEM_H
#define ATTENDANCE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENT_MAX 1000
#define ATTEND_MAX 10000


int attend_num;
int student_num;  // 全局变量，分别是但前考勤记录条数和学生人数

void add_student();
void delect_student();
void search_student();
void list_student();
void record_attend();
void view_attend();
void count_attend();
void revise();
void loaddata();
void savedata();
void menu();

// 学生基本信息结构体
typedef struct student {
    int id;            // 学号
    char name[15];     // 姓名
    char classes[20];  // 班级
    char sex[5];       // 性别
    int sum;           // 总共有的课数
    int count;         // 总出勤数
} Student;

// 考勤信息结构体
typedef struct attent {
    int attend_id;     // 记录id
    int id;            // 学号
    char subject[20];  // 课程
    int mode;          // 考勤状态
    char date[20];     // 日期

} Attend;

Student student[STUDENT_MAX];  // 学生基本信息结构体数组
Attend attend[ATTEND_MAX];     // 考勤信息结构体数组

#endif
