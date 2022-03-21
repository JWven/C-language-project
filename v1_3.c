// ************************************** 学生管理系统 **************************************
// 作者：JWven
// 版本：v1.3
// 时间：2022.3.20  20:50  星期日
// 说明：修复了少量bug，添加了文件存储模块;将链表设置为全局变量，减少函数之间参数的传递，直接对全局
//       变量进行操作;创建了头文件
// 待优化：
//        1.成绩统计：年级总分最高，单科最高，单科平均，学生排名；班级总分最高、排名，单科最高、平均、
//                    排名
//        2.增强人机交互功能
//        3.代码优化
//        4.算法优化(排序算法，搜索算法)
//        5.非法输入处理 
// *****************************************************************************************

// 头文件
#include "stadef.h"

// 模块一：文件读写
/*********************************** 文件读入函数 ***********************************/  
void read_file(char * file_name)  
{
    FILE * fp = NULL;                               // 文件指针
    char data_temp[10] = {'\0'};                    // 存储一行中某个数据
    char data_row[100] = {'\0'};                    // 存储一行的数据
    int i,j;                                        // 循环中计数器
    
    printf("文件加载中.......\n");
    // 打开文件
    if ((fp = fopen(file_name, "r")) == NULL)       // 文件打开失败
    {
        printf("Can not open file!\n");
        exit(0);
    }

    // 创建链表
    Student * head_r;                               // 头指针
    Student * p1, * p2;                             // 移动结点
    n = 0;                                          // 结点个数（即数据条数）
    p1 = p2 = (Student *)malloc(LEN);               // 申请内存

    // 从文件中读取数据，并将其存放入链表中
    fgets(data_row, 100, fp);                       // 忽略第一行（第一行为数据标签）
    fgets(data_row, 100, fp);                       // 读入一行，放到数组data_row中
    data_input(p1,data_row);                        // 将该行数据存入链表中

    head = NULL;                                    // 头指针指向NULL
    while (!feof(fp))                               // 未到文件结尾，继续读取
    {   
        n = n + 1;                                  // 结点数加一（数据条数加一）
        if (n == 1)                                 // 如果是第一个结点
            head = p1;                              // 头指针指向第一个结点
        else                                        // 读到第一个之后的结点
            p2->next = p1;                          // 前一个结点指向当前结点
        
        p2 = p1;                                    // 把当前结点赋给p2
        p1 = (Student *)malloc(LEN);                // 开辟下一个新结点
        fgets(data_row, 100, fp);                   // 读入新的一行，放到数组中
        data_input(p1,data_row);                    // 将该行数据存入链表欧中
    }
    p2->next = NULL;                                // 最后一个结点指向NULL
    fclose(fp);                                     // 关闭文件
    printf("文件加载完成！\n");
}

/*********************************** 数据写入函数 ***********************************/ 
void data_input(Student * p1, char data_row[100])
{   
    char data_temp[10] = {'\0'};                    // 存储一行中某个数据
    int i, j;

    for (i = 0; data_row[i] != ','; i++)            // 将名字写入链表
    {
        p1->name[i] = data_row[i];
        p1->name[i+1] = '\0';
    }
    i++;
    /************ 依次写入数字 ************/
    for(j = 0;data_row[i] != ','; j++, i++)         // 依次读入，直到遇到逗号(csv文件格式所决定)
        data_temp[j] = data_row[i];
    p1->continue_drop = atoi(data_temp);
    for (int k = j; k >= 0; k--)                    // data_temp数组需置空，因为atoi函数会将数组里的所有数字一起转换(详细见文档)
        data_temp[k] = '\0';
    i++;                                            // i++跳过逗号

    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->student_id = atol(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;
    
    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->gender = atoi(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;

    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->grade= atoi(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;

    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->class = atoi(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;
    
    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->chinese_marks = atof(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;

    for(j = 0;data_row[i] != ','; j++, i++)       
        data_temp[j] = data_row[i];
    p1->english_marks = atof(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
    i++;

    for(j = 0;data_row[i] != '\n'; j++, i++)       
        data_temp[j] = data_row[i];
    p1->math_marks = atof(data_temp);
    for (int k = j; k >= 0; k--)
        data_temp[k] = '\0';
}

/*********************************** 写出文件函数 ***********************************/
void write_file(char * filename)
{
    FILE * fp;
    // 首行数据标签
    char * row = "name,continue_drop,student_id,gender, grade,class,Chinese_marks,english_marks,math_marks\n";
    Student * p = head;
    if ((fp = fopen(filename, "w")) == NULL)        // 文件打开失败
    {
        printf("Open the file error!\n");
        exit(0);
    }    
    fputs(row,fp);                                  // 输出标签行

    while (p != NULL)                               // 按行保存数据
    {
        for (int i = 0; p->name[i] != '\0'; i++)    // 保存名字
            fprintf(fp,"%c",p->name[i]);
        // 保存数值类数据(实际在文件中以字符形式存储)
        fprintf(fp,",%d,%ld,%d,%d,%d,%.2f,%.2f,%.2f\n",p->continue_drop,p->student_id,p->gender,
                p->grade,p->class,p->chinese_marks,p->english_marks,p->math_marks);
        p = p->next;                                // 移动结点
    }
    fprintf(fp,"\n");                               // 在文件末尾添加换行符，方便如果下次需要读入该文件
    printf("Save successfully!\n");
    fclose(fp);
}


// 模块二：辅助函数
/*********************************** 释放链表函数 ***********************************/  
void disposal_LinkList(Student * headNode)
{
    Student * nextNode;                         // 下一个结点
    Student * curNode;                          // 当前结点
	if (headNode == NULL)                       // 如果为空表
	{
        return;
	}
	//清空链表,是不清空头节点的，因此从第一个有数据的节点开始释放
	curNode = headNode->next;                   // 当前结点指向第一个结点
	while (curNode != NULL)                     // 未到达链表尾，继续释放
	{
		nextNode = curNode->next;               //先存下下一个节点的位置
		free(curNode);                          // 释放当前结点
		curNode = nextNode;	                    // 当前结点指向下一个结点
	}
	free(headNode);                             //释放头结点
	headNode = NULL;	                        //头结点指针置空
}

/*********************************** 插入结点函数 ***********************************/
void insert(Student * stud)
{
    // 参数：需要插入的结点
    Student * p0, * p1, *p2;            // 辅助指针
    p1 = head;                          // p1指向第一个结点
    p0 = stud;                          // p0指向需要插入的新结点

    if (head == NULL)                   // 如果是空链表，则将这个结点作为第一个结点
    {
        head = p0;
        p0->next = NULL;
    }
    else                                // 非空链表
    {
        while ((p0->student_id > p1->student_id) && (p1->next != NULL))    // 还没到达结点位置或没到达链尾
        {
            p2 = p1;                    // 保存当前结点
            p1 = p1->next;              // 继续搜索下一个结点
        }

        if (p0->student_id <= p1->student_id)         // 找到了
        {
            if (p1 == head)             // 插入到第一个结点之前
                head = p0;
            else
                p2->next = p0;          // 插入p1之前，p2之后

            p0->next = p1;              // p0(新结点)指向p1
        }
        else                            // 没找到(就是插到尾结点之后)
        {
            p1->next = p0;             
            p0->next = NULL;
        }
    }
    n = n + 1;                          // 结点数+1
}

/********************************* 链表排序(按学号) *********************************/
void sort()
{
    // 中间变量
    char name_t[7];                      // 名字
    int continue_drop_t;                 // 是否在读
    long student_id_t;                   // 学号
    int gender_t;                        // 性别
    int grade_t;                         // 年级
    int class_t;                         // 班别
    float chinese_marks_t;               // 语文成绩
    float english_marks_t;               // 英语成绩
    float math_marks_t;                  // 数学成绩

    Student * p1, * p2;                  // 移动结点

    // 排序
    for (int i = 0; i < n-1; i++)
    {
        p2 = head;
        p1 = p2->next;
        for (int j = 0; j < n-1; j++)
        {
            if (p2->student_id > p1->student_id)    // 升序排列
            {
                // 只将两结点的数据域交换，还有其他的结点交换方法，如交换整个结点
                for (int k = 0; k < 7; k++)
                    name_t[k] = p1->name[k];
                continue_drop_t = p1->continue_drop;
                student_id_t = p1->student_id;
                gender_t = p1->gender;
                grade_t = p1->grade;
                class_t = p1->class;
                chinese_marks_t = p1->chinese_marks;
                english_marks_t = p1->english_marks;
                math_marks_t = p1->math_marks;
                
                for (int k = 0; k < 7; k++)
                    p1->name[k] = p2->name[k];
                p1->continue_drop = p2->continue_drop;
                p1->student_id = p2->student_id;
                p1->gender = p2->gender;
                p1->grade = p2->grade;
                p1->class = p2->class;
                p1->chinese_marks = p2->chinese_marks;
                p1->english_marks = p2->english_marks;
                p1->math_marks = p2->math_marks;

                for (int k = 0; k < 7; k++)
                    p2->name[k] = name_t[k];
                p2->continue_drop = continue_drop_t;
                p2->student_id = student_id_t;
                p2->gender = gender_t;
                p2->grade = grade_t;
                p2->class = class_t;
                p2->chinese_marks = chinese_marks_t;
                p2->english_marks = english_marks_t;
                p2->math_marks = math_marks_t;
            }
            p2 = p1;
            p1 = p1->next;
        }
    }

    // return head;
}


// 模块三：基本功能
/*********************************** 添加学生函数 ***********************************/
void add()
{
    int length = 0;                     // 存储名字数组的长度
    Student * new;                      // 新结点
    char data_row[100] = {'\0'};        // 存储行数据，即新结点数据
    
    printf("\n输入新添加的学生信息，用','分隔：(输入0退出)\n");
    printf("格式：name, continue_drop, student_id, gender, grade, class, Chinese_marks, english_marks, math_marks\n");
    gets(data_row);                     // 输入一行，注意这里不读取换行符
    length = strlen(data_row);
    data_row[length] = '\n';            // 在数组中数据的后面添加换行符，data_input函数最后需要根据换行符判断数据结尾
    while (data_row[0] != '0')
    {   
        new = (Student *) malloc(LEN);  // 申请内存
        data_input(new, data_row);      // 将字符数据存入结点
        insert(new);                    // 将新结点有序插入到链表中
        printf("添加成功！\n");
        print_personal(new);
        printf("\n输入新添加的学生信息，用','分隔：(输入0退出)\n");
        printf("格式：name, continue_drop, student_id, gender, grade, class, Chinese_marks, english_marks, math_marks\n");
        gets(data_row);
        length = strlen(data_row);
        data_row[length] = '\n';
    }
}

/*********************************** 删除学生函数 ***********************************/ 
void clear()
{
    long id;                             // 学生ID
    Student * p1, *p2;                   // 移动指针
    char confirm = 'Y';
    printf("请输入需要删除学生的学号(输入0退出)：");
    scanf("%ld", &id);
    getchar();                           // 丢弃换行符

    while (id != 0)                      // 当输入不等于0
    {
        if (head == NULL)                // 如果是空表
        {
            printf("\nlist null!\n");
            return;
        }
        p1 = head;                       // p1指向第一个结点
        while (id != p1->student_id && p1->next != NULL)      // 开始搜索，直到找到或者到达链表尾
        {
            p2 = p1;        
            p1 = p1->next;              // p2指向上一个结点，防止其丢失。 p1指向下一个结点，继续搜索
        }
        if (id == p1->student_id)       // 找到了
        {
            printf("将要删除：\n");
            print_personal(p1);         // 打印出该学生信息
            printf("是否确认删除该学生信息？(Y/N)\n");
            confirm = getchar();        // 输入Y or N
            getchar();
            if (confirm == 'Y')         // 确认删除
            {
                if (p1 == head)         // 如果找到的是第一个结点，则删除头结点
                    head = p1->next;    // 将头结点指向第二个结点，丢弃第一个结点
                else                    
                    p2->next = p1->next;// 丢弃p1这个结点：其之前的结点（即p2）指向p1之后一个结点

                printf("删除成功！\n");
                n = n - 1;              // 结点数-1
            }
            else                        // 取消删除
                printf("取消删除\n");
        }
        else                            // 没有找到
            printf("student:%ld not benn found!\n", id);
        
        printf("请输入需要删除学生的学号(输入0退出)：");
        scanf("%ld", &id);
        getchar();                      // 丢弃换行符
    }
}

/*********************************** 查找学生函数 ***********************************/  
void seek()
{
    long id;                            // 学生ID
    Student * p1, *p2;                  // 移动结点
    
    printf("请输入需要查找/修改学生的学号(输入0退出)：");
    scanf("%ld", &id);
    getchar();                          // 丢弃换行符

    while (id != 0)                     // 当输入不为0
    {
        if (head == NULL)               // 如果是空表
        {
            printf("\nlist null!\n");
            return;                     // 返回空指针
        }

        p1 = head;                      // p1指向第一个结点
        while (id != p1->student_id && p1->next != NULL)      // 开始搜索，直到到达链表尾
        {
            p2 = p1;        
            p1 = p1->next;              // p2指向上一个结点，防止其丢失。 p1指向下一个结点，继续搜索
        }

        if (id == p1->student_id)       // 找到了
        {
            print_personal(p1);         // 打印该学生信息
        }
        else                            // 没有找到
        {
            printf("student:%ld was not be found!\n", id);
            p1 = NULL;                  // p1置空，不直接返回，因为还要继续输入
        }
        printf("请输入需要查找/修改学生的学号(输入0退出)：");
        scanf("%ld", &id);
        getchar();                      // 丢弃换行符

    }
}

/*********************************** 修改信息函数 ***********************************/
void change()
{
    Student * p, * p2;                                  // 移动结点
    char ch, n[7];                                      // 选项，存储名字的数组
    char data_row[100] = {'\0'};                        // 储存一行数据
    long id = 0;                                        // 学生ID
    int length;
    printf("请输入需要查找/修改学生的学号(输入0退出)：");
    scanf("%ld", &id);
    getchar();                                          // 丢弃换行符
    while (id != 0)                                     // 当输入不为0
    {
        if (head == NULL)                               // 如果是空表
        {
            printf("\nlist null!\n");
            return;                                     // 返回空指针
        }

        p = head;                                       // p1指向第一个结点
        while (id != p->student_id && p->next != NULL)  // 开始搜索，直到到达链表尾
        {
            p2 = p;        
            p = p->next;                                // p2指向上一个结点，防止其丢失。 p1指向下一个结点，继续搜索
        }

        if (id == p->student_id)                        // 找到了
        {
            printf("你将要修改的学生：\n");
            print_personal(p);                          // 打印需要修改的学生信息
        }
        else                                            // 没有找到
        {
            printf("student:%ld was not be found!\n", id);
            goto Enter;                                 // 跳过下面过程重新输入学生ID
        }
        
        printf("\n***************** 请选择需要修改的项目 *****************\n");
        printf(" A: 名字       B: 性别       C: 学号       D: 在校状态\n");
        printf(" E: 年级       F: 班别       G: 语文成绩    H：英语成绩\n");
        printf(" I: 数学成绩    J:修改所有信息              0: 退出修改\n");
        printf("******************************************************\n");
        scanf("%c", &ch);
        getchar();
        while (ch != '0')
        {
            switch (ch)                                 // 选项
            {
                case 'A':
                    printf("将名字修改为：");
                    scanf("%s", n);
                    getchar();                          // 丢弃换行符，后面每输入一次都要紧跟丢弃
                    for (int i = 0; i < 7; i++) 
                        p->name[i] = n[i];
                    printf("修改完成！\n");
                    break;
                case 'B':
                    printf("将性别修改为：");
                    scanf("%d", &p->gender);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'C':
                    printf("将学号修改为：");
                    scanf("%ld", &p->student_id);
                    getchar();
                    sort();                     // 如果学号发生变化，则链表重新排序
                    printf("修改完成！\n");
                    break;
                case 'D':
                    printf("将在校状态修改为：");
                    scanf("%d", &p->continue_drop);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'E':
                    printf("将年级修改为：");
                    scanf("%d", &p->grade);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'F':
                    printf("将班级修改为：");
                    scanf("%d", &p->class);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'G':
                    printf("将语文成绩修改为：");
                    scanf("%f", &p->chinese_marks);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'H':
                    printf("将英语修改为：");
                    scanf("%f", &p->english_marks);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'I':
                    printf("将数学成绩修改为：");
                    scanf("%f", &p->math_marks);
                    getchar();
                    printf("修改完成！\n");
                    break;
                case 'J':
                    printf("依次输入各项数据,用逗号分隔：\n");
                    printf("格式：name,continue_drop,student_id,gender, grade,class,Chinese_marks,english_marks,math_marks\n");
                    scanf("%s", data_row);           
                    getchar();
                    length = strlen(data_row);
                    data_row[length] = '\n';
                    data_input(p, data_row);
                    sort();                  // 如果学号发生变化，则链表重新排序
                    printf("修改完成！\n");
                    break;
                default:
                    break;
            }  
        printf("\n***************** 请选择需要修改的项目 *****************\n");
        printf(" A: 名字       B: 性别       C: 学号       D: 在校状态\n");
        printf(" E: 年级       F: 班别       G: 语文成绩    H：英语成绩\n");
        printf(" I: 数学成绩    J:修改所有信息              0: 退出修改\n");
        printf("******************************************************\n");
        scanf("%c", &ch);
        getchar();
        }
Enter:  printf("请输入需要查找/修改学生的学号(输入0退出)：");
        scanf("%ld", &id);
        getchar();
    }


}


// 模块四：显示信息
/********************************* 显示所有学生函数 *********************************/  
void print()           
{  
    Student * p;                            // 移动结点
    printf("There are %5d datas:\n",n);
    printf("Name  student_id  continue_drop  gender  grade  class  chinese_marks  english_marks  math_marks\n");
    p = head;                               // 移动结点指向头结点
    if (p != NULL)                          // 如果链表非空
    {
        do
        {  
            /* 为了打印对齐，这里对两字名字与三字名字进行区分，暂时不考虑四字名字，同时不再将 0或 1转化为yes or no */
            
            if (p->name[5] != '\0')         // 三字名字
            {
                printf("%4s %8ld", p->name, p->student_id);
                p->continue_drop?printf("       YES"):printf("       NO ");
                p->gender?printf("         MALE  "):printf("        FEMALE ");
                printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                printf("\n");
            }
            else                            // 两字名字
            {
                printf("%4s %10ld", p->name,p->student_id);
                p->continue_drop?printf("       YES"):printf("       NO ");
                p->gender?printf("         MALE  "):printf("        FEMALE ");
                printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                printf("\n");
            }
            p = p->next;                    // 移动结点指向下一个结点
        }while (p != NULL);                 // 未达到链表尾则继续打印
    }
    else                                    // 如果为空链表
        printf("The student was not found!\n");
}

/******************************* 打印单个学生信息函数 ********************************/ 
void print_personal(Student * p)
{
    printf("Student ID: %ld\n", p->student_id);
    printf("Name: %s\n", p->name);
    // 判断性别
    if (p->gender == 0)
        printf("Gender: male\n");
    else
        printf("Gender: female\n");
    printf("Class: class%d grade%d\n", p->class, p->grade);
    // 判断在读状态
    if (p->continue_drop == 0)
        printf("Whether the student is in school: NO\n");
    else
        printf("Whether the student is in school: YES\n");
    // 成绩
    printf("Chinese score: %.2f\n", p->chinese_marks);
    printf("Math score: %.2f\n", p->math_marks);
    printf("English score: %.2f\n", p->english_marks);
}

/******************************* 打印单个班级学生函数 ********************************/ 
void print_class()
{
    Student * p;
    int grade;
    int class;
    printf("Enter the class:(grade,class)  ");
    scanf("%d,%d", &grade,&class);
    getchar();
    p= head;
    printf("\n\t\t****************** Class %d Grade %d ******************\n", class, grade);
    printf("Name  student_id  continue_drop  gender  grade  class  chinese_marks  english_marks  math_marks\n");
    if (p != NULL)
    {
        do
        {  
            // 遍历到需要打印的班级之后时，直接退出
            // if (p->grade > grade || p->class > class)   
            //     break;       (后来发现这样不行，会产生bug，如果前面同时修改过学生的学号，重新排序后可能导致
            // 班级和年级并非是有序排序，故需要遍历整个链表，而不能只遍历前半部分)

            if (p->grade == grade && p->class == class)            // 遍历整个链表
            {
                /* 为了打印对齐，这里对两字名字与三字名字进行区分，暂时不考虑四字名字，同时不再将 0或 1转化为yes or no */
                
                if (p->name[5] != '\0')         // 三字名字
                {
                    printf("%4s %8ld", p->name, p->student_id);
                    p->continue_drop?printf("       YES"):printf("       NO ");
                    p->gender?printf("         MALE  "):printf("        FEMALE ");
                    printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                    printf("\n");
                }
                else                            // 两字名字
                {
                    printf("%4s %10ld", p->name,p->student_id);
                    p->continue_drop?printf("       YES"):printf("       NO ");
                    p->gender?printf("         MALE  "):printf("        FEMALE ");
                    printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                    printf("\n");
                }
            }
            p = p->next;                        // 移动结点指向下一个结点
        }while (p != NULL);                     // 未达到链表尾则继续打印
    }
    else                                        // 如果为空链表
        printf("Error!\n");
}

/******************************* 打印单个年级学生函数 ********************************/ 
void print_grade()
{
    Student * p;
    int grade;
    printf("Enter the grade:");
    scanf("%d", &grade);
    getchar();
    p= head;
    printf("\n\t\t********************** Grade %d **********************\n", grade);
    printf("Name  student_id  continue_drop  gender  grade  class  chinese_marks  english_marks  math_marks\n");
    if (p != NULL)                          // 非空链表
    {
        do
        {  
            // if (p->grade > grade)        // 不用的原因同 print_class
            //     break;
            if (p->grade == grade)
            {
                /* 为了打印对齐，这里对两字名字与三字名字进行区分，暂时不考虑四字名字，同时不再将 0或 1转化为yes or no */
                
                if (p->name[5] != '\0')     // 三字名字
                {
                    printf("%4s %8ld", p->name, p->student_id);
                    p->continue_drop?printf("       YES"):printf("       NO ");
                    p->gender?printf("         MALE  "):printf("        FEMALE ");
                    printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                    printf("\n");
                }
                else                        // 两字名字
                {
                    printf("%4s %10ld", p->name,p->student_id);
                    p->continue_drop?printf("       YES"):printf("       NO ");
                    p->gender?printf("         MALE  "):printf("        FEMALE ");
                    printf("%5d %5d %11.2f %15.2f %12.2f", p->grade, p->class, p->chinese_marks, p->english_marks, p->math_marks);
                    printf("\n");
                }
            }
            p = p->next;                    // 移动结点指向下一个结点
        }while (p != NULL);                 // 未达到链表尾则继续打印
    }
    else                                    // 如果为空链表
        printf("Error!\n");
}



/************************************ 用户接口 *************************************/
void user()
{
    char choose;             // 存储用户选项
    char choose_a, choose_b;
    char *filename;

    printf("******************** 选择功能 ********************\n");
    printf("   A: 显示学生信息    B: 查找学生    C: 添加学生    \n");
    printf("   D: 修改学生信息    E: 删除学生    F: 存取数据    \n");
    printf("   0：退出程序\n");
    printf("**************************************************\n");
    scanf("%c", &choose);
    getchar();
    while (choose != '0')
    {
        switch (choose)
        {
        case 'A':
            printf("\na: 显示所有学生  b：显示班级   c:显示年级\nEnter:");
            scanf("%c", &choose_a);
            getchar();
            switch (choose_a)
            {
                case 'a': print(); 
                    break;
                case 'b': print_class();
                    break;
                case 'c': print_grade();
                    break;
                default:
                    break;
            }
            break;
        case 'B':
            seek();
            break;
        case 'C':
            add();
            break;
        case 'D':
            change();
            break;
        case 'E':
            clear();
            break;
        case 'F':
            printf("a: 保存(默认textdata_save.csv)     b:另存为(新文件)\nEnter:");
            scanf("%c", &choose_b);
            getchar();
            switch (choose_b)
            {
                case 'a':
                    write_file("textdata_save.csv");
                    break;
                case 'b':
                    printf("Enter new file name:");
                    scanf("%s", filename);
                    getchar();
                    write_file(filename);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
        }
        printf("******************** 选择功能 ********************\n");
        printf("   A: 显示学生信息    B: 查找学生    C: 添加学生    \n");
        printf("   D: 修改学生信息    E: 删除学生    F: 存取数据    \n");
        printf("   0：退出程序\n");
        printf("**************************************************\n");
        scanf("%c", &choose);
        getchar();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/************************************** 主函数  *************************************/
/////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char * filename = "student_data.csv";       // 文件名
    read_file(filename);                        // 加载文件
    user(head);                                 // 用户接口
    disposal_LinkList(head);                    // 释放内存
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////