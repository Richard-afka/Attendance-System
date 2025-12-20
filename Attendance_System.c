#include "Attendance_System.h"

// Student student[STUDENT_MAX];  // 学生基本信息结构体数组
// Attend attend[ATTEND_MAX];     //考勤信息结构体数组
int attend_num=0, student_num=0;   //全局变量，分别是但前考勤记录条数和学生人数

void menu() {
    printf("=== 菜单 ===\n");
    printf("1. 添加学生\n");
    printf("2. 删除学生或某条考勤记录\n");
    printf("3. 查询学生\n");
    printf("4. 显示所有学生\n");
    printf("5. 记录考勤\n");
    printf("6. 查看考勤\n");
    printf("7. 考勤统计\n");
    printf("8. 修改某条考勤记录\n");
    printf("0. 退出系统\n");
    printf("请选择操作：\n");
}

int main() {
    printf("欢迎使用学生考勤系统！\n\n");
    int n;
    loaddata();
    while (1) {
        menu();
        scanf("%d", &n);
        getchar();
        if (n == 0) {
            printf("感谢使用！\n");
            savedata();
            return 0;
        }
        switch(n){
            case 1:
                add_student();
                break;
            case 2:
                delect_student();
                break;
            case 3:
                search_student();
                break;
            case 4:
                list_student();
                break;
            case 5:
                record_attend();
                break;
            case 6:
                view_attend();
                break;
            case 7:
                count_attend();
                break;
            case 8:
                revise();
                break;
            default:
                printf("请输入正确选项！\n");
                break;
        }
    }
    return 0;
}
void loaddata(){
    int count_stu = 0;
    int count_att = 0;
    FILE* fp_stu = fopen("Studentdata.txt", "r");
    if(fp_stu==NULL){
        printf("文件不存在！\n");
        student_num = 0;
    }else{
    char line_stu[100];
    fgets(line_stu, sizeof(line_stu), fp_stu);
    for (int i = 0; student_num < STUDENT_MAX; i++) {
        if(fscanf(fp_stu, "学号：%d\n姓名：%s\n班级：%s\n性别：%s\n",
             &student[i].id, student[i].name,
             student[i].classes, student[i].sex)==4){
            count_stu++;
        }else{
            break;
        }
    }
    printf("已加载%d条学生数据,", count_stu);
    fclose(fp_stu);
}
    FILE* fp_att = fopen("Attenddata.txt", "r");
    if (fp_att == NULL) {
        printf("文件不存在！\n");
        attend_num = 0;
    }
    else {
        char line_att[100];
        fgets(line_att, sizeof(line_att), fp_att);
        for (int i = 0; attend_num < ATTEND_MAX; i++) {
            if (fscanf(fp_att, "%d\t%d\t%s\t\t%d\t%s", &attend[i].attend_id,
                       &attend[i].id, attend[i].subject, &attend[i].mode,
                       attend[i].date) == 5) {
                count_att++;
            } else {
                break;
            }
        }
        fclose(fp_att);
        printf("%d条考勤记录\n\n",count_att);
    }
    student_num = count_stu;
    attend_num = count_att;
}
void savedata(){
    FILE* fp_stu = fopen("Studentdata.txt", "w");
    if (fp_stu == NULL) {
        perror("文件打开错误！\n");
        return;
    }
    fprintf(fp_stu, "学生信息：\n");
    for (int i = 0; i < student_num; i++) {
        fprintf(fp_stu, "学号：%d\n", student[i].id);
        fprintf(fp_stu, "姓名：%s\n", student[i].name);
        fprintf(fp_stu, "班级：%s\n", student[i].classes);
        fprintf(fp_stu, "性别：%s\n\n", student[i].sex);

    }
    FILE* fp_att = fopen("Attenddata.txt", "w");
    if (fp_att == NULL) {
        perror("文件打开错误！\n");
        return;
    }
    fprintf(fp_att, "记录id\t学号\t课程\t\t考勤状态\t日期\n");
    for (int i = 0; i < attend_num; i++) {
        fprintf(fp_att, "%d\t", attend[i].attend_id);
        fprintf(fp_att, "%d\t", attend[i].id);
        fprintf(fp_att, "%s\t\t", attend[i].subject);
        fprintf(fp_att, "%d\t", attend[i].mode);
        fprintf(fp_att, "%s\n", attend[i].date);
    }
    fclose(fp_stu);
    fclose(fp_att);
} void record_attend() {
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
        printf("\n暂无考勤记录！\n\n");
        return;
    }

    int choice;
    printf("\n----- 选择查看方式 -----\n");
    printf("1. 查看全部考勤记录\n");
    printf("2. 查看某学生的考勤记录\n");
    printf("3. 查看某课程的考勤记录\n");
    printf("4. 查看某天的考勤记录\n");
    printf("请输入选项：");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > 4) {
        printf("输入错误！请输入1-4之间的数字\n\n");
        return;
    }

    const char* mode_str[] = {"", "出勤", "缺勤", "迟到", "请假"};
    int match_cnt = 0;

    switch (choice) {
        case 1:
            // 列宽保持35，足够显示合规课程名
            printf("\n---------------------------------- 全部考勤记录 ------------------------------------------\n");
            printf("%-10s%-15s%-35s%-10s%-20s\n",
                   "记录ID", "学号", "课程", "考勤状态", "日期");
            printf("------------------------------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                printf("%-10d%-15d%-35s%-10s%-20s\n",
                       attend[i].attend_id,
                       attend[i].id,
                       attend[i].subject,
                       mode_str[attend[i].mode],
                       attend[i].date);
                match_cnt++;
            }
            printf("------------------------------------------------------------------------------------------\n");
            break;

        case 2: {
            int target_id;
            printf("请输入学生学号：");
            scanf("%d", &target_id);
            printf("\n-------------------------- 学生%d的考勤记录 --------------------------\n", target_id);
            printf("%-10s%-35s%-10s%-20s\n",
                   "记录ID", "课程", "考勤状态", "日期");
            printf("---------------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (attend[i].id == target_id) {
                    printf("%-10d%-35s%-10s%-20s\n",
                           attend[i].attend_id,
                           attend[i].subject,
                           mode_str[attend[i].mode],
                           attend[i].date);
                    match_cnt++;
                }
            }
            printf("---------------------------------------------------------------------------\n");
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
            printf("\n-------------------------- 课程%s的考勤记录 --------------------------\n", target_sub);
            printf("%-10s%-15s%-10s%-20s\n",
                   "记录ID", "学号", "考勤状态", "日期");
            printf("-------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (strcmp(attend[i].subject, target_sub) == 0) {
                    printf("%-10d%-15d%-10s%-20s\n",
                           attend[i].attend_id,
                           attend[i].id,
                           mode_str[attend[i].mode],
                           attend[i].date);
                    match_cnt++;
                }
            }
            printf("-------------------------------------------------------\n");
            if (match_cnt == 0) {
                printf("该课程无考勤记录！\n");
            }
            break;
        }

        case 4: {
            char target_date[20];
            printf("请输入日期（格式：2025-12-15）：");
            scanf("%s", target_date);
            printf("\n-------------------------- %s的考勤记录 --------------------------\n", target_date);
            printf("%-10s%-15s%-35s%-10s\n",
                   "记录ID", "学号", "课程", "考勤状态");
            printf("----------------------------------------------------------------------\n");
            for (int i = 0; i < attend_num; i++) {
                if (strcmp(attend[i].date, target_date) == 0) {
                    printf("%-10d%-15d%-35s%-10s\n",
                           attend[i].attend_id,
                           attend[i].id,
                           attend[i].subject,
                           mode_str[attend[i].mode]);
                    match_cnt++;
                }
            }
            printf("----------------------------------------------------------------------\n");
            if (match_cnt == 0) {
                printf("该日期无考勤记录！\n");
            }
            break;
        }
    }

    if (match_cnt > 0) {
        printf("共找到%d条考勤记录\n\n", match_cnt);
    } else {
        printf("\n");
    }
}
