//contact.h用于放结构体，宏以及函数声明
#pragma once
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<errno.h>
//类型的声明
//
//人的信息
typedef struct 
{
    char name[20];
    int age;
    char sex[10];
    char tele[12];
    char addr[30];//地址
}Peoinfo;

//通讯录
typedef struct 
{
    //Peoinfo data[100];//有100个这样的数组存放人的信息    <---静态
    Peoinfo *data;  //动态管理
    int count; //数人
    int capacity; //先设最多3人
}Contact;


int InitContact(Contact* pc); //初始化
void AddContact(Contact *pc);//添加
void ShowContact(const Contact* pc);//打印信息
void DelContact(Contact* pc);//删除
void SearchContact(Contact* pc);//搜索
void ModifyContact(Contact* pc);//修改
void SortContact(Contact* pc);//排序
void DestoryContact(Contact* pc); // Exit时销毁指针
void SaveContact(const Contact* pc);//保存通讯录
void LoadContact(Contact* pc);//加载文件信息到通讯录中