#pragma once
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"
//#ifdef _Frame_h_
//define _Frame_h_


class MyDesk
{
public:
	MyDesk();
	void PlaceAnApple();
	bool MoveSnake(char direction);
	void GiveSnakeNewCoord(int length, int width, MySnake::Node*head);
	void PrintDeskSnakeAndApple();
	~MyDesk();
	char direction;
private:
	bool IsApplePlaceable(/*MyApple& apple*/);
	bool CanSnakeMove(char direction);
	bool** desk;
	MyApple* apple;
	MySnake* snake;
	QueueApplesInSnake* queue;
};

void PrintGame(MyDesk* desk);

void Commands(MyDesk* desk);
//#endif // _Frame_h_
