#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define Node struct node
Node             //结构体类型定义，包括：姓名、电话号码和联系地址
{
 char szName[20];
 char szPhoneNum[12];
 char szAddress[30];
 Node *next;
};
Node *strpHead;  //全局变量，链表头指针
Node *strpCurrent;  //用于指向当前正在操作的结点
 //函数原型声明
void HandleChoice_f(int);
void AddRecord_f();
void InsertNode_f(Node * );
Node *InsertPoint_f(char * );
void MakeNewHead_f(Node * );
void AddToEnd_f(Node * );
void MoveToEnd_f();
void DisplayList_f();
void DeleteRecord_f();
void DelHead_f();
void DelEnd_f(Node * );
void DelMid_f(Node * );
int VerifyDel_f();
void DelNode_f(Node * );
void DelList_f();
void SearchByName_f();
void WriteFile_f();
void LoadFile_f();
void Help_f();

//主程序
int main()
{
 int nChoice;
 system("color 1a");
 printf("             欢迎来到通讯录管理系统                \n");
 system("pause");
 system("cls");
 strpHead=NULL;
 LoadFile_f();
 do
 {printf("   ☆☆☆☆☆☆☆☆☆菜单☆☆☆☆☆☆☆☆☆☆\n");
 printf("   ┌─────────────────────┐  \n");
 printf("   │     1.增加记录                           │  \n");
 printf("   │     2.显示所有记录                       │　\n");
 printf("   │     3.按名字查找朋友的信息               │　\n");
 printf("   │     4.删除记录                           │　\n");
 printf("   │   ★5.请求帮助                           │  \n");
 printf("   │     6.退出程序                           │  \n");
 printf("   └─────────────────────┘  \n");
 printf("      ☆程珊☆　　手机:13684601282  　　　　       \n");
 printf("    请选择代码(1,2,3,4,5,6):");
 scanf("%d",&nChoice);
 HandleChoice_f(nChoice);  /*接受用户的选择*/
 }while(nChoice!=6);
 return 0;
 
}
void HandleChoice_f(int nChoice)   /*根据用户选择nChoice调用相应的函数*/
{
 switch(nChoice)
 {
 case 1:
  AddRecord_f();
  break;
 case 2:
  DisplayList_f();
  break;
 case 3:
  SearchByName_f();
  break;
 case 4:
  DeleteRecord_f();
  break;
 case 5:
  Help_f();
  break;
 case 6:
  WriteFile_f();       /*将链表中的数据写回文件*/
  if(strpHead!=NULL)
  {
   DelList_f();
  }
  break;
 default:
  printf("没有您要的选项!\n");
  break;
 }
}

void AddRecord_f()
{
 Node *strpNew;/*为新记录定义临时指针变量*/
 strpNew=(Node *)malloc(sizeof(Node));/*开辟空间存放新记录数据*/
 getchar();
 printf("姓名:");
 gets(strpNew->szName);
 printf("电话号码:");
 gets(strpNew->szPhoneNum);
 printf("联系地址:");
 gets(strpNew->szAddress);
 InsertNode_f(strpNew);
 system("cls");
}
void InsertNode_f(Node *strpNew)
{
 Node *strpFront;
 Node *strpBack;
 system("cls");
 if(strpHead==NULL)
 {
  strpNew->next=NULL;
  strpHead=strpNew;
 }
 else
 {
  if(strcmp(strpNew->szName,strpHead->szName)>0)
  {
   MakeNewHead_f(strpNew);
  }
  else //查找新结点的位置
  {
   strpCurrent=InsertPoint_f(strpNew->szName);
   strpFront=strpCurrent;
   strpBack=strpCurrent->next;
   if(strpBack==NULL)
   {
    AddToEnd_f(strpNew);
   }
   else
   {
    strpFront->next=strpNew;
    strpNew->next=strpBack;
   }
  }
 }
}
Node *InsertPoint_f(char *szName) /*根据新增记录的姓氏，返回其将插入的正确位置*/
{
 char szTempName[20];
 Node *strpTemp;
 int nTemp;
 if(strpHead->next!=NULL)
 {
  strpCurrent=strpHead;
  strpTemp=strpCurrent->next;
  strcpy(szTempName,strpTemp->szName);
  nTemp=strcmp(szName,szTempName);
  while((nTemp>0)&&(strpCurrent->next!=NULL))
  {
   strpCurrent=strpTemp;
   if(strpCurrent->next!=NULL)
   {
    strpTemp=strpCurrent->next;
    strcpy(szTempName,strpTemp->szName);
    nTemp=strcmp(szName,szTempName);
   }
  }
 }
 else
 {
  strpCurrent=strpHead;
 }
 return(strpCurrent);
}
void MakeNewHead_f(Node *strpNew)/*新结点成为链表的头结点*/
{
 Node *strpTemp;
 strpTemp=strpHead;
 strpNew->next=strpTemp;
 strpHead=strpNew;
}
void AddToEnd_f(Node *strpNew)/*新结点成为链表的尾结点*/
{
 strpNew->next=NULL;
 MoveToEnd_f();
 strpCurrent->next=strpNew;
}
void MoveToEnd_f()/*当前指针移到链表尾*/
{
 strpCurrent=strpHead;
 while(strpCurrent->next!=NULL)
 {
  strpCurrent=strpCurrent->next;
 }
}
void DisplayList_f()
{
 
 strpCurrent=strpHead;
 if(strpCurrent!=NULL)
 {
  printf("\n");
  printf("      姓名             电话号码           联系地址         \n");
  printf("------------------------------------------------------------\n");
  do
  {
   printf("%10s",strpCurrent->szName);
   printf("%20s",strpCurrent->szPhoneNum);
   printf("%20s\n",strpCurrent->szAddress);
   strpCurrent=strpCurrent->next;
   printf("\n");
  }while(strpCurrent!=NULL);
  system("pause");
  system("cls");
 }
 else
 {
  printf("没有记录可以显示!\n");
 }
}
void SearchByName_f()
{
 char szSearch[20];
 strpCurrent=strpHead;
 system("cls");
 getchar();
 printf("\n输入您要查找的姓名:");
 gets(szSearch);
 while((strpCurrent!=NULL)&&(strcmp(strpCurrent->szName,szSearch)!=0))
 {
  strpCurrent=strpCurrent->next;
 }
 if(strpCurrent!=NULL)
 {
  printf("\n记录找到了!\n");
  printf("%s\n",strpCurrent->szName);
  printf("%s\n",strpCurrent->szPhoneNum);
  printf("%s\n",strpCurrent->szAddress);
 }
 else
 {
  printf("没有相应的记录!\n");
  printf("按ENTER键继续\n");
  system("pause");
  system("cls");
 }
}
void DeleteRecord_f()
{
 char szSearch[20];
 Node *strpFront;
 system("cls");
 strpFront=NULL;
 strpCurrent=strpHead;
 getchar();
 printf("\n输入朋友的姓名以删除该记录:");
 gets(szSearch);
 while((strpCurrent!=NULL)&&(strcmp(strpCurrent->szName,szSearch)!=0))
 {
  strpFront=strpCurrent;
  strpCurrent=strpCurrent->next;
 }
 if(strpCurrent!=NULL)
 {
  printf("\n记录找到了\n");
  printf("%s\n",strpCurrent->szName);
  printf("%s\n",strpCurrent->szPhoneNum);
  printf("%s\n",strpCurrent->szAddress);
  if(VerifyDel_f())
  {
   DelNode_f(strpFront);
   printf("\n该记录已经删除!\n");
  }
  else
  {
   printf("\n该记录没有删除!\n");
  }
 }
 else
 {
  printf("\n没有匹配的记录被删除!\n");
 }
 system("cls");
}
void Help_f()
{
 int nChoice;
 do
 {
  system("cls");
  printf("欢迎来到帮助栏,请选择代号\n");
  printf("1:通讯录的功能\n");
  printf("2:怎么清除所有记录\n");
  printf("3:在加入新的信息时，原来的信息还在吗\n");
  printf("4:你操作时需要注意的事项!\n");
  printf("5:退出\n");
  scanf("%d",&nChoice);
  switch(nChoice)
  {
  case 1:
   printf("这是一个简单的通讯录，刚开始是一个空的电话本。你可以根据提示加入或删除纪录，还可以根据需要显示和查询电话号码\n");
   printf("按ENTER键继续\n");
   getch();
   system("cls");
   break;
  case 2:
   printf("你只要删除文件Friend.dat或者退出程序释放存储空间，就可以删除所有纪录了\n");
   printf("按ENTER键继续\n");
   getch();
   system("cls");
   break;
  case 3:
   printf("当然拉，加入信息不会改变原来的信息\n");
   printf("按ENTER键继续\n");
   getch();
   system("cls");
   break;
  case 4:
   printf("在查找和删除纪录时，应该把要找的朋友的全名写好，否则将无法显示和操作\n");
   printf("按ENTER键继续\n");
   getch();
   system("cls");
   break;
  default:
  case 5:
   printf("按ENTER键继续\n");
   break;
  }
 }while(nChoice!=5);
}
int VerifyDel_f() /*删除信息时要求予以确认*/
{
 char chYesNo;
 printf("你确定要删除吗?(Y/N)");
 scanf("%c",&chYesNo);
 if((chYesNo=='Y')||(chYesNo=='y'))
 {
  return(1);
 }
 else
 {
  return(0);
 }
}
void DelNode_f(Node *strpFront)/*删除结点*/
{
 if(strpCurrent==strpHead)
  DelHead_f();
 else
 {
  if(strpCurrent->next==NULL)
   DelEnd_f(strpFront);
  else
   DelMid_f(strpFront);
 } 
}
void DelHead_f()  /*删除头结点*/
{
 strpCurrent=strpHead;
 if(strpHead->next!=NULL)
  strpHead=strpCurrent->next;
 else
  strpHead=NULL;
 free(strpCurrent);
}
void DelEnd_f(Node *strpFront) /*删除尾结点*/
{
 free(strpCurrent);
 strpFront->next=NULL;
 strpCurrent=strpHead;
}
void DelMid_f(Node *strpFront) /*删除链表中的结点*/
{
 strpFront->next=strpCurrent->next;
 free(strpCurrent);
 strpCurrent=strpHead;
}
void DelList_f()/*删除链表，释放空间*/
{
 Node *strpTemp;
 strpCurrent=strpHead;
 do
 {
  strpTemp=strpCurrent->next;
  free(strpCurrent);
  strpCurrent=strpTemp;
 }while(strpTemp!=NULL);
}
void Deln(char *szString)/*删除字符串后的回车符*/
{
 int nLength;
 nLength=strlen(szString);
 if(nLength>=2)
 {
  if(szString[nLength-1]=='\n')
   szString[nLength-1]='\0';
 }
}
void WriteFile_f()/*程序退出，将链表数据写回文件*/
{
 FILE *fpoutfile;
 if((fpoutfile=fopen("FRIENDS.DAT","w"))==NULL)
 {
  printf("File Error!\n");
  exit(0);
 }
 strpCurrent=strpHead;
 if(strpHead!=NULL)
 {
  do
  {
   fprintf(fpoutfile,"%s\n",strpCurrent->szName);
   fprintf(fpoutfile,"%s\n",strpCurrent->szPhoneNum);
   fprintf(fpoutfile,"%s\n",strpCurrent->szAddress);
   strpCurrent=strpCurrent->next;
  }while(strpCurrent!=NULL);
 }
 fprintf(fpoutfile,"END OF FILE");
 fclose(fpoutfile);//关闭文件
}
void LoadFile_f()/*从数据文件FRIEND.DAT中读取数据重建链表*/
{
 Node *strpNew;
 FILE *fpinfile;/*输入文件指针*/
 int nEndLoop=0;
 if((fpinfile=fopen("FRIENDS.DAT","r"))==NULL)
 {
  printf("现在没有可用数据载入,链表为空\n");
 }
 else{
  do{
  strpNew=(Node *)malloc(sizeof(Node));
  if(strpNew!=NULL)
  {
   fgets(strpNew->szName,20,fpinfile);
   if((strcmp(strpNew->szName,"")!=0)&&(strcmp(strpNew->szName,"END OF FILE")!=0))
   {
    fgets(strpNew->szPhoneNum,15,fpinfile);
    fgets(strpNew->szAddress,15,fpinfile);
    Deln(strpNew->szName);
    Deln(strpNew->szPhoneNum);
    Deln(strpNew->szAddress);
    InsertNode_f(strpNew);
   }
   else
   {
    free(strpNew);
    nEndLoop=1;
   }
  }
  else
  {
   printf("WARNING:Memory error!\n");
   nEndLoop=1;
  }   
  }while(nEndLoop==0);
  fclose(fpinfile);
 }
}