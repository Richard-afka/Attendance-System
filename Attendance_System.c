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
	int i;
	int chuqin = 0, qingjia = 0, queqin = 0, chidao = 0;
	
	if (attend_num == 0) {
		printf("暂无考勤记录！\n");
		return;
	}
	
	for (i = 0; i < attend_num; i++) {
		switch (attend[i].mode) {
			case 1: chuqin++; break;
			case 2: queqin++; break;
			case 3: chidao++; break;
			case 4: qingjia++; break;
		}
	}
	
	printf("总记录数：%d\n", attend_num);
	printf("出勤：%d\n", chuqin);
	printf("缺勤：%d\n", queqin);
	printf("迟到：%d\n", chidao);
	printf("请假：%d\n", qingjia);
	
	printf("出勤率：%.2f%%\n", (float)chuqin / attend_num * 100);
}

void revise() {
	int id, i;
	int found = 0;
	
	if (attend_num == 0) {
		printf("暂无考勤记录，无法修改！\n");
		return;
	}

	view_attend();

	printf("请输入要修改的记录编号：");
	scanf("%d",&id);
		while(1){
			if(id>attend_num){printf("该学生不存在！\n请重新输入：\n");
			scanf("%d", &id);
		}
			else break;}
			

	for (i = 0; i < attend_num; i++) {
		if (attend[i].attend_id == id) {
			found = 1;
			
			printf("请输入新的学号：");
			scanf("%s", &attend[i].id);

			printf("请输入新的课程：");
			scanf("%s", attend[i].subject);
			
			printf("请输入新的日期(如 2025-12-12)：");
			scanf("%s", attend[i].date);
			
			printf("请输入新的考勤状态(1出勤 2缺勤 3迟到 4请假)：");
			int a;
			int old_mode=attend[i].mode;
			scanf("%d", &a);
			while(1){
				if(a<1||a>4){printf("请输入正确数字：");
				scanf("%d", &a);
			}
				else{   
					attend[i].mode=a;
			     		break;
			    }
			     	}
			if((old_mode==1||old_mode==3)&&(a==2||a==4)){
				student[i].count--;}
			else if((old_mode==2||old_mode==4)&&(a==1||a==3)){
				student[i].count++;}
			
			printf("修改成功！\n");
			break;
		}
	}
	
	if (!found) {
		printf("未找到该记录编号！\n");
	}
	count_attend();
}


