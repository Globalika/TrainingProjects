#pragma once
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"

class QueueApplesInSnake
{
	class AppleNode
	{
	public:
		MyApple* apple;
		AppleNode* pNext;
		AppleNode(MyApple* apple, AppleNode* pNext = nullptr)
		{
			this->apple = apple;
			this->pNext = pNext;
		}
	};
public:
	AppleNode* first;
	int size;
	QueueApplesInSnake();
	void AddAppleInQueue(MyApple* apple, AppleNode* first);
	void TakeAppleOutOfQueue();
	~QueueApplesInSnake();
}; 
