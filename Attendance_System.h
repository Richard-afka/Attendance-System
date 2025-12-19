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

void record_attend() {
    if (attend_num >= ATTEND_MAX) {
        printf("考勤记录已达上限！\n");
        return;
    }

    int stu_id;
    printf("请输入学生学号：");
    scanf("%d", &stu_id);
    getchar();

    int stu_idx = -1;
    for (int i = 0; i < student_num; i++) {
        if (student[i].id == stu_id) {
            stu_idx = i;
            break;
        }
    }
    if (stu_idx == -1) {
        printf("该学生不存在！\n");
        return;
    }

    Attend new_att;
    new_att.attend_id = attend_num + 1;
    new_att.id = stu_id;

    printf("请输入课程名称：");
    fgets(new_att.subject, 20, stdin);
    new_att.subject[strcspn(new_att.subject, "\n")] = '\0';

    printf("请输入考勤状态（1-出勤 2-缺勤 3-迟到 4-请假）：");
    scanf("%d", &new_att.mode);
    if (new_att.mode < 1 || new_att.mode > 4) {
        printf("输入错误！请输入1-4之间的数字\n");
        return;
    }

    printf("请输入日期（格式：2025-12-15）：");
    scanf("%s", new_att.date);

    attend[attend_num] = new_att;
    attend_num++;

    student[stu_idx].sum += 1;
    if (new_att.mode == 1) {
        student[stu_idx].count += 1;
    }

    printf("考勤记录添加成功！\n");
}

void view_attend() {
    if (attend_num == 0) {
        printf("暂无考勤记录！\n");
        return;
    }

    int choice;
    printf("请选择查看方式：\n");
    printf("1. 查看全部考勤记录\n");
    printf("2. 查看某学生的考勤记录\n");
    printf("3. 查看某课程的考勤记录\n");
    printf("4. 查看某天的考勤记录\n");
    printf("请输入选项：");
    scanf("%d", &choice);
    getchar();
    if (choice < 1 || choice > 4) {
        printf("输入错误！请输入1-4之间的数字\n");
        return;
    }

    const char* mode_str[] = {"", "出勤", "缺勤", "迟到", "请假"};
    int match_cnt = 0;

    switch (choice) {
        case 1:
            printf("-------------------------- 全部考勤记录 --------------------------\n");
            printf("记录ID\t学号\t课程\t\t考勤状态\t日期\n");
            printf("------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                printf("%d\t%d\t%s\t\t%s\t\t%s\n",
                       attend[i].attend_id,
                       attend[i].id,
                       attend[i].subject,
                       mode_str[attend[i].mode],
                       attend[i].date);
                match_cnt++;
            }
            break;

        case 2: {
            int target_id;
            printf("请输入学生学号：");
            scanf("%d", &target_id);
            printf("-------------------------- 学生%d的考勤记录 --------------------------\n", target_id);
            printf("记录ID\t课程\t\t考勤状态\t日期\n");
            printf("------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (attend[i].id == target_id) {
                    printf("%d\t%s\t\t%s\t\t%s\n",
                           attend[i].attend_id,
                           attend[i].subject,
                           mode_str[attend[i].mode],
                           attend[i].date);
                    match_cnt++;
                }
            }
            if (match_cnt == 0) {
                printf("该学生无考勤记录！\n");
            }
            break;
        }

        case 3: {
            char target_sub[20];
            printf("请输入课程名称：");
            fgets(target_sub, 20, stdin);
            target_sub[strcspn(target_sub, "\n")] = '\0';
            printf("-------------------------- 课程%s的考勤记录 --------------------------\n", target_sub);
            printf("记录ID\t学号\t考勤状态\t日期\n");
            printf("------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (strcmp(attend[i].subject, target_sub) == 0) {
                    printf("%d\t%d\t%s\t\t%s\n",
                           attend[i].attend_id,
                           attend[i].id,
                           mode_str[attend[i].mode],
                           attend[i].date);
                    match_cnt++;
                }
            }
            if (match_cnt == 0) {
                printf("该课程无考勤记录！\n");
            }
            break;
        }

        case 4: {
            char target_date[20];
            printf("请输入日期（格式：2025-12-15）：");
            scanf("%s", target_date);
            printf("-------------------------- %s的考勤记录 --------------------------\n", target_date);
            printf("记录ID\t学号\t课程\t\t考勤状态\n");
            printf("------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (strcmp(attend[i].date, target_date) == 0) {
                    printf("%d\t%d\t%s\t\t%s\n",
                           attend[i].attend_id,
                           attend[i].id,
                           attend[i].subject,
                           mode_str[attend[i].mode]);
                    match_cnt++;
                }
            }
            if (match_cnt == 0) {
                printf("该日期无考勤记录！\n");
            }
            break;
        }
    }

    if (match_cnt > 0) {
        printf("------------------------------------------------------------------\n");
        printf("共找到%d条考勤记录\n", match_cnt);
    }
}

