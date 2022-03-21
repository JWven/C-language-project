/***********************************************************************************/
/*********************************** 声明与定义 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define LEN sizeof(struct Student)     // 结点大小
// 全局变量
int n = 0;                             // 数据条数（结点个数）
typedef struct Student                 // 定义链表
{
    char name[7];                      // 名字
    int continue_drop;                 // 是否在读（1是，0否）
    long student_id;                   // 学号
    int gender;                        // 性别（1男，0女）
    int grade;                         // 年级
    int class;                         // 班别
    float chinese_marks;               // 语文成绩
    float english_marks;               // 英语成绩
    float math_marks;                  // 数学成绩
    struct Student * next;             // 指针域
}Student;                              // 重命名
Student * head;                        // 链表头指针

// 函数声明
void add();                                          // 添加学生
void sort();                                         // 链表按学号排序
void seek();                                         // 查找学生
void user();                                         // 用户使用接口
void clear();                                        // 删除学生
void print();                                        // 链表打印
void change();                                       // 修改学生信息
void print_class();                                  // 打印单个班级学生信息
void print_grade();                                  // 打印单个年级学生信息
void insert(Student * stud);                         // 链表插入结点
void read_file(char * file_name);                    // 读取文件
void write_file(char * filename);                    // 写出文件函数
void print_personal(Student * p);                    // 打印单个学生信息
void disposal_LinkList(Student * headNode);          // 释放链表
void data_input(Student * p1, char * data_row);      // 存储文件数据
/***********************************************************************************/
/***********************************************************************************/