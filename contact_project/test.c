#include"contact.h"
int main()
{
    int input=0;
    Contact con;
    InitContact(&con);
    do
    {
        printf("*********************************\n");
        printf("***1.Add        2.Del         ***\n");
        printf("***3.Search     4.Modify      ***\n");
        printf("***5.Show       6.Sort        ***\n");
        printf("***0.Exit                     ***\n");
        printf("            Thank!               \n");
        scanf("%d",&input);
        switch (input)
        {
        case 1: //也可以用enum的枚举来代表1,2,3…………            
            AddContact(&con);
            break;
        case 2:
            DelContact(&con);
            break;
        case 3:
            SearchContact(&con);
            break;
        case 4:
            ModifyContact(&con);
            break;
        case 5:
            ShowContact(&con);
            break;
        case 6:
            SortContact(&con);
            break;
        case 0:
            printf("Exit the Contact.\n");
            SaveContact(&con);
            DestoryContact(&con);
        default:
            printf("error!\n");
            break;
        }
    } while (input);
    
    return 0;
}