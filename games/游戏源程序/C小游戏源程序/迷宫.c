#include <stdio.h>
#include <slib.h>
#include <malloc.h>
#include <conio.h>
#include <dos.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define F9 0x43
#define Esc 0x1b
#define Del 0x53
#define Home 0x47
#define End 0x4f
#define Space 0x20
#define Up 0x48
#define Down 0x50
#define Left 0x4b
#define Right 0x4d
#define Enter 0x0d
#define F2 0x3c
#define F3 0x3d
#define STACK_INIT_SIZE 200
#define STACKINCREMENT 10
typedef int Boolean;
typedef int Status;
typedef suct {
int x;
int y;
} PosType;
typedef suct {
int ord;
PosType seat;
int di;
} SElemType;
typedef suct {
int ;
int foot;
int mark;
} MazeType;
typedef suct {
SElemType *base;
SElemType *top;
int stacksize;
} Stack;
int Maze[20][30];
MazeType maze[20][30];
PosType StartPlace;
PosType EndPlace;
int count;
int m,n;
Boolean b_start=FALSE,b_end=FALSE;
void CreatMaze(void);
Status SaveMaze(char *filename);
Status LoadMaze(char *filename);
void Error(char *message);
Status InitStack(Stack *s);
Status DesoyStack(Stack *s);
Status ClearStack(Stack *s);
Boolean StackEmpty(Stack *s);
int StackLength(Stack *s);
Status Push(Stack *s,SElemType e);
SElemType Pop(Stack *s,SElemType e);
Status GetTop(Stack *s,SElemType *e);
Status StackTraverse(Stack *s,Status (* visit)(SElemType *se));
Boolean Pass(PosType curpos);
void MarkPrint(PosType seat);
void FootPrint(PosType curpos);
PosType NextPos(PosType seat,int di);
Status MazePath(PosType start,PosType end);
void CreatMaze(void)
/* Form the maze. */
{
void Error(char *message);
Status SaveMaze(char *filename);
Status LoadMaze(char *filename);
int i,j;
int x,y;
char c;
char savename[12],loadname[12];
Boolean flag=FALSE,load=FALSE;
clrscr();
printf("Menu:\n\n");
printf("1.Load Mazefile:(*.dd)\n\n");
printf("2.Input Maze:\n\n");
printf("Input your choice: ");
do
{
c=getch();
switch(c)
{
case ''''''''''''''''''''''''''''''''1'''''''''''''''''''''''''''''''': putch(''''''''''''''''''''''''''''''''1''''''''''''''''''''''''''''''''); break;
case ''''''''''''''''''''''''''''''''2'''''''''''''''''''''''''''''''': putch(''''''''''''''''''''''''''''''''2''''''''''''''''''''''''''''''''); break;
case Esc: sleep(1); exit(1);
default: break;
}
}
while(c!=''''''''''''''''''''''''''''''''1''''''''''''''''''''''''''''''''&&c!=''''''''''''''''''''''''''''''''2'''''''''''''''''''''''''''''''') ;
if(c==''''''''''''''''''''''''''''''''1'''''''''''''''''''''''''''''''')
{
printf("\n\nLoadName: ");
scanf("%s",loadname);
if(LoadMaze(loadname))
{
sleep(1); load=TRUE;
}
else { gotoxy(1,9); printf("Load fail! "); }
}
if(!load)
{
printf("\nInput the maze''''''''''''''''''''''''''''''''s size:\n");
printf("\nInput Length :\n");
scanf("%d",&m);
printf("\nInput Width :\n");
scanf("%d",&n);
if(m<4||n<4) Error("Input");
if(m>30||n>20) Error("Maze too large");
for(i=0;i<30;i )
for(j=0;j<20;j )
Maze[j][i]=2;
StartPlace.x=0;
StartPlace.y=0;
EndPlace.x=0;
EndPlace.y=0;
clrscr();BR> for(i=1;i<=n;i )
{
for(j=1;j<=m;j )
{
printf(" #");
Maze[i-1][j-1]=0;
}
printf("\n");
}
}
gotoxy(65,5);
printf("''''''''''''''''''''''''''''''''#'''''''''''''''''''''''''''''''':Wall");
gotoxy(65,7);
printf("Start:Home");
gotoxy(65,9);
printf("End:End");
gotoxy(65,11);
printf("Delete Wall:Del");
gotoxy(65,13);
printf("Enter Wall:Enter");
gotoxy(65,15);
printf("Save Maze:F2");
gotoxy(65,17);
printf("Complete:F9");
gotoxy(65,19);
printf("Exit:Esc");
gotoxy(4,3);
x=4;y=3;
do
{
c=getch();
switch(c)
{
case Up: if(y>3) { y--; gotoxy(x,y); }
break;
case Down: if(y<n) { y ; gotoxy(x,y); }
break;
case Left: if(x>4) { x-=2; gotoxy(x,y); }
break;
case Right: if(x<2*m-2) { x =2; gotoxy(x,y); }
break;
case Del: if(y-2==StartPlace.y&&x/2-1==StartPlace.x) b_start=FALSE;
if(y-2==EndPlace.y&&x/2-1==EndPlace.x) b_end=FALSE;
putch('''''''''''''''''''''''''''''''' ''''''''''''''''''''''''''''''''); Maze[y-2][x/2-1]=1; gotoxy(x,y);
break;
case Enter: if(y-2==StartPlace.y&&x/2-1==StartPlace.x) break;
if(y-2==EndPlace.y&&x/2-1==EndPlace.x) break;
putch(''''''''''''''''''''''''''''''''#''''''''''''''''''''''''''''''''); Maze[y-2][x/2-1]=0; gotoxy(x,y);
break;
case Home: if(Maze[y-2][x/2-1]&&!b_start)
{
StartPlace.x=x/2-1;
StartPlace.y=y-2;
putch(''''''''''''''''''''''''''''''''S'''''''''''''''''''''''''''''''');
gotoxy(x,y);
b_start=TRUE;
}
break;
case End: if(Maze[y-2][x/2-1]&&!b_end)
{
EndPlace.x=x/2-1;
EndPlace.y=y-2;
putch(''''''''''''''''''''''''''''''''E'''''''''''''''''''''''''''''''');
gotoxy(x,y);
b_end=TRUE;
}
break;
case Esc: gotoxy(2,22); printf("exit"); sleep(1); exit(1);
case F9: if(b_start&&b_end) flag=TRUE; break;
case F2: gotoxy(2,22);
printf("Savename:");
scanf("%s",savename);
gotoxy(2,22);
if(SaveMaze(savename)) printf("Save OK! ");
else printf("Save fail! ");
sleep(1);
gotoxy(2,22);
printf(" ");
gotoxy(x,y);
break;
default: break;
}
}
while(!flag);
for(i=0;i<30;i )
for(j=0;j<20;j )
{
maze[j][i].=Maze[j][i];
maze[j][i].mark=0;
maze[j][i].foot=0;
}
}
Status LoadMaze(char *file)
/* The maze has been loaded. */
{
FILE *fp;
char *buffer;
char ch;
int i=0,j,k;
Boolean len=FALSE,wid=FALSE;
if((fp=fopen(file,"r"))==NULL)
return ERROR;
buffer=(char *)malloc(600*sizeof(char));
ch=fgetc(fp);
while(ch!=EOF)
{
buffer[i]=ch;
i ;
ch=fgetc(fp);
}
m=30;n=20;
for(i=0;i<600;i )
{
j=i/30; k=i0;
if(buffer[i]==''''''''''''''''''''''''''''''''2''''''''''''''''''''''''''''''''&&!len){ m=i; len=TRUE; }
if(k==0&&buffer[i]==''''''''''''''''''''''''''''''''2''''''''''''''''''''''''''''''''&&!wid){ n=j; wid=TRUE; }
switch(buffer[i])
{
case ''''''''''''''''''''''''''''''''0'''''''''''''''''''''''''''''''': Maze[j][k]=0; break;
case ''''''''''''''''''''''''''''''''1'''''''''''''''''''''''''''''''': Maze[j][k]=1; break;
case ''''''''''''''''''''''''''''''''2'''''''''''''''''''''''''''''''': Maze[j][k]=2; break;
case ''''''''''''''''''''''''''''''''3'''''''''''''''''''''''''''''''': Maze[j][k]=1;
StartPlace.x=k;
StartPlace.y=j;
b_start=TRUE;
break;
case ''''''''''''''''''''''''''''''''4'''''''''''''''''''''''''''''''': Maze[j][k]=1;
EndPlace.x=k;
EndPlace.y=j;
b_end=TRUE;
break;
default : break;
}
}
fclose(fp);
clrscr();
for(i=0;i<30;i )
for(j=0;j<20;j )
{
maze[j][i].=Maze[j][i];
maze[j][i].foot=0;
maze[j][i].mark=0;
if(Maze[j][i]==0)
{
gotoxy(2*i 2,j 2);
putch(''''''''''''''''''''''''''''''''#'''''''''''''''''''''''''''''''');
}
}
gotoxy(2*StartPlace.x 2,StartPlace.y 2);
putch(''''''''''''''''''''''''''''''''S'''''''''''''''''''''''''''''''');
gotoxy(2*EndPlace.x 2,EndPlace.y 2);
putch(''''''''''''''''''''''''''''''''E'''''''''''''''''''''''''''''''');
return OK;
}
Status SaveMaze(char *filename)
/* The maze has been saved. */
{
FILE *fp;
char *buffer;
int i,j,k;
fp=fopen(filename,"wb");
buffer=(char *)malloc(600*sizeof(char));
for(i=0;i<600;i )
{
j=i/30; k=i0;
switch(Maze[j][k])
{
case 0: buffer[i]=''''''''''''''''''''''''''''''''0''''''''''''''''''''''''''''''''; break;
case 1: buffer[i]=''''''''''''''''''''''''''''''''1''''''''''''''''''''''''''''''''; break;
case 2: buffer[i]=''''''''''''''''''''''''''''''''2''''''''''''''''''''''''''''''''; break;
default : Error("Write"); break;
}
if(k==StartPlace.x&&j==StartPlace.y) buffer[i]=''''''''''''''''''''''''''''''''3'''''''''''''''''''''''''''''''';
if(k==EndPlace.x&&j==EndPlace.y) buffer[i]=''''''''''''''''''''''''''''''''4'''''''''''''''''''''''''''''''';
}
fwrite(buffer,600,1,fp);
free(buffer);
fclose(fp);
return OK;
}
void Error(char *message)
{
clrscr();
fprintf(serr,"Error:%s\n",message);
exit(1);
} /* Error */

Status InitStack(Stack *s)
/* The stack s has been created and is initialized to be empty. */
{
s->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
if(!s->base) Error("Overflow");
s->top=s->base;
s->stacksize=STACK_INIT_SIZE;
return OK;
} /* InitStack */
Status DesoyStack(Stack *s)
/* The stack s has been desoyed. */
{
s->top=NULL;
s->stacksize=0;
free(s->base);
s->base=NULL;
return OK;
} /* DesoyStack */
Status ClearStack(Stack *s)
/* The stack has been clear to be maximum. */
{
s->top=s->base;
s->stacksize=STACK_INIT_SIZE;
return OK;
} /* ClearStack */
Boolean StackEmpty(Stack *s)
/* Check if the stack s is empty. */
{
if(s->top==s->base) return TRUE;
else return FALSE;
} /* StackEmpty */
int StackLength(Stack *s)
/* Gain the length of the stack s. */
{
if(s->top>s->base) return (int)(s->top-s->base);
else return 0;
} /* StackLength */
Status Push(Stack *s,SElemType e)
/* The element e has been pushed into the stack s. */
{
if(s->top-s->base>=s->stacksize)
{
s->base=(SElemType *)realloc(s->base,
(s->stacksize STACKINCREMENT)*sizeof(SElemType));
if(!s->base) Error("Overflow");
s->top=s->base s->stacksize;
s->stacksize =STACKINCREMENT;
}
*s->top =e;
return OK;
} /* Push */
SElemType Pop(Stack *s,SElemType e)
/* The element e has been removed from the stack s. */
{
if(s->top==s->base) Error("Pop");
e=*--s->top;
return e;
} /* Pop */
Status GetTop(Stack *s,SElemType *e)
/* The element e has got to the top of the stack s.*/
{
if(s->top==s->base) Error("GetTop");
*e=*(s->top-1);
return OK;
} /* GetTop */
/* Traverse the stack s using ''''''''''''''''''''''''''''''''visiting'''''''''''''''''''''''''''''''' function. */
/* Status StackTraverse(Stack *s,Status (* visit)(SElemType *se))
{
SElemType p;
int result;
if(s->top==s->base) return ERROR;
p=s->base;
while(!(p==s->top))
{
result=(*visit)(p);
p ;
}
return OK;
} */
Boolean Pass(PosType curpos)
/* Check if the current position can be passed. */
{
if(maze[curpos.x][curpos.y].==1&&
maze[curpos.x][curpos.y].foot==0&&maze[curpos.x][curpos.y].mark==0)
return TRUE;
else return FALSE;
} /* Pass */
void MarkPrint(PosType seat)
/* Mark the position seat. */
{
maze[seat.x][seat.y].mark=-1;
/* Marking ''''''''''''''''''''''''''''''''-1'''''''''''''''''''''''''''''''' symbolize the current position cannot be put. */
} /* MarkPrint */
void FootPrint(PosType curpos)
/* The foot of the curpos of the maze has been set ''''''''''''''''''''''''''''''''ue''''''''''''''''''''''''''''''''. */
{
maze[curpos.x][curpos.y].foot=1;
} /* FootPrint */
PosType NextPos(PosType seat,int di)
{
switch(di)
{
case 1: seat.y ; return seat; /* Eastward */
case 2: seat.x ; return seat; /* Southward */
case 3: seat.y--; return seat; /* Westward */
case 4: seat.x--; return seat; /* Northward */
default: seat.x=0; seat.y=0; return seat;
}
} /* NextPos */

/* The key to the program. */
/* Pre: The maze array & the startplace & the endplace.
Post: Find the one averse of the maze and perform the mazepath.
Uses: The ADT stack class.
*/
Status MazePath(PosType start,PosType end)
{
PosType curpos;
int curstep;
SElemType e;
Stack *s,stack;
stack.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
if(!stack.base) Error("Overflow");
stack.top=stack.base;
stack.stacksize=STACK_INIT_SIZE;
s=&stack;
curpos=start;
curste
printf("\n");<'0''''''''''''''''''''''''''''''''; break;
case 1: buffer[i]=''''''''''''''''''''''''''''''''1''''''''''''''''''''''''''''''''; break;
case 2: buffer[i]=''''''''''''''''''''''''''''''''2''''''''''''''''''''''''''''''''; break;
default : Error("Write"); break;
}
if(k==StartPlace.x&&j==StartPlace.y) buffer[i]=''''''''''''''''''''''''''''''''3'''''''''''''''''''''''''''''''';
if(k==EndPlace.x&&j==EndPlace.y) buffer[i]=''''''''''''''''''''''''''''''''4'''''''''''''''''''''''''''''''';
}
fwrite(buffer,600,1,fp);
free(buffer);
fclose(fp);
return OK;
}
void Error(char *message)
{
clrscr();
fprintf(serr,"Error:%s\n",message);
exit(1);
} /* Error */

Status InitStack(Stack *s)
/* The stack s has been created and is initialized to be empty. */
{
s->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
if(!s->base) Error("Overflow");
s->top=s->base;
s->stacksize=STACK_INIT_SIZE;
return OK;
} /* InitStack */
Status DesoyStack(Stack *s)
/* The stack s has been desoyed. */
{
s->top=NULL;
s->stacksize=0;
free(s->base);
s->base=NULL;
return OK;
} /* DesoyStack */
Status ClearStack(Stack *s)
/* The stack has been clear to be maximum. */
{
s->top=s->base;
s->stacksize=STACK_INIT_SIZE;
return OK;
} /* ClearStack */
Boolean StackEmpty(Stack *s)
/* Check if the stack s is empty. */
{
if(s->top==s->base) return TRUE;
else return FALSE;
} /* StackEmpty */
int StackLength(Stack *s)
/* Gain the length of the stack s. */
{
if(s->top>s->base) return (int)(s->top-s->base);
else return 0;
} /* StackLength */
Status Push(Stack *s,SElemType e)
/* The element e has been pushed into the stack s. */
{
if(s->top-s->base>=s->stacksize)
{
s->base=(SElemType *)realloc(s->base,
(s->stacksize STACKINCREMENT)*sizeof(SElemType));
if(!s->base) Error("Overflow");
s->top=s->base s->stacksize;
s->stacksize =STACKINCREMENT;
}
*s->top =e;
return OK;
} /* Push */
SElemType Pop(Stack *s,SElemType e)
/* The element e has been removed from the stack s. */
{
if(s->top==s->base) Error("Pop");
e=*--s->top;
return e;
} /* Pop */
Status GetTop(Stack *s,SElemType *e)
/* The element e has got to the top of the stack s.*/
{
if(s->top==s->base) Error("GetTop");
*e=*(s->top-1);
return OK;
} /* GetTop */
/* Traverse the stack s using ''''''''''''''''''''''''''''''''visiting'''''''''''''''''''''''''''''''' function. */
/* Status StackTraverse(Stack *s,Status (* visit)(SElemType *se))
{
SElemType p;
int result;
if(s->top==s->base) return ERROR;
p=s->base;
while(!(p==s->top))
{
result=(*visit)(p);
p ;
}
return OK;
} */
Boolean Pass(PosType curpos)
/* Check if the current position can be passed. */
{
if(maze[curpos.x][curpos.y].==1&&
maze[curpos.x][curpos.y].foot==0&&maze[curpos.x][curpos.y].mark==0)
return TRUE;
else return FALSE;
} /* Pass */
void MarkPrint(PosType seat)
/* Mark the position seat. */
{
maze[seat.x][seat.y].mark=-1;
/* Marking ''''''''''''''''''''''''''''''''-1'''''''''''''''''''''''''''''''' symbolize the current position cannot be put. */
} /* MarkPrint */
void FootPrint(PosType curpos)
/* The foot of the curpos of the maze has been set ''''''''''''''''''''''''''''''''ue''''''''''''''''''''''''''''''''. */
{
maze[curpos.x][curpos.y].foot=1;
} /* FootPrint */
PosType NextPos(PosType seat,int di)
{
switch(di)
{
case 1: seat.y ; return seat; /* Eastward */
case 2: seat.x ; return seat; /* Southward */
case 3: seat.y--; return seat; /* Westward */
case 4: seat.x--; return seat; /* Northward */
default: seat.x=0; seat.y=0; return seat;
}
} /* NextPos */

/* The key to the program. */
/* Pre: The maze array & the startplace & the endplace.
Post: Find the one averse of the maze and perform the mazepath.
Uses: The ADT stack class.
*/
Status MazePath(PosType start,PosType end)
{
PosType curpos;
int curstep;
SElemType e;
Stack *s,stack;
stack.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
if(!stack.base) Error("Overflow");
stack.top=stack.base;
stack.stacksize=STACK_INIT_SIZE;
s=&stack;
curpos=start;
curstep=1;
do
{
if(Pass(curpos))
{
FootPrint(curpos);
e.ord=curstep; e.seat=curpos; e.di=1;
gotoxy((curpos.y 1)*2,curpos.x 2);
putch(''''''''''''''''''''''''''''''''@'''''''''''''''''''''''''''''''');
delay(8000); /* pospone time. */
Push(s,e);
if(curpos.x==end.x&&curpos.y==end.y) /* Proceed recursively. */
{
DesoyStack(s);
return TRUE;
}
curpos=NextPos(curpos,1); /* Try next position. */
curstep ;
}
else
{
if(!StackEmpty(s))
{
e=Pop(s,e); /* Removed e from s. */
while(e.di==4&&!StackEmpty(s)) /* Four directions have been checked
and s is not empty. */
{
MarkPrint(e.seat);
gotoxy((e.seat.y 1)*2,e.seat.x 2);
putch(''''''''''''''''''''''''''''''''@'''''''''''''''''''''''''''''''');
delay(8000); /* Pospone time. */
gotoxy((e.seat.y 1)*2,e.seat.x 2);
putch('''''''''''''''''''''''''''''''' '''''''''''''''''''''''''''''''');
e=Pop(s,e); /* Remove e from s. */
curstep--;
}
if(e.di<4) /* The current position hasnot been checked. */
{
e.di ;
Push(s,e); /* Insert e into s. */
curpos=NextPos(e.seat,e.di); /* Try next position. */
}
}
}
}
while(!StackEmpty(s));
DesoyStack(s);
return FALSE;
} /* MazePath */
void main()
{
PosType start,end;
CreatMaze();
start.x=StartPlace.y;
start.y=StartPlace.x;
end.x=EndPlace.y;
end.y=EndPlace.x;
if(MazePath(start,end))
{
gotoxy(2,22);
printf("Path found\n");
}
else
{
gotoxy(2,22);
printf("Path not found\n");
}
getch();
clrscr();
} 