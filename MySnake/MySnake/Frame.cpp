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


MyDesk::MyDesk()
{
	this->direction = 'd';
	this->apple = new MyApple();
	this->snake = new MySnake(SNAKE_LENGTH);
	this->queue = new QueueApplesInSnake;

	this->desk = new bool*[DESK_LENGTH];
	for (int i = 0; i < DESK_LENGTH; i++)
	{
		this->desk[i] = new bool[DESK_WIDTH];
		for (int j = 0; j < DESK_WIDTH; j++)
		{
			
			this->desk[i][j] = false;
		}
	}
}
void MyDesk::PlaceAnApple()
{

	srand(time(NULL));
	do
	{
		this->apple->lengthCoord = rand() % DESK_LENGTH;
		this->apple->widthCoord = rand() % DESK_WIDTH;
	} while (!IsApplePlaceable(/*newApple*/));
}
bool MyDesk::IsApplePlaceable()
{
	MySnake::Node* buff = snake->head;
	while (buff != nullptr)
	{
		if (apple->lengthCoord == buff->lengthCoord && apple->widthCoord == buff->widthCoord)
		{
			return false;
		}
		buff = buff->pNext;
	}
	return true;
}
void MyDesk::GiveSnakeNewCoord(int length, int width, MySnake::Node* head)
{
	if (head->pNext != nullptr)
	{
		GiveSnakeNewCoord(head->pNext->lengthCoord, head->pNext->widthCoord, head->pNext);
	}
	if (head == snake->head)
	{
		head->pNext->lengthCoord = head->lengthCoord;
		head->pNext->widthCoord = head->widthCoord;
		snake->head->lengthCoord = length;
		snake->head->widthCoord = width;
	}
	else if (head->pNext == nullptr)
	{
		this->snake->tail = head;
	}
	else
	{
		head->pNext->lengthCoord = head->lengthCoord;
		head->pNext->widthCoord = head->widthCoord;	
	}
}
void MyDesk::PrintDeskSnakeAndApple()
{
	for (int i = 0; i < DESK_LENGTH+2; i++)
	{
		for (int j = 0; j < DESK_WIDTH+2; j++)
		{
			if (i == 0 && j == 0)
			{
				cout << "  ";
			}
			else if (i == 0 && j == 1)
			{
				cout << char(201) << char(205);
			}
			else if (i == 0 && j == DESK_WIDTH + 1)
			{
				cout << char(205) << char(205) << char(187);
			}
			else if (i == DESK_LENGTH + 1 && j == 0)
			{
				cout << "  ";
			}
			else if (i == DESK_LENGTH + 1 && j == 1)
			{
				cout << char(200) << char(205);
			}
			else if (i == DESK_LENGTH + 1 && j == DESK_WIDTH + 1)
			{
				cout << char(205) << char(205) << char(188);
			}
			else if (i == 0 || i == DESK_LENGTH + 1)
			{
				cout << char(205) << char(205) << char(205);
			}
			else if (j == 0)
			{
				cout << "  " << char(186);
			}
			else if (j == DESK_WIDTH + 1)
			{
				cout << char(186) << "  ";
			}

			else if (snake->CoordsCheck(i-1, j-1))
			{
				if (i == snake->head->lengthCoord+1 && j == snake->head->widthCoord+1)
				{
					cout << "[ ]";
				}
				else
				{
					cout << "( )";
				}
			}

			else if (i == apple->lengthCoord+1 && j == apple->widthCoord+1)
			{
				cout << " @ ";
			}

			else
			{
				cout << "   ";
			}
		}
		cout << endl;
	}
	cout << endl;
	/*for (int i = 0; i < DESK_LENGTH; i++)
	{
		for (int j = 0; j < DESK_WIDTH; j++)
		{
			if (snake->CoordsCheck(i,j))
			{
				if (i == snake->head->lengthCoord && j == snake->head->widthCoord)
				{
					cout << "[ ]";
				}
				else
				{
					cout << "( )";
				}
			}
			else if (i == apple->lengthCoord && j == apple->widthCoord)
			{
				cout << " @ ";
			}
			else
			{
				cout << "   ";
			}
		}
		cout << endl;
	}
	cout << endl;*/
}

bool MyDesk::MoveSnake(char direction)
{




	if (this->queue->first->apple != nullptr)
	{
		if (snake->tail->lengthCoord == queue->first->apple->lengthCoord && snake->tail->widthCoord == queue->first->apple->widthCoord)
		{
			snake->extend_tail();
			queue->TakeAppleOutOfQueue();
		}
	}
	switch (direction)
	{
		case 'w':
			{
				if (CanSnakeMove('w'))
				{
					GiveSnakeNewCoord(snake->head->lengthCoord - 1, snake->head->widthCoord, snake->head);
					if (snake->head->lengthCoord == apple->lengthCoord && snake->head->widthCoord == apple->widthCoord)
					{
						queue->AddAppleInQueue(apple, queue->first);
						PlaceAnApple();
					}
				}
				else
				{
					return false;
				}
				break;
			}
		case 'a':
			{
				if (CanSnakeMove('a'))
				{
					GiveSnakeNewCoord(snake->head->lengthCoord, snake->head->widthCoord - 1, snake->head);
					if (snake->head->lengthCoord == apple->lengthCoord && snake->head->widthCoord == apple->widthCoord)
					{
						queue->AddAppleInQueue(apple, queue->first);
						PlaceAnApple();
					}
				}
				else
				{
					return false;
				}
				break;
			}
		case 's':
		{
			if (CanSnakeMove('s'))
			{
				GiveSnakeNewCoord(snake->head->lengthCoord + 1, snake->head->widthCoord, snake->head);
				if (snake->head->lengthCoord == apple->lengthCoord && snake->head->widthCoord == apple->widthCoord)
				{
					queue->AddAppleInQueue(apple, queue->first);
					PlaceAnApple();
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case 'd':
		{
			if (CanSnakeMove('d'))
			{
				GiveSnakeNewCoord(snake->head->lengthCoord, snake->head->widthCoord + 1, snake->head);
				if (snake->head->lengthCoord == apple->lengthCoord && snake->head->widthCoord == apple->widthCoord)
				{
					queue->AddAppleInQueue(apple, queue->first);//
					PlaceAnApple();
				}
			}
			else
			{
				return false;
			}
			break;
		}
	}
	return true;
}
//mutex mtx;
bool MyDesk::CanSnakeMove(char direction)//
{
	//mtx.lock();
	MySnake::Node* buff = snake->head;
	switch (direction)
	{
		case 'w':
		{
			if (snake->head->lengthCoord - 1 == -1)
			{
				return false;
			}
			while (buff != nullptr)
			{
				if (snake->head->lengthCoord - 1 == buff->lengthCoord && snake->head->widthCoord == buff->widthCoord)
				{
					return false;
				}
				buff = buff->pNext;
			}
			break;
		}
		case 'a':
		{
			if (snake->head->widthCoord - 1 == -1)
			{
				return false;
			}
			while (buff != nullptr)
			{
				if (snake->head->lengthCoord == buff->lengthCoord && snake->head->widthCoord - 1 == buff->widthCoord)
				{
					return false;
				}
				buff = buff->pNext;
			}
			break;
		}
		case 's':
		{
			if (snake->head->lengthCoord + 1 == DESK_LENGTH)
			{
				return false;
			}
			while (buff != nullptr)
			{
				if (snake->head->lengthCoord + 1 == buff->lengthCoord && snake->head->widthCoord == buff->widthCoord)
				{
					return false;
				}
				buff = buff->pNext;
			}
			break;
		}
		case 'd':
		{
			if (snake->head->widthCoord + 1 == DESK_WIDTH)
			{
				return false;
			}
			while (buff != nullptr)
			{
				if (snake->head->lengthCoord == buff->lengthCoord && snake->head->widthCoord + 1 == buff->widthCoord)
				{
					return false;
				}
				buff = buff->pNext;
			}
			break;
		}
	}
	return true;
	//mtx.unlock();
}
MyDesk::~MyDesk()
{
	for (int i = 0; i < DESK_LENGTH; i++)
	{
		delete[] desk[i];
	}
	delete[] desk;
}


void PrintGame(MyDesk* desk)
{
	desk->PlaceAnApple();
	system("CLS");
	desk->PrintDeskSnakeAndApple();
	while (desk->MoveSnake(desk->direction))
	{
		system("CLS");
		desk->PrintDeskSnakeAndApple();
		Sleep(400);
	}
}

void Commands(MyDesk* desk)
{
	while (true)
	{
		char ch = _getch();
		switch (ch)
			{
			case 'w':
			{
				if (desk->direction != 's')
				{
					desk->direction = 'w';
				}
				break;
			}
			case 'a':
			{
				if (desk->direction != 'd')
				{
					desk->direction = 'a';
				}
				break;
			}
			case 's':
			{
				if (desk->direction != 'w')
				{
					desk->direction = 's';
				}
				break;
			}
			case 'd':
			{
				if (desk->direction != 'a')
				{
					desk->direction = 'd';
				}
				break;
			}
			default:
			{
				break;
			}
		}
		Sleep(400);//??
	}
}
