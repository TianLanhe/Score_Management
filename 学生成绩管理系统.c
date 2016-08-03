#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define NAME 0
#define NUMBER 1
#define ALL 2
#define MARK 3
#define COU1 4
#define COU2 5
#define COU3 6
#define COU4 7
#define COU5 8
#define FROMBIG 0                               //从大到小
#define FROMSMALL 1                             //从小到大
typedef struct cou{
	int lesnumber;								//课程编号
    char lesname[41];      						//课程名字
    double score,point;     					//分数,学分
}COU;
typedef struct stu{
	int num;									//学号
	char name[11],sex[5],cla[20];				//姓名，性别，班级
    struct cou les[5];                       	//5门课程
    double all,average,mark;                    //总分，平均分，绩点
	struct stu *next;
}STU;
void PrintMenuTea();							 //打印老师菜单
void PrintMenuStu();							 //打印学生菜单
void PrintLogin();							     //打印登录菜单
void PrintMenuSort();						     //打印排序菜单
void PrintMenuSort2();							 //打印排序菜单2
int RegisterTea();      						 //教师注册
int RegisterStu();      						 //学生注册
int LoginTea();         						 //教师登录
int LoginStu();         						 //学生登录
int Count(STU *head);                            //计算学生人数(节点个数)
int StuNum(STU *p,double low,double high); 		 //计算学生科目符合条件的数量
void DisplayAll(STU *head);						 //打印所有学生信息
STU *Search_name(STU *head,char *name);		     //通过名字搜索学生
STU *Search_num(STU *head,int num);    		     //通过学号搜索学生
void DisplayOne(STU *head,int n,char *name);	 //打印一个学生详细信息
void DisplayCla(STU *head,char *class);			 //按班级显示学生信息
void DisplayGrade(STU *head,double low,double high); //按分数段查询成绩
void DisplayFail(STU *head);					 //不及格科目查询
STU *Delete(STU *head,int n,char *name,int *item);   //删除学生成绩
int Modify(STU *head,int n,char *name);			 //修改学生成绩
int Save(STU *head);							 //保存学生成绩
int Lof(FILE *fp);								 //计算文件中学生人数
STU *Initialize();								 //初始化读取文件中的学生
STU *Creat(int n);                  			 //创建链表
int Position(STU *head,STU *p);					 //确定节点在链表的位置
STU *Sort(STU *head,int m,int n);                //成绩排序
STU *SetPosition(STU *head,int n);				 //将链表移动到指定节点
STU *Connect(STU *head,STU *end);   			 //连接两个链表
double Mark(STU *p);							 //计算绩点
STU *Input();              			 			 //输入学生成绩
void HideCursor();								 //隐藏光标
void PutCursor(); 								 //显示光标
void GotoXy(int x,int y);						 //将光标移动到(X,Y)
void GetXy(int *X,int *Y,int x1,int x2,int y1,int y2); //获取在限定范围内鼠标点击的坐标
void Clear(int x,int y,int line);				 //清除line行的内容后将坐标返回(x,y)
void PrintMenuTea(){                      		 //打印老师菜单
	printf("\n");
	printf("         ┌─────────欢迎使用学生成绩管理系统────────┐         ");
	printf("         │                                                          │         ");
	printf("         │            请选择操作项目：                              │         ");
	printf("         │               1.录入成绩          2.修改成绩             │         ");
	printf("         │               3.删除成绩          4.查询成绩             │         ");
	printf("         │               5.成绩排序          6.显示成绩             │         ");
	printf("         │               7.保存成绩          8.退出登录             │         ");
	printf("         │               0.退出系统                                 │         ");
	printf("         └─────────────────────────────┘         ");
}
void PrintMenuStu(){					         //打印学生菜单
	printf("\n");
	printf("         ┌─────────欢迎使用学生成绩管理系统────────┐         ");
	printf("         │                                                          │         ");
	printf("         │            请选择操作项目：                              │         ");
	printf("         │               1.查询成绩          2.退出登录             │         ");
	printf("         │               0.退出系统                                 │         ");
	printf("         └─────────────────────────────┘         ");
}
void PrintLogin(){                               //打印登录界面
	printf("\n");
	printf("         ┌─────────欢迎使用学生成绩管理系统────────┐         ");
	printf("         │                                                          │         ");
	printf("         │            请选择身份登录或注册：                        │         ");
	printf("         │                         1.教师注册                       │         ");
	printf("         │                         2.教师登录                       │         ");
	printf("         │                         3.学生注册                       │         ");
	printf("         │                         4.学生登录                       │         ");
	printf("         │                         0.退出系统                       │         ");
	printf("         └─────────────────────────────┘         ");
}
void PrintMenuSort(){                      		 //打印排序菜单
	printf("\n");
	printf("         ┌───────────学生信息排序菜单──────────┐         ");
	printf("         │                                                          │         ");
	printf("         │            请选择排序方式：                              │         ");
	printf("         │               1.按学号            2.按姓名               │         ");
	printf("         │               3.按总分            4.按绩点               │         ");
	printf("         │               5.按课程1           6.按课程2              │         ");
	printf("         │               7.按课程3           8.按课程4              │         ");
	printf("         │               9.按课程5                                  │         ");
	printf("         └─────────────────────────────┘         ");
}
void PrintMenuSort2(){					         //打印排序菜单2
	printf("\n");
	printf("         ┌───────────学生信息排序菜单──────────┐         ");
	printf("         │                                                          │         ");
	printf("         │            请选择排序方式：                              │         ");
	printf("         │               1.从小到大          2.从大到小             │         ");
	printf("         └─────────────────────────────┘         ");
}
int RegisterTea(){      						 //教师注册
	char account[16],password[16],reginum[11];  //账号，密码，注册密码
	FILE *fp;
	int turn=1;                                 //用于检测账号是否已注册的开关
	char password_che[16];						//用于检测两次输入的密码是否一致
	char str1[16]={0},str2[16]={0};             //检验账号，检验密码
	printf("请输入您的工号：");
	scanf("%s",account);
	do{
		printf("请输入密码：");
		scanf("%s",password);
		printf("请再次输入密码：");
		scanf("%s",password_che);
		if(strcmp(password,password_che))printf("密码不一致，请重新输入！\n\n");
	}while(strcmp(password,password_che));
	printf("请输入注册密码：");
	scanf("%s",reginum);
	if(strcmp(reginum,"2014052421")){
		printf("注册密码错误，注册失败！\n");
		return 0;
	}else{
		if((fp=fopen("admintea.txt","a+"))==NULL){
			printf("注册失败！\n");
			return 0;
		}else{
			while(!feof(fp)){
				fscanf(fp,"%s%s",str1,str2);
				if(!strcmp(str1,account)){
					turn=0;
					break;
				}
			}
			if(turn){
				fseek(fp,0,2);
				fprintf(fp,"%s %s\n",account,password);
				fflush(fp);
				printf("注册成功！\n");
				fclose(fp);
				return 1;
			}else{
				printf("账号已注册！\n");
				fclose(fp);
				return 0;
			}
		}
	}
}
int RegisterStu(){								 //学生注册
	char account[16],password[16],reginum[11];  //账号，密码，注册密码
	FILE *fp;
	int turn=1;                                 //用于检测账号是否已注册的开关
	char password_che[16];						//用于检测两次密码是否输入正确
	char str1[16]={0},str2[16]={0};             //检验账号，检验密码
	printf("请输入您的学号：");
	scanf("%s",account);
	do{
		printf("请输入密码：");
		scanf("%s",password);
		printf("请再次输入密码：");
		scanf("%s",password_che);
		if(strcmp(password,password_che))printf("密码不一致，请重新输入！\n\n");
	}while(strcmp(password,password_che));
	printf("请输入注册密码：");
	scanf("%s",reginum);
	if(strcmp(reginum,"2014052421")){
		printf("注册密码错误，注册失败！\n");
		return 0;
	}else{
		if((fp=fopen("adminstu.txt","a+"))==NULL){
			printf("注册失败！\n");
			return 0;
		}else{
			while(!feof(fp)){
				fscanf(fp,"%s%s",str1,str2);
				if(!strcmp(str1,account)){
					turn=0;
					break;
				}
			}
			if(turn){
				fseek(fp,0,2);
				fprintf(fp,"%s %s\n",account,password);
				fflush(fp);
				printf("注册成功！\n");
				fclose(fp);
				return 1;
			}else{
				printf("账号已注册！\n");
				fclose(fp);
				return 0;
			}
		}
	}
}
int LoginTea(){									 //教师登录
	char account[16],password[16];       	    //账号，密码
	char che_acc[16]={0},che_pas[16]={0};       //检验账号，检验密码
	FILE *fp;
	int turn=0;                                 //用于检验账号密码是否匹配
	printf("请输入您的工号：");
	scanf("%s",account);
	printf("请输入密码：");
	scanf("%s",password);
	if((fp=fopen("admintea.txt","r"))==NULL){
		printf("登录失败！\n");
		return 0;
	}else{
		while(!feof(fp)){
			fscanf(fp,"%s%s",che_acc,che_pas);
			if(!strcmp(che_acc,account)&&!strcmp(che_pas,password)){
				turn=1;
				break;
			}
		}
		if(turn){
			printf("                                    登录成功！\n");
			fclose(fp);
			return 1;
		}else{
			printf("账号或密码错误，登录失败！\n");
			fclose(fp);
			return 0;
		}
	}
}
int LoginStu(){                                  //学生登录
	char account[16],password[16];       	    //账号，密码
	char che_acc[16]={0},che_pas[16]={0};       //检验账号，检验密码
	FILE *fp;
	int turn=0;                                 //用于检验账号密码是否匹配
	printf("请输入您的学号：");
	scanf("%s",account);
	printf("请输入密码：");
	scanf("%s",password);
	if((fp=fopen("adminstu.txt","r"))==NULL){
		printf("登录失败！\n");
		return 0;
	}else{
		while(!feof(fp)){
			fscanf(fp,"%s%s",che_acc,che_pas);
			if(!strcmp(che_acc,account)&&!strcmp(che_pas,password)){
				turn=1;
				break;
			}
		}
		if(turn){
			printf("                                    登录成功！\n");
			fclose(fp);
			return 1;
		}else{
			printf("账号或密码错误，登录失败！\n");
			fclose(fp);
			return 0;
		}
	}
}
int Count(STU *head){                            //计算学生人数(节点个数)
	int i;
	for(i=0;head!=NULL;i++,head=head->next);
	return i;
}
int StuNum(STU *p,double low,double high){ 		 //计算学生科目符合条件的数量
	int i,n=0;
	for(i=0;i<5;i++){
		if(p->les[i].score>=low&&p->les[i].score<=high)n++;
	}
	return n;
}
void DisplayAll(STU *head){						 //打印所有学生信息
	int rank=1;
	int i,n;
	printf("\n");
	n=Count(head);
	if(n==0){
		printf("────────────────────────────────────────");
		printf("                                  无学生记录！                                  ");
		printf("────────────────────────────────────────");
	}else{
		printf("─────┬───┬ ──┬ ──┬ ──┬ ──┬ ──┬ ──┬───┬──┬──");
		printf("   学号   │ 姓名 │课程1│课程2│课程3│课程4│课程5│总 分│平均分│绩点│排名");
		for(;head!=NULL;head=head->next){
			printf("%10d│%6s",head->num,head->name);
			for(i=0;i<5;i++)printf("│%5.1f",head->les[i].score);
			printf("│%5.1f│%6.1f│%4.1f│%3d ",head->all,head->average,head->mark,rank++);
		}
		printf("─────┴───┴ ──┴ ──┴ ──┴ ──┴ ──┴ ──┴───┴──┴──");
		printf("共有%d名学生\n",n);
	}
}
void DisplayOne(STU *head,int n,char *name){     //打印一个学生详细信息
	STU *p;
	int i;
	if(n==0)p=Search_name(head,name);
	else p=Search_num(head,atoi(name));
	if(p==NULL){
		printf("                               没有该学生的信息！\n");
		return;
	}
	printf("%s同学的详细信息：\n",p->name);
	printf("┌───┬──────┬───┬────┐\n");
	printf("│ 学号 │%12d│ 姓名 │%7s │\n",p->num,p->name);
	printf("├───┼──────┼───┼────┤\n");
	printf("│ 班级 │%12s│ 性别 │%7s │\n",p->cla,p->sex);
	printf("├───┼──────┼───┼────┤\n");
	for(i=0;i<5;i++){
		printf("│ 课程%d│%12s│ 分数 │%7.1f │\n",i+1,p->les[i].lesname,p->les[i].score);
		printf("├───┼──────┼───┼────┤\n");
	}
	printf("│ 总分 │%11.1f │平均分│%7.1f │\n",p->all,p->average);
	printf("├───┼──────┼───┴────┘\n");
	printf("│ 绩点 │%11.1f │\n",p->mark);
	printf("└───┴──────┘\n");
}
void DisplayCla(STU *head,char *class){			 //按班级显示学生信息
	int rank=1;
	int i,n=0;
	STU *t=head;
	for(;head!=NULL;head=head->next){
		if(!strcmp(head->cla,class)){
			break;
		}
	}
	if(head!=NULL){
		head=t;
		printf("\n");
		printf("─────┬───┬ ──┬ ──┬ ──┬ ──┬ ──┬ ──┬───┬──┬──");
		printf("   学号   │ 姓名 │课程1│课程2│课程3│课程4│课程5│总 分│平均分│绩点│排名");
		for(;head!=NULL;head=head->next){
			if(!strcmp(head->cla,class)){
				printf("%10d│%6s",head->num,head->name);
				for(i=0;i<5;i++)printf("│%5.1f",head->les[i].score);
				printf("│%5.1f│%6.1f│%4.1f│%3d ",head->all,head->average,head->mark,rank++);
				n++;
			}
		}
		printf("─────┴───┴ ──┴ ──┴ ──┴ ──┴ ──┴ ──┴───┴──┴──");
		printf("共有%d名 %s 班级的学生\n",n,class);
	}else{
		printf("\n");
		printf("────────────────────────────────────────");
		printf("                           无 %s 班级的学生！                            \n",class);
		printf("────────────────────────────────────────");
	}
}
void DisplayGrade(STU *head,double low,double high){ //按分数段查询成绩
	int i;
	int n;
	int t=0;
	for(;head!=NULL;head=head->next){
		n=StuNum(head,low,high);
		if(n!=0){
			t=1;
			printf("┌───┬──────┬───┬────┐\n");
			printf("│ 学号 │%12d│ 姓名 │%7s │\n",head->num,head->name);
			printf("├───┼──────┼───┼────┤\n");
			printf("│ 班级 │%12s│ 性别 │%7s │\n",head->cla,head->sex);
			for(i=0;i<5;i++){
				if(head->les[i].score>=low&&head->les[i].score<=high){
					printf("├───┼──────┼───┼────┤\n");
					printf("│ 课程%d│%12s│ 分数 │%7.1f │\n",i+1,head->les[i].lesname,head->les[i].score);
				}
			}
			printf("└───┴──────┴───┴────┘\n");
		}
	}
	if(t==0)printf("                              没有%.0f到%.0f分的成绩！\n",low,high);
}
void DisplayFail(STU *head){					 //不及格科目查询
	int i;
	int n;
	int t=0;
	for(;head!=NULL;head=head->next){
		n=StuNum(head,0,59);
		if(n!=0){
			t=1;
			printf("┌───┬──────┬───┬────┐\n");
			printf("│ 学号 │%12d│ 姓名 │%7s │\n",head->num,head->name);
			printf("├───┼──────┼───┼────┤\n");
			printf("│ 班级 │%12s│ 性别 │%7s │\n",head->cla,head->sex);
			for(i=0;i<5;i++){
				if(head->les[i].score<60){
					printf("├───┼──────┼───┼────┤\n");
					printf("│ 课程%d│%12s│ 分数 │%7.1f │\n",i+1,head->les[i].lesname,head->les[i].score);
				}
			}
			printf("└───┴──────┴───┴────┘\n");
		}
	}
	if(t==0)printf("\n                                没有不及格学生！\n");
}
STU *Delete(STU *head,int n,char *name,int *item){   //删除学生成绩
	STU *p,*t;
	if(n==0)p=Search_name(head,name);
	else p=Search_num(head,atoi(name));
	if(p==NULL){
		*item=0;
		return head;
	}else{
		if(p==head)head=head->next;
		else{
			for(t=head;t->next!=p;t=t->next);
			t->next=p->next;
		}
		*item=1;
		free(p);
		p=NULL;
		return head;
	}
}
int Modify(STU *head,int n,char *name){			 //修改学生成绩
	STU *p;
	int i;
	if(n==0)p=Search_name(head,name);
	else p=Search_num(head,atoi(name));
	if(p==NULL){
		return 0;
	}else{
		printf("请输入学号：");
	    scanf("%d",&p->num);
		printf("请输入姓名：");
	    scanf("%s",p->name);
	    printf("请输入班级：");
	    scanf("%s",p->cla);
	    printf("请输入性别：");
	    scanf("%s",p->sex);
	    p->all=0;
	    for(i=0;i<5;i++){
	    	printf("请输入第%d门课程的编号：",i+1);
	    	scanf("%d",&p->les[i].lesnumber);
	    	printf("请输入第%d门课程的名称：",i+1);
	    	scanf("%s",p->les[i].lesname);
	    	printf("请输入第%d门课程的学分：",i+1);
	    	scanf("%lf",&p->les[i].point);
	    	printf("请输入第%d门课程的成绩：",i+1);
	    	scanf("%lf",&p->les[i].score);
	    	p->all+=p->les[i].score;
	    }
	    p->average=p->all/5;
	    p->mark=Mark(p);
	    return 1;
	}
}
STU *Search_name(STU *head,char *name){		     //通过名字搜索学生
	for(;head!=NULL;head=head->next){
		if(!strcmp(head->name,name))return head;
	}
	return NULL;
}
STU *Search_num(STU *head,int num){		   		 //通过学号搜索学生
	for(;head!=NULL;head=head->next){
		if(num==head->num)return head;
	}
	return NULL;
}
int Save(STU *head){							 //保存学生成绩
	FILE *fp;
	int i;
	if((fp=fopen("studata.txt","w"))==NULL){
		return 0;
	}else{
		for(;head!=NULL;head=head->next){
			fprintf(fp,"%d %s %s %s ",head->num,head->name,head->sex,head->cla);
			for(i=0;i<5;i++){
				fprintf(fp,"%d %s %.1f ",head->les[i].lesnumber,head->les[i].lesname,head->les[i].point);
				fprintf(fp,"%.1f ",head->les[i].score);
			}
			fprintf(fp,"%.1f %.1f %.1f\n",head->all,head->average,head->mark);
		}
		fclose(fp);
		return 1;
	}
}
int Lof(FILE *fp){								 //计算文件中学生人数
	char str[201];
	int n;
	for(n=0;fgets(str,201,fp)!=NULL && strcmp(str,"") && strcmp(str,"\n");n++);
	rewind(fp);
	return n;
}
STU *Initialize(){								 //初始化读取文件中的学生
	FILE *fp;
	STU *head=NULL;
	STU *p=NULL;
	int i,n,line;
	if((fp=fopen("studata.txt","r"))==NULL)return NULL;
	else{
		char str[11]={0};
		fgets(str,11,fp);
		if(!strcmp(str,"") || !strcmp(str,"\n"))return NULL;	//可能文件是空的
	}
	rewind(fp);
	line=Lof(fp);
	head=p=Creat(line);							//创建节点为line的单向链表
	for(n=1;n<=line;n++,p=p->next){				//先创建，再往里添信息
		fscanf(fp,"%d%s%s%s",&p->num,p->name,p->sex,p->cla);
		for(i=0;i<5;i++)fscanf(fp,"%d%s%lf%lf",&p->les[i].lesnumber,p->les[i].lesname,&p->les[i].point,&p->les[i].score);
		fscanf(fp,"%lf%lf%lf",&p->all,&p->average,&p->mark);
	}
	head=Sort(head,ALL,FROMBIG);
	fclose(fp);
	return head;
}
int Position(STU *head,STU *p){					 //确定节点在链表的位置
	int n;
	for(n=0;head&&head!=p;head=head->next,n++);
	if(head)return n;
	else return -1;
}
STU *SetPosition(STU *head,int n){				 //将链表移动到指定节点
	int i;
	for(i=0;head&&i<n;i++,head=head->next);
	if(head)return head;
	else return NULL;
}
/*插入法，不改变节点内容，交换节点指针域进行排序*/
STU *Sort(STU *head,int m,int n){                //成绩排序
	STU *p,*p0,*t,*t0;
	int p_pos,p0_pos,t_pos,t0_pos;
	int turn;
	for(p0=head,p=head->next;p!=NULL;p0=p0->next,p=p->next){
		p_pos=Position(head,p);
		p0_pos=Position(head,p0);
		for(t=head,t0=head;t!=p;t=t->next){
			t_pos=Position(head,t);
			t0_pos=Position(head,t0);
			turn=0;
			if(n==0){
				switch(m){
					case 0:if(strcmp(p->name,t->name)>0)turn=1;break;
					case 1:if(p->num>t->num)turn=1;break;
					case 2:if(p->all>t->all)turn=1;break;
					case 3:if(p->mark>t->mark)turn=1;break;
					case 4:if(p->les[0].score>t->les[0].score)turn=1;break;
					case 5:if(p->les[1].score>t->les[1].score)turn=1;break;
					case 6:if(p->les[2].score>t->les[2].score)turn=1;break;
					case 7:if(p->les[3].score>t->les[3].score)turn=1;break;
					case 8:if(p->les[4].score>t->les[4].score)turn=1;break;
				}
				if(turn==1){
					p0->next=p->next;
					p->next=t;
					if(t==head)head=p;
					else t0->next=p;
					p=p0;
				}
			}else{
				switch(m){
					case 0:if(strcmp(p->name,t->name)<0)turn=1;break;
					case 1:if(p->num<t->num)turn=1;break;
					case 2:if(p->all<t->all)turn=1;break;
					case 3:if(p->mark<t->mark)turn=1;break;
					case 4:if(p->les[0].score<t->les[0].score)turn=1;break;
					case 5:if(p->les[1].score<t->les[1].score)turn=1;break;
					case 6:if(p->les[2].score<t->les[2].score)turn=1;break;
					case 7:if(p->les[3].score<t->les[3].score)turn=1;break;
					case 8:if(p->les[4].score<t->les[4].score)turn=1;break;
				}
				if(turn==1){
					p0->next=p->next;
					p->next=t;
					if(t==head)head=p;
					else t0->next=p;
					p=p0;
				}
			}
			p=SetPosition(head,p_pos);
			p0=SetPosition(head,p0_pos);
			t=SetPosition(head,t_pos);
			t0=SetPosition(head,t0_pos);
			if(t!=head)t0=t0->next;
		}
	}
	return head;
}
STU *Creat(int n){                  			 //创建链表
	STU *pf,*head,*pb;
	int i;
	for(i=0;i<n;i++){
		pb=(STU *)malloc(sizeof(STU));
		if(i==0)pf=head=pb;
		else pf->next=pb;
		pf=pb;
	}
	pb->next=NULL;
	return head;
}
STU *Connect(STU *head,STU *end){                //连接两个链表
	STU *p=head;
	for(;head->next!=NULL;head=head->next);
	head->next=end;
	return p;
}
double Mark(STU *p){							 //计算绩点
	double mark_all=0;
	double mark=0;
	double point_all=0;
	int i;
    for(i=0;i<5;i++){
    	mark=(p->les[i].score-50)/10.0*p->les[i].point;
    	point_all+=p->les[i].point;
    	mark_all+=mark;
    }
    mark_all/=point_all;
    return mark_all;
}
STU *Input(){              			 			 //输入学生成绩
	STU *head;
	int i;
	head=Creat(1);
	printf("请输入学号(输入0结束录入)：");
    scanf("%d",&head->num);
    if(head->num==0){
    	free(head);
    	head=NULL;
    	return NULL;
    }
    printf("请输入姓名：");
    scanf("%s",head->name);
    printf("请输入班级：");
    scanf("%s",head->cla);
    printf("请输入性别：");
    scanf("%s",head->sex);
    head->all=0;
    for(i=0;i<5;i++){
	    printf("请输入第%d门课程的编号：",i+1);
    	scanf("%d",&head->les[i].lesnumber);
    	printf("请输入第%d门课程的名称：",i+1);
    	scanf("%s",head->les[i].lesname);
    	printf("请输入第%d门课程的学分：",i+1);
    	scanf("%lf",&head->les[i].point);
    	printf("请输入第%d门课程的成绩：",i+1);
    	scanf("%lf",&head->les[i].score);
    	head->all+=head->les[i].score;
    }
    head->average=head->all/5;
    head->mark=Mark(head);
	return head;
}
void HideCursor(){								 //隐藏光标
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void PutCursor(){								 //显示光标
	CONSOLE_CURSOR_INFO cursor_info={1,1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void GotoXy(int x,int y){						 //将光标移动到(X,Y)
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void GetXy(int *X,int *Y,int x1,int x2,int y1,int y2){ //获取在限定范围内鼠标点击的坐标
	HANDLE hInput;                              //获取标准输入设备句柄
    INPUT_RECORD inRec;                         //返回数据记录
    DWORD res;                                  //返回已读取的记录数
    int x=-1,y=-1;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	do{
		ReadConsoleInput(hInput, &inRec, 1, &res);
		if(inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED){
			x=(int)inRec.Event.MouseEvent.dwMousePosition.X;
			y=(int)inRec.Event.MouseEvent.dwMousePosition.Y;
		}
	}while(!(x>=x1&&x<=x2&&y>=y1&&y<=y2));
	*X=x;
	*Y=y;
}
void Clear(int x,int y,int line){				 //清除line行的内容后将坐标返回(x,y)
	int i;
	for(i=0;i<line*80-1;printf(" "),i++);
	GotoXy(x,y);
}
int main(){
    int X=0,Y=0;								//鼠标左键单击的坐标(X,Y)
    int turn=0;									//检验是否登录或注册成功的开关
    int admin=0;								//检验用户是以教师或学生身份登录的开关
    HideCursor();
    PrintLogin();
    while(1){
    	if(admin==0){
			while(1){									//登录界面的操作
				GetXy(&X,&Y,38,45,4,8);
				PutCursor();
				turn=0;
				switch(Y){
					case 4:turn=RegisterTea();break;
					case 5:turn=LoginTea();break;
					case 6:turn=RegisterStu();break;
					case 7:turn=LoginStu();break;
					case 8:GotoXy(28,11);return 0;
				}
				HideCursor();
				if(turn==1&&(Y==5||Y==7)){
						if(Y==5)admin=1;
						if(Y==7)admin=2;
						printf("                             (按任意键进入操作菜单)");
						getch();
						break;
				}else{
					GotoXy(33,11);
					printf("接下来你希望：");
					GotoXy(15,12);
					printf("        1.返回登录菜单     2.退出管理系统");
					do{
						GetXy(&X,&Y,25,55,12,12);
					}while(X>=37&&X<=44);
					if(X>=25&&X<=36){
						GotoXy(0,10);
						Clear(0,10,10);
					}else{
						GotoXy(28,11);
						return 0;
					}
				}
			}
		}else if(admin==1){
			int ismodify=0;
			STU *head=Initialize();
			GotoXy(0,0);
			PrintMenuTea();
			Clear(0,10,15);
			while(1){
				do{
					GetXy(&X,&Y,28,55,4,8);
				}while((X>=36&&X<=47)||(Y==8&&X>=48&&X<=55));
				if(Y==4){
					if(X/10==2||X/10==3){
						STU *p=NULL;
						int t=Count(head);
						int item=t;
						PutCursor();
						do{
							if(p!=NULL){
								GotoXy(0,10);
								Clear(0,10,24);
							}
							p=Input();
							if(t==0){
								head=p;
								t=Count(head);
							}else Connect(head,p);
						}while(p!=NULL);
						HideCursor();
						if(t!=item){
							ismodify=1;
							GotoXy(25,20);
							printf("      学生信息录入成功！");
							GotoXy(25,21);
							printf("    (按任意键返回操作菜单)");

						}else{
							printf("                               学生信息录入失败！\n");
							printf("                             (按任意键返回操作菜单)");
						}
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);
					}else{
						char number[11];
						int t;
						GotoXy(27,11);
						printf("请选择通过学号或姓名修改信息：");
						GotoXy(27,12);
						printf("    1.学号        2.姓名\n");
						do{
							GetXy(&X,&Y,33,50,12,12);
						}while(X>=37&&X<=46);
						PutCursor();;
						if(X>=33&&X<=36){
							printf("请输入学号：");
							scanf("%s",number);
							t=Modify(head,NUMBER,number);
						}else{
							printf("请输入姓名：");
							scanf("%s",number);
							t=Modify(head,NAME,number);
						}
						HideCursor();
						if(t==0){
							printf("                         找不到该学生的信息，无法修改！\n");
							printf("                             (按任意键返回操作菜单)");					
						}
						else{
							ismodify=1;
							GotoXy(25,23);
							printf("      学生信息修改成功！");
							GotoXy(25,24);
							printf("    (按任意键返回操作菜单)");
						}
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);	
					}
				}else if(Y==5){
					char number[11];
					int t=0;
					if(X/10==2||X/10==3){
						GotoXy(27,11);
						printf("请选择通过学号或姓名删除学生：");
						GotoXy(27,12);
						printf("    1.学号        2.姓名\n");
						do{
							GetXy(&X,&Y,33,50,12,12);
						}while(X>=37&&X<=46);
						PutCursor();;
						if(X>=33&&X<=36){
							printf("请输入学号：");
							scanf("%s",number);
							head=Delete(head,NUMBER,number,&t);
						}else{
							printf("请输入姓名：");
							scanf("%s",number);
							head=Delete(head,NAME,number,&t);
						}
						HideCursor();
						if(t==0){
							printf("                         找不到该学生的信息，无法删除！\n");
							printf("                             (按任意键返回操作菜单)");					
						}
						else{
							ismodify=1;
							printf("                               该学生信息已删除！\n");
							printf("                             (按任意键返回操作菜单)");
						}
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);	
					}else{
						GotoXy(32,11);
						printf("请选择查询方式：");
						GotoXy(16,12);
						printf("1.查询个人成绩  2.按分数段查询  3.查询不及格学生\n");
						do{
							GetXy(&X,&Y,18,63,12,12);
						}while(X==30||X==31||X==46||X==47);
						if(X/10==1||X/10==2){
							GotoXy(27,14);
							printf("请选择通过学号或姓名查询学生：");
							GotoXy(27,15);
							printf("    1.学号        2.姓名\n");
							do{
								GetXy(&X,&Y,33,50,15,15);
							}while(X>=37&&X<=46);
							PutCursor();;
							if(X>=33&&X<=36){
								printf("请输入学号：");
								scanf("%s",number);
								DisplayOne(head,NUMBER,number);
							}else{
								printf("请输入姓名：");
								scanf("%s",number);
								DisplayOne(head,NAME,number);
							}
							HideCursor();
						}else if(X/10==3||X/10==4){
							double low,high;
							PutCursor();
							printf("请输入分数下限：");
							scanf("%lf",&low);
							printf("请输入分数上限：");
							scanf("%lf",&high);
							HideCursor();
							DisplayGrade(head,low,high);
						}else{
							DisplayFail(head);
						}
						printf("                             (按任意键返回操作菜单)");
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);
					}
				}else if(Y==6){
					if(X/10==2||X/10==3){
						int m,n;
						PrintMenuSort();
						do{
							GetXy(&X,&Y,28,54,14,18);
						}while((X>=35&&X<=47)||(Y==18&&X>=48&&X<=54));
						if(X>=28&&X<=34){
							switch(Y){
								case 14:m=NUMBER;break;
								case 15:m=ALL;break;
								case 16:m=COU1;break;
								case 17:m=COU3;break;
								case 18:m=COU5;break;
							}
						}else{
							switch(Y){
								case 14:m=NAME;break;
								case 15:m=MARK;break;
								case 16:m=COU2;break;
								case 17:m=COU4;break;
							}
						}
						PrintMenuSort2();
						do{
							GetXy(&X,&Y,28,55,24,24);
						}while(X>=36&&X<=47);
						switch(X/10){
							case 2:
							case 3:n=FROMSMALL;break;
							case 4:
							case 5:n=FROMBIG;break;
						}
						if(head){
							head=Sort(head,m,n);
							ismodify=1;
							printf("                    学生信息排序完毕！是否打印所有学生信息？\n");
							printf("                                  是(Y)  否(N)\n");
							do{
								GetXy(&X,&Y,34,45,27,27);
							}while(X==39||X==40);
							if(X>=34&&X<=38){
								DisplayAll(head);
								printf("                             (按任意键返回操作菜单)");
								getch();
							}
						}else{
							printf("────────────────────────────────────────");
							printf("                                  无学生记录！                                  ");
							printf("────────────────────────────────────────");
							printf("                             (按任意键返回操作菜单)");
							getch();
						}
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);
					}else{
						GotoXy(32,11);
						printf("请选择显示方式：");
						GotoXy(27,12);
						printf("1.显示所有      2.按班显示\n");
						do{
							GetXy(&X,&Y,29,52,12,12);
						}while(X>=37&&X<=44);
						if(X>=29&&X<=36){
							DisplayAll(head);
						}else{
							char cla[11];
							PutCursor();
							printf("请输入班级名称:");
							scanf("%s",cla);
							HideCursor();
							DisplayCla(head,cla);
						}
						printf("                             (按任意键返回操作菜单)");
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,14);
					}
				}else if(Y==7){
					if(X/10==2||X/10==3){
						int t;
						t=Save(head);
						if(t==1){
							ismodify=0;
							printf("\n                               学生信息保存成功！\n");
						}else{
							printf("\n                               学生信息保存失败！\n");
						}
						printf("                             (按任意键返回操作菜单)");
						getch();
						GotoXy(0,0);
						PrintMenuTea();
						Clear(0,10,15);
					}else{
						admin=0;
						if(ismodify==1){
							GotoXy(0,11);
							printf("                  您已对学生信息做出修改，请问是否保存后退出？\n");
							printf("                                  是(Y)  否(N)\n");
							do{
								GetXy(&X,&Y,34,45,12,12);
							}while(X==39||X==40);
							if(X>=34&&X<=38)Save(head);
						}
						GotoXy(0,11);
						Clear(0,11,2);
						printf("                             (按任意键返回登录菜单)");
						getch();
						GotoXy(0,0);
						Clear(0,0,20);
						PrintLogin();
						break;
					}
				}else{
					if(ismodify==1){
						GotoXy(0,11);
						printf("                  您已对学生信息做出修改，请问是否保存后退出？\n");
						printf("                                  是(Y)  否(N)\n");
						do{
							GetXy(&X,&Y,34,45,12,12);
						}while(X==39||X==40);
						if(X>=34&&X<=38)Save(head);
					}
					GotoXy(0,11);
					Clear(28,11,2);
					return 0;
				}
			}
		}else if(admin==2){
			STU *head=Initialize();
			GotoXy(0,0);
			PrintMenuStu();
			Clear(0,10,8);
			while(1){
				do{
					GetXy(&X,&Y,28,55,4,5);
				}while((X>=36&&X<=47)||(Y==5&&X>=48&&X<=55));
				if(Y==4){
					if(X/10==2||X/10==3){
						char number[11];
						GotoXy(27,8);
						printf("请选择通过学号或姓名查询学生：");
						GotoXy(27,9);
						printf("    1.学号        2.姓名\n");
						do{
							GetXy(&X,&Y,33,50,9,9);
						}while(X>=37&&X<=46);
						PutCursor();;
						if(X>=33&&X<=36){
							printf("请输入学号：");
							scanf("%s",number);
							DisplayOne(head,NUMBER,number);
						}else{
							printf("请输入姓名：");
							scanf("%s",number);
							DisplayOne(head,NAME,number);
						}
						HideCursor();
						printf("                             (按任意键返回操作菜单)");
						getch();
						GotoXy(0,0);
						PrintMenuStu();
						Clear(0,10,18);
					}else{
						admin=0;
						GotoXy(0,11);
						printf("                             (按任意键返回登录菜单)");
						getch();
						GotoXy(0,0);
						Clear(0,0,21);
						PrintLogin();
						break;
					}
				}
				else{
					GotoXy(0,11);
					Clear(28,11,2);
					return 0;
				}
			}
		}
	}
	return 0;
}
