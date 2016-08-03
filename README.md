学生成绩管理系统
========
__注册密码：2014052421__

* `studata.txt`：学生数据文件，保存学生姓名学号成绩等信息
* `admintea.txt`：教师登录文件，保存教师账号和密码
* `adminstu.txt`：学生登录文件，保存学生账号和密码

学号是`int`而不是`char[]` 
正确返回1，错误返回0 
ASCII编码，不能UTF-8编码 
会判断文件开头和末尾的空行，不能判断中间的空行 
main函数太杂太长 
鼠标操作,不能键盘操作 
二进制文件

```c
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
```
