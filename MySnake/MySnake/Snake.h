#pragma once
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"

class MySnake
{
public:
	class Node
	{
	public:
		bool data;
		Node* pNext;
		int lengthCoord;
		int widthCoord;
		Node(bool data = true, Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->lengthCoord = 0;
			this->widthCoord = 0;
		}
	};
public:
	MySnake(int size);
	bool CoordsCheck(int length, int width);
	void extend_tail();
	~MySnake();
	int size;
	Node* head;
	Node* tail;	
};
#pragma once
