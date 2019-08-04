#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define Node struct node
Node             //�ṹ�����Ͷ��壬�������������绰�������ϵ��ַ
{
 char szName[20];
 char szPhoneNum[12];
 char szAddress[30];
 Node *next;
};
Node *strpHead;  //ȫ�ֱ���������ͷָ��
Node *strpCurrent;  //����ָ��ǰ���ڲ����Ľ��
 //����ԭ������
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

//������
int main()
{
 int nChoice;
 system("color 1a");
 printf("             ��ӭ����ͨѶ¼����ϵͳ                \n");
 system("pause");
 system("cls");
 strpHead=NULL;
 LoadFile_f();
 do
 {printf("   ����������˵������������\n");
 printf("   ����������������������������������������������  \n");
 printf("   ��     1.���Ӽ�¼                           ��  \n");
 printf("   ��     2.��ʾ���м�¼                       ����\n");
 printf("   ��     3.�����ֲ������ѵ���Ϣ               ����\n");
 printf("   ��     4.ɾ����¼                           ����\n");
 printf("   ��   ��5.�������                           ��  \n");
 printf("   ��     6.�˳�����                           ��  \n");
 printf("   ����������������������������������������������  \n");
 printf("      ���ɺ����ֻ�:13684601282  ��������       \n");
 printf("    ��ѡ�����(1,2,3,4,5,6):");
 scanf("%d",&nChoice);
 HandleChoice_f(nChoice);  /*�����û���ѡ��*/
 }while(nChoice!=6);
 return 0;
 
}
void HandleChoice_f(int nChoice)   /*�����û�ѡ��nChoice������Ӧ�ĺ���*/
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
  WriteFile_f();       /*�������е�����д���ļ�*/
  if(strpHead!=NULL)
  {
   DelList_f();
  }
  break;
 default:
  printf("û����Ҫ��ѡ��!\n");
  break;
 }
}

void AddRecord_f()
{
 Node *strpNew;/*Ϊ�¼�¼������ʱָ�����*/
 strpNew=(Node *)malloc(sizeof(Node));/*���ٿռ����¼�¼����*/
 getchar();
 printf("����:");
 gets(strpNew->szName);
 printf("�绰����:");
 gets(strpNew->szPhoneNum);
 printf("��ϵ��ַ:");
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
  else //�����½���λ��
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
Node *InsertPoint_f(char *szName) /*����������¼�����ϣ������佫�������ȷλ��*/
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
void MakeNewHead_f(Node *strpNew)/*�½���Ϊ�����ͷ���*/
{
 Node *strpTemp;
 strpTemp=strpHead;
 strpNew->next=strpTemp;
 strpHead=strpNew;
}
void AddToEnd_f(Node *strpNew)/*�½���Ϊ�����β���*/
{
 strpNew->next=NULL;
 MoveToEnd_f();
 strpCurrent->next=strpNew;
}
void MoveToEnd_f()/*��ǰָ���Ƶ�����β*/
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
  printf("      ����             �绰����           ��ϵ��ַ         \n");
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
  printf("û�м�¼������ʾ!\n");
 }
}
void SearchByName_f()
{
 char szSearch[20];
 strpCurrent=strpHead;
 system("cls");
 getchar();
 printf("\n������Ҫ���ҵ�����:");
 gets(szSearch);
 while((strpCurrent!=NULL)&&(strcmp(strpCurrent->szName,szSearch)!=0))
 {
  strpCurrent=strpCurrent->next;
 }
 if(strpCurrent!=NULL)
 {
  printf("\n��¼�ҵ���!\n");
  printf("%s\n",strpCurrent->szName);
  printf("%s\n",strpCurrent->szPhoneNum);
  printf("%s\n",strpCurrent->szAddress);
 }
 else
 {
  printf("û����Ӧ�ļ�¼!\n");
  printf("��ENTER������\n");
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
 printf("\n�������ѵ�������ɾ���ü�¼:");
 gets(szSearch);
 while((strpCurrent!=NULL)&&(strcmp(strpCurrent->szName,szSearch)!=0))
 {
  strpFront=strpCurrent;
  strpCurrent=strpCurrent->next;
 }
 if(strpCurrent!=NULL)
 {
  printf("\n��¼�ҵ���\n");
  printf("%s\n",strpCurrent->szName);
  printf("%s\n",strpCurrent->szPhoneNum);
  printf("%s\n",strpCurrent->szAddress);
  if(VerifyDel_f())
  {
   DelNode_f(strpFront);
   printf("\n�ü�¼�Ѿ�ɾ��!\n");
  }
  else
  {
   printf("\n�ü�¼û��ɾ��!\n");
  }
 }
 else
 {
  printf("\nû��ƥ��ļ�¼��ɾ��!\n");
 }
 system("cls");
}
void Help_f()
{
 int nChoice;
 do
 {
  system("cls");
  printf("��ӭ����������,��ѡ�����\n");
  printf("1:ͨѶ¼�Ĺ���\n");
  printf("2:��ô������м�¼\n");
  printf("3:�ڼ����µ���Ϣʱ��ԭ������Ϣ������\n");
  printf("4:�����ʱ��Ҫע�������!\n");
  printf("5:�˳�\n");
  scanf("%d",&nChoice);
  switch(nChoice)
  {
  case 1:
   printf("����һ���򵥵�ͨѶ¼���տ�ʼ��һ���յĵ绰��������Ը�����ʾ�����ɾ����¼�������Ը�����Ҫ��ʾ�Ͳ�ѯ�绰����\n");
   printf("��ENTER������\n");
   getch();
   system("cls");
   break;
  case 2:
   printf("��ֻҪɾ���ļ�Friend.dat�����˳������ͷŴ洢�ռ䣬�Ϳ���ɾ�����м�¼��\n");
   printf("��ENTER������\n");
   getch();
   system("cls");
   break;
  case 3:
   printf("��Ȼ����������Ϣ����ı�ԭ������Ϣ\n");
   printf("��ENTER������\n");
   getch();
   system("cls");
   break;
  case 4:
   printf("�ڲ��Һ�ɾ����¼ʱ��Ӧ�ð�Ҫ�ҵ����ѵ�ȫ��д�ã������޷���ʾ�Ͳ���\n");
   printf("��ENTER������\n");
   getch();
   system("cls");
   break;
  default:
  case 5:
   printf("��ENTER������\n");
   break;
  }
 }while(nChoice!=5);
}
int VerifyDel_f() /*ɾ����ϢʱҪ������ȷ��*/
{
 char chYesNo;
 printf("��ȷ��Ҫɾ����?(Y/N)");
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
void DelNode_f(Node *strpFront)/*ɾ�����*/
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
void DelHead_f()  /*ɾ��ͷ���*/
{
 strpCurrent=strpHead;
 if(strpHead->next!=NULL)
  strpHead=strpCurrent->next;
 else
  strpHead=NULL;
 free(strpCurrent);
}
void DelEnd_f(Node *strpFront) /*ɾ��β���*/
{
 free(strpCurrent);
 strpFront->next=NULL;
 strpCurrent=strpHead;
}
void DelMid_f(Node *strpFront) /*ɾ�������еĽ��*/
{
 strpFront->next=strpCurrent->next;
 free(strpCurrent);
 strpCurrent=strpHead;
}
void DelList_f()/*ɾ�������ͷſռ�*/
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
void Deln(char *szString)/*ɾ���ַ�����Ļس���*/
{
 int nLength;
 nLength=strlen(szString);
 if(nLength>=2)
 {
  if(szString[nLength-1]=='\n')
   szString[nLength-1]='\0';
 }
}
void WriteFile_f()/*�����˳�������������д���ļ�*/
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
 fclose(fpoutfile);//�ر��ļ�
}
void LoadFile_f()/*�������ļ�FRIEND.DAT�ж�ȡ�����ؽ�����*/
{
 Node *strpNew;
 FILE *fpinfile;/*�����ļ�ָ��*/
 int nEndLoop=0;
 if((fpinfile=fopen("FRIENDS.DAT","r"))==NULL)
 {
  printf("����û�п�����������,����Ϊ��\n");
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