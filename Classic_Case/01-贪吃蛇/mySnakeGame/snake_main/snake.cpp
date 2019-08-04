//a snake game
//2009,6,12

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#include"ConsoleOut.h"
#pragma comment (lib, "ConsoleOut.lib")

#define NULL 0

//create the location
struct location
{
	int x;
	int y;
};
typedef struct location Point;

//create the list for snake
struct snake
{
	Point value;
	struct snake *next;
};
typedef struct snake node;

//define the first snake and food
node *head = (node *)malloc(sizeof(node));
node *end = (node *)malloc(sizeof(node));
Point food;
static unsigned int food_num;//the food number

//void main();

//draw the welcome graphics
void graph_welcome(void);

//draw the game graphics
void graph_game(void);

//initialize the game
//add a two node snake and a food
void initial(void);

//show the snake
void show_snake(void);

//show the food
void show_food(void);

//begin the game
void begin_game(void);

//judge the snake is die or not
//if die, return 1, else return 0
int if_die(void);

//create the food, and return the location
void creat_food(void);

//add the snake's node
void add_snake(void);

//move the snake
void move(void);

//get the direction of the player input
int get_direction(void);

//acquiesce direction
int acquiesce(void);

//over the game
void end_game(void);



/*.......................................the function............................................*/

//the welcome graph
void graph_welcome(void)
{
	CreateSmWindow(4, 1, 60, 20, 12, 0, 2, 1, "Snake Game", false);
	
	MoveCursorTo(4, 5);

	SetTextColor(12, 1);
	MoveCursorTo(22, 5);
	printf("Welcome to play the snake game!");

	MoveCursorTo(17, 10);
	printf("游戏规则:\t向左:a\t向右:d");
	MoveCursorTo(17,11);
	printf("\t\t向上:w\t向下:s");
}

//the game page layout
void graph_game(void)
{
	system("CLS");
	CreateSmWindow(4, 1, 60, 20, 12, 0, 2, 1, "Snake Game", false);
}

//initialize the snake and the food
void initial(void)
{
	//initialize the sanke's head location
	head->value.x = 22;
	head->value.y = 10;
	head->next = end;

	//initialize the snake's end location
	end->value.x = 21;
	end->value.y = 10;
	end->next = NULL;

	//initialize the food
	creat_food();
}

//begin the game
void begin_game(void)
{
	while(1)
	{
		//show the snake and food
		show_snake();
		show_food();

		move();//move

		//judge if snake eat food
		if(head->value.x == food.x && head->value.y == food.y)
		{
			add_snake();
			creat_food();
		}

		//judge if die
		if(if_die())
		{
			end_game();
		}

	}
}

//create the food 
void creat_food(void)
{
	srand(food_num + 1);
	food.x = rand()%29 + 3;
	food_num++;
	food.y = rand()%19 + 2;
}

//add the snake node
void add_snake(void)
{
	node *new_head = (node *)malloc(sizeof(node));
	node *temp = (node *)malloc(sizeof(node));
	int direct = acquiesce();

	new_head->next = head;
	new_head->value = head->value;

	switch(direct)
	{
	case 1:
		{
			new_head->value.y --;
		}break;
	case 2:
		{
			new_head->value.y ++;
		}break;
	case 3:
		{
			new_head->value.x --;
		}break;
	case 4:
		{
			new_head->value.x ++;
		}break;
	}

	temp = head;
	head = new_head;
	new_head = temp;

}

//get the direction
int get_direction(void)
{
	//char direct;
	int direction = 0;
	int calculagraph = 0;

//	direct = getchar();
	while(1)
	{
		if(kbhit())
		{
			switch(getch())
			{
    		case 'w':
				{
					direction = 1;
				}break;
    		case 's':
				{
					direction = 2;
				}break;
    		case 'a':
				{
					direction = 3;
				}break;
    		case 'd':
				{
					direction = 4;
				}break;
			}
		}

		if(direction != 0)
			break;
		else
		{
			Sleep(100 - food_num);
			calculagraph++;

			if(calculagraph == 4)
			{
				direction = acquiesce();
				break;
			}
		}
	};
	

	return direction;
}

//acquiesce direction
int acquiesce(void)
{
	if(head->value.y < head->next->value.y)
	{
		return 1;//acquiesce up
	}
	else if(head->value.y > head->next->value.y)
	{
		return 2;//acquiesce down
	}
	else if(head->value.x < head->next->value.x)
	{
		return 3;//acquiesce left
	}
	else
	{
		return 4;//acquiesce right
	}
}

//move the snake
void move(void)
{
	int locat_x[100] = {0};
	int locat_y[100] = {0};
	node *temp = (node *)malloc(sizeof(node));
	int i;

	temp = head;

	//store the value of every node
	for(i = 0; temp->next != NULL; temp = temp->next)
	{
		locat_x[i] = temp->value.x;
		locat_y[i] = temp->value.y;
		i++;
	}

	//move the head
	switch(get_direction())
	{
	case 1:
		{
			head->value.y--;
		}break;
	case 2:
		{
			head->value.y++;
		}break;
	case 3:
		{
			head->value.x--;
		}break;
	case 4:
		{
			head->value.x++;
		}
	}

	//clear the trace
	MoveCursorTo(end->value.x * 2, end->value.y);
	SetTextColor(12, 1);
	printf(" ");

	//move the other nodes
	temp = head;
	i = 0;
	for(; temp->next != NULL; temp = temp->next)
	{
		temp->next->value.x = locat_x[i];
		temp->next->value.y = locat_y[i];
		i++;
	}

}

//show the snake
void show_snake(void)
{
	node *temp = (node *)malloc(sizeof(node));

	temp = head;

	for(; temp->next != NULL; temp = temp->next)
	{
		MoveCursorTo(temp->value.x * 2, temp->value.y);
		printf("●");
	}
	//show the end node
	MoveCursorTo(end->value.x * 2, end->value.y);
	printf("●");//show the end

}

//show the food
void show_food(void)
{
	MoveCursorTo(food.x * 2, food.y);
	printf("★");
}

//judge the snake if die
//if die, return 1,
//else return 0
int if_die(void)
{
	int die = 0;
	node *temp = (node *)malloc(sizeof(node));
	temp = head;

	//judge if touch the boundary
	if((temp->value.x == 2) || (temp->value.x == 33)||
		(temp->value.y == 1) || (temp->value.y == 22))
	{
		die = 1;
	}
	else if(1)
	{
		//judge if touch itself
		for(;temp->next != NULL; temp = temp->next)
		{
	    	if(head->value.x == temp->next->value.x && head->value.y == temp->next->value.y)
			{
				die = 1;
				break;
			}
		}
	}
	else
	{
		die = 0;
	}

	return die;

}

//over the game
void end_game(void)
{
	system("CLS");
	CreateSmWindow(4, 1, 60, 20, 12, 0, 2, 1, "Snake Game", false);
	
	MoveCursorTo(4, 5);

	SetTextColor(12, 1);
	MoveCursorTo(17, 10);
	printf("OVER THE GAME!");

	Sleep(1000);

	exit(1);
}
