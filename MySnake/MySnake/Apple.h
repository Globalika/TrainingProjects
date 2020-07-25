#pragma once
#include "Frame.h"
#include "Snake.h"
#include "Queue.h"
#include "Apple.h"

struct MyApple
{
	MyApple();
	MyApple& operator = (const MyApple& other);
	MyApple(const MyApple& other);
	bool apple;
	int lengthCoord;
	int widthCoord;
};