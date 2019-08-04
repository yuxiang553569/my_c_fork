#include "snake.cpp"

void main()
{
	//welcome to play the game
	graph_welcome();
	
	//delay
	Sleep(1000);

	//the game page layout view
	graph_game();

	//initialize the snake and food
	initial();

	//begin the game
	begin_game();
}//end main