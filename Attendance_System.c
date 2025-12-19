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
}

void count_attend() {
	int present = 0, absent = 0, late = 0, leave = 0;
	
	for (int i = 0; i < attend_count; i++) {
		if (strcmp(attends[i].status, "出勤") == 0) {
			present++;
		} else if (strcmp(attends[i].status, "缺勤") == 0) {
			absent++;
		} else if (strcmp(attends[i].status, "迟到") == 0) {
			late++;
		} else if (strcmp(attends[i].status, "请假") == 0) {
			leave++;
		}
	}

	printf("总记录数：%d\n", attend_count);
	printf("出勤：%d\n", present);
	printf("请假：%d\n", leave);
	printf("缺勤：%d\n", absent);
	printf("迟到：%d\n", late);
	
	if (attend_count > 0) {
		float attendance_rate = ((float)present / attend_count) * 100;
		printf("出勤率：%.2f%%\n", attendance_rate);
	} else {
		printf("没有考勤记录。\n");
	}
}


void revise_attend() {

	printf("选择要修改的记录编号：\n");
	for (int i = 0; i < attend_count; i++) {
		printf("%d. 学号：%s 日期：%s 课程：%s 状态：%s\n", 
			   i + 1, attends[i].stu_id, 
			   attends[i].date, 
			   attends[i].course, 
			   attends[i].status);
	}
	
	int record_index;
	printf("请输入要修改的记录编号：");
	scanf("%d", &record_index);

	if (record_index < 1 || record_index > attend_count) {
		printf("无效的记录编号。\n");
		return;
	}
	

	Attendance *record = &attends[record_index - 1];

	printf("请输入新的考勤状态：\n");
	printf("1. 出勤\n2. 缺勤\n3. 迟到\n4. 请假\n");
	int new_status;
	scanf("%d", &new_status);

	switch (new_status) {
		case 1: strcpy(record->status, "出勤"); break;
		case 2: strcpy(record->status, "缺勤"); break;
		case 3: strcpy(record->status, "迟到"); break;
		case 4: strcpy(record->status, "请假"); break;
	default:
		printf("无效的状态。\n");
		return;
	}
	
	printf("考勤记录修改成功！\n");
}




