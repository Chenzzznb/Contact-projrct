//contact.c用于函数实现
#include"contact.h"

//静态版本
// void InitContact(Contact* pc)
// {
//     assert(pc);
//     pc->count=0; //最初通讯录人数为0
//     memset(pc->data,0,sizeof(pc->data));
// }

void LoadContact(Contact* pc)
{
    FILE* pfRead=fopen("contact.txt","rb");
    if (pfRead==NULL)
    {
        perror("LoadContact");
        return ;
    }
    Peoinfo tmp={0};
    while (fread(&tmp,sizeof(Peoinfo),1,pfRead)==1)
    {
        pc->data[pc->count]=tmp;
        pc->count++;
    }
    fclose(pfRead);
    pfRead=NULL;
}

//动态版本
int InitContact(Contact* pc)
{
    assert(pc);
    pc->count=0; //最初通讯录人数为0
    pc->data=(Peoinfo*)calloc(3,sizeof(Peoinfo));
    if (pc->data==NULL)
    {
        printf("InitContact::%s\n",strerror(errno));
        return 1;
    }
    pc->capacity=3;

    //加载文件信息到通讯录中
    LoadContact(pc);
    return 0;
}

//添加联系人
void AddContact(Contact *pc)
{
    assert(pc);
    // 静态
    // if (pc->count==100) //也可以在头文件中用#define Max=100来写
    // {
    //     printf("The Contact is full!\n");
    //     return;
    // }
    //动态
    // 增容
    if (pc->count==pc->capacity)
    {
        Peoinfo* ptr=realloc(pc->data,(pc->capacity+2)*sizeof(Peoinfo));  //每次增加2个
        if (ptr==NULL)
        {
            printf("AddContact::%s\n",strerror(errno));
            return;    
        }
        else
        {
            pc->data=ptr;
            pc->capacity+=2;
        }
        
    } // 可以把这一段if封装成一个函数CheckCapacity(Contact* pc)
    
    //
    printf("Please enter his/her name:\n");
    scanf("%s",pc->data[pc->count].name);
    printf("Please enter his/her age:\n");
    scanf("%d",&(pc->data[pc->count].age));
    printf("Please enter his/her sex:\n");
    scanf("%s",pc->data[pc->count].sex); //数组本身就是地址，不需要&传地址
    printf("Please enter his/her telephone:\n");
    scanf("%s",pc->data[pc->count].tele);
    printf("Please enter his/her address:\n");
    scanf("%s",pc->data[pc->count].addr);
    pc->count++;
}
void ShowContact(const Contact* pc)
{
    assert(pc);
    int i=0;
    printf("%20s\t%3s\t%5s\t%12s\t%30s\n", "NAME", "AGE", "SEX", "TELE", "ADDR");
    for ( i = 0; i <pc->count ; i++)
    {
        printf("%20s\t%3d\t%5s\t%12s\t%30s\n",pc->data[i].name,
            pc->data[i].age,
            pc->data[i].sex,
            pc->data[i].tele,
            pc->data[i].addr);//这样写方便看
    }
    
}
static int FindByName(Contact* pc,char name[])   //只在函数内部用，不需要在头文件中声明
{
    assert(pc);
    int i=0;
    for ( i = 0; i <pc->count; i++)
    {
        if (0==strcmp(pc->data[i].name,name))
        {
            return i;
        }
        
    }
    return -1;
}
void DelContact(Contact* pc)
{
    assert(pc);
    char name[100];
    if (pc->count==0)
    {
        printf("The Contact is empty,there is no infomation to delete!\n");
        return;
    }
    printf("Please enter the name of people you want to delete:>");
    scanf("%s",name);
    //删除
    //1.查找
    int pos=FindByName(pc,name);
    //2。删除
    for (int j= pos;j<pc->count-1; j++)
    {
        pc->data[j]=pc->data[j+1];// 全部删掉目标人物信息
    }
    pc->count--; //把最后一个人的信息前移一位后减一，访问不了最后一人的信息
}

void SearchContact(Contact* pc)
{
    assert(pc);
    char name[100]={0};
    printf("Enter name that you wanna search:\n");
    scanf("%s",name);
    //1.查找，用FindByName
    int position=FindByName(pc,name);
    //2.打印
    if (position==-1)
    {
        printf("Not Exist!\n");
        return;
    }
    else
    {
        printf("%20s\t%3d\t%5s\t%12s\t%30s\n",pc->data[position].name,
            pc->data[position].age,
            pc->data[position].sex,
            pc->data[position].tele,
            pc->data[position].addr);
    }
    
}
void ModifyContact(Contact* pc)
{
    assert(pc);
    char name[100]={0};
    printf("Enter name of person want to modify:");
    scanf("%s",name);
    //1.查找
    int pos=FindByName(pc,name);
    if (pos==-1)
    {
        printf("Not Exist!\n");
        return;
    }
    //2.修改
    printf("Please enter his/her name:\n");
    scanf("%s",pc->data[pos].name);
    printf("Please enter his/her age:\n");
    scanf("%d",&(pc->data[pos].age));
    printf("Please enter his/her sex:\n");
    scanf("%s",pc->data[pos].sex); //数组本身就是地址，不需要&传地址
    printf("Please enter his/her telephone:\n");
    scanf("%s",pc->data[pos].tele);
    printf("Please enter his/her address:\n");
    scanf("%s",pc->data[pos].addr);
    printf("Sucessfully Modify!\n");
}

//按照名字来排序
int Cmp_by_name(const void*a,const void *b)
{
    return strcmp(((Peoinfo*)a)->name,((Peoinfo*)b)->name);
}
void SortContact(Contact* pc)
{
    assert(pc);
    qsort(pc->data,pc->count,sizeof(Peoinfo),Cmp_by_name);  // qsort的库是stdlib.h
    printf("Sucessfully Sort!\n");
}


//销毁指针
void DestoryContact(Contact* pc)
{
    assert(pc);
    free(pc->data);
    pc->data=NULL;
}


//保存文件
void SaveContact(const Contact* pc)
{
    assert(pc);
    FILE* pfWrite=fopen("contact.txt","wb");
    if (pfWrite==NULL)
    {
        perror("SaveContact");
        return;
    }
    // 写文件-二进制形式
    int i=0;
    for ( i = 0; i <pc->count; i++)
    {
        fwrite(pc->data+i,sizeof(Peoinfo),1,pfWrite);  //第一位要地址，不能写data[i],而是写data+i
    }
    fclose(pfWrite);
    pfWrite=NULL;
}