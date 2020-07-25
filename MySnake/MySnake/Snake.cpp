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


MySnake::MySnake(int size)
{
	this->size = size;
	this->head = new Node;
	head->lengthCoord = DESK_LENGTH - 1;
	head->widthCoord = DESK_WIDTH / 2;
	Node* buff = head;
	if (size > 1)
	{
		while (--size)
		{
			buff->pNext = new Node;
			buff->pNext->lengthCoord = buff->lengthCoord;
			buff->pNext->widthCoord = buff->widthCoord - 1;
			buff = buff->pNext;
		}
	}
	this->tail = buff;
}
bool MySnake::CoordsCheck(int length, int width)
{
	Node* buff = head;
	while (buff != nullptr)
	{
		if (buff->lengthCoord == length && buff->widthCoord == width)
		{
			return true;
		}
		buff = buff->pNext;
	}
	delete[] buff;
	return false;
}
void MySnake::extend_tail()
{
	tail->pNext = new Node;
	tail->pNext->lengthCoord = tail->lengthCoord;
	tail->pNext->widthCoord = tail->widthCoord;
	size++;
}
MySnake::~MySnake()
{
	do
	{
		Node* temp = head;
		head = head->pNext;
		delete[] temp;
	} while (--size);
}
