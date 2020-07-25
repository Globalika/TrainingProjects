#include <iostream>
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"
#include "windows.h"
#include <thread>
using namespace std;

int main()
{
	/*MyApple* apple1 = new MyApple;
	apple1->lengthCoord = 1;
	MyApple* apple2 = new MyApple;
	apple2->lengthCoord = 2;
	MyApple* apple3 = new MyApple;
	apple3->lengthCoord = 3;
	QueueApplesInSnake queue;
	queue.AddAppleInQueue(apple1,);
	queue.AddAppleInQueue(apple2);
	queue.AddAppleInQueue(apple3);*/


	MyDesk* newDesk = new MyDesk;
	thread t(Commands, newDesk);
	PrintGame(newDesk);
	t.detach();


	/*while (true)
	{
		system("CLS");
		newDesk->PrintDeskSnakeAndApple();
		Sleep(300);
		newDesk->MoveSnake(newDesk->direction);
		newDesk->direction = 'w';
		system("CLS");
		newDesk->PrintDeskSnakeAndApple();
		Sleep(300);
		newDesk->MoveSnake(newDesk->direction);
		newDesk->direction = 'd';
	}*/
	return 0;
}