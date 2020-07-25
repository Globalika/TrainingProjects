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

MyApple::MyApple()
{
	this->apple = true;
	this->lengthCoord = 0;
	this->widthCoord = 0;
}
//MyApple& MyApple::operator =(const MyApple& other)
//{
//	this->apple = other.apple;
//	this->lengthCoord = other.lengthCoord;
//	this->widthCoord = other.widthCoord;
//	return *this;
//}

MyApple::MyApple(const MyApple& other)
{
	this->apple = other.apple;
	this->lengthCoord = other.lengthCoord;
	this->widthCoord = other.widthCoord;
}