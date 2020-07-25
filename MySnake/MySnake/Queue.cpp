#include <iostream>
#include <ctime>
#include <map>
#include "windows.h"
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"
#include <conio.h>
#include <mutex>
using namespace std;
#define DESK_LENGTH  20
#define DESK_WIDTH  16
#define SNAKE_LENGTH  3

QueueApplesInSnake::QueueApplesInSnake()
{
	size = 0;
	first = new AppleNode(nullptr, nullptr);
}

void QueueApplesInSnake::AddAppleInQueue(MyApple* apple, AppleNode* first)
{
	
	if (first->apple != nullptr)
	{
		AddAppleInQueue(apple, first->pNext);
	}
	if (first->pNext == nullptr)
	{
		MyApple* newApple = new MyApple(*apple);//11!!
		first->apple = newApple;
		first->pNext = new AppleNode(nullptr, nullptr);
		size++;
	}
}

void QueueApplesInSnake::TakeAppleOutOfQueue()
{
	QueueApplesInSnake::AppleNode* buff = first;
	first = first->pNext;
	delete[] buff;
	size--;
}
QueueApplesInSnake::~QueueApplesInSnake()
{
	do
	{
		AppleNode* temp = first;
		first = first->pNext;
		delete[] temp;
	} while (--size);
}