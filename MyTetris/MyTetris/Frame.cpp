#include <iostream>
#include "Frame.h"
#include "Timer.h"
#include <string>
#include <ctime>
#include "windows.h"
#include <conio.h>
using namespace std;
#define TABLE_LENGTH 24
#define TABLE_WIDTH 16
#define FIGURE_MATRIX_SIZE 4  

Figure::Figure() {
	this->figureZeroLines = 0;
	this->k = FIGURE_MATRIX_SIZE;
	this->M = new bool* [k];
	for (int i = 0; i < k; i++)
	{
		this->M[i] = new bool[k];
		for (int j = 0; j < k; j++)
		{
			M[i][j] = false;
		}
	}
}
void Figure::TurnMatrix()
{
	bool** oldM = new bool* [k];
	for (int i = 0; i < k; i++)
	{
		oldM[i] = new bool[k];
		for (int j = 0; j < k; j++)
		{
			oldM[i][j] = this->M[i][j];
		}
	}
	int t = k;
	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; j++)
		{
			--t;
			this->M[i][j] = oldM[t][i];
		}
		t = k;
	}
	ZeroLinesCount();
	for (int i = 0; i < k; i++)
	{
		delete[] oldM[i];
	}
	delete[] oldM;
	
}
void Figure::ZeroLinesCount() {
	int stepDownsFromTop = 0;
	int h = 0;
	for (int i = 0; i < FIGURE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < FIGURE_MATRIX_SIZE; j++)
		{
			if (this->M[i][j]) {
				break;
			}
			else {
				h++;
			}
		}
		if (h == 4) {
			stepDownsFromTop++;
			h = 0;
		}
		else {
			break;
		}
	}
	this->figureZeroLines = stepDownsFromTop;
}
bool**& Figure::GetFigureMatrix() {
	return *&M;
}
int Figure::GetZerolines() {
	return figureZeroLines;
}
Figure1::Figure1() : Figure() {
	this->M[0][0] = true;
	this->M[1][0] = true;
	this->M[2][0] = true;
	this->M[3][0] = true;
}
Figure2::Figure2() : Figure() {
	this->M[0][0] = true;
	this->M[1][0] = true;
	this->M[1][1] = true;
	this->M[2][1] = true;
}
Figure3::Figure3() : Figure() {
	this->M[0][1] = true;
	this->M[1][0] = true;
	this->M[1][1] = true;
	this->M[1][2] = true;
}
Figure4::Figure4() : Figure() {
	this->M[0][0] = true;
	this->M[1][0] = true;
	this->M[2][0] = true;
	this->M[2][1] = true;
}
Figure5::Figure5() : Figure() {
	this->M[0][1] = true;
	this->M[1][1] = true;
	this->M[2][0] = true;
	this->M[2][1] = true;
}
Figure6::Figure6() : Figure() {
	this->M[0][0] = true;
	this->M[0][1] = true;
	this->M[1][0] = true;
	this->M[1][1] = true;
}
Figure7::Figure7() : Figure() {
	this->M[0][1] = true;
	this->M[1][0] = true;
	this->M[1][1] = true;
	this->M[2][0] = true;
}
Figure*& FigureCall()
{
	srand(time(NULL));
	int randFigure = rand() % 7;
	int randTurnFigure = rand() % 4;
	Figure* figure;
	switch (randFigure + 1)
	{
		case 1:
		{
			figure = new Figure1;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 2:
		{
			figure = new Figure2;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 3:
		{
			figure = new Figure3;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 4:
		{
			figure = new Figure4;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 5:
		{
			figure = new Figure5;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 6:
		{
			figure = new Figure6;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		case 7:
		{
			figure = new Figure7;
			SelectFigurePosition(figure, randTurnFigure);
			break;
		}
		default:
		{
			figure = new Figure;
			break;
		}
	}
	
	return *&figure;
}
Figure::~Figure() {
	for (int i = 0; i < k; i++)
	{
		delete[] M[i];
	}
	delete[] M;
}
void SelectFigurePosition(Figure*& myFigure, int position) {
	for (int i = 0; i < position; i++)
	{
		myFigure->TurnMatrix();
	}
}
//void Cube::Result(bool a)
//{
//	if (a == 0)
//	{
//		cout << "   ";
//	}
//	else {
//		cout << "[ ]";
//	}
//}
string Cube(bool cube) {
	if (cube)
	{
		return "[ ]";
	}
	else
	{
		return "   ";
	}
}
TetrisDesk::TetrisDesk() {
	this->desk = new bool* [TABLE_LENGTH];
	for (int i = 0; i < TABLE_LENGTH; i++) {
		this->desk[i] = new bool[TABLE_WIDTH];
		for (int j = 0; j < TABLE_WIDTH; j++)
		{
			this->desk[i][j] = false;
		}
	}
	this->stepDown = 0;
	this->stepSide = (TABLE_WIDTH - FIGURE_MATRIX_SIZE) / 2;
	figure = new Figure;
}
void TetrisDesk::SetFigure(Figure* figure) {
	this->figure = figure;
}
void TetrisDesk::SetStepDown(int stepDown) {
	this->stepDown = stepDown;
}
void TetrisDesk::SetStepSide(int stepSide) {
	this->stepSide = stepSide;
}
bool** TetrisDesk::GetDesk() {
	return this->desk;
}
bool TetrisDesk::CurrentFigureOnDesk() {
	int k;
	int zeroLines = figure->GetZerolines();
	bool** figureMatrix = figure->GetFigureMatrix();

	for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown; i >= stepDown; i--)
	{
		k = 0;
		for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
		{
			if (figureMatrix[i - stepDown][0] || figureMatrix[i - stepDown][1] || figureMatrix[i - stepDown][2] || figureMatrix[i - stepDown][3])
			{
				if (i + 1 - zeroLines > 23)
				{
					return false;
				}
				if ((figureMatrix[i - stepDown][k] && desk[i - zeroLines][j]))
				{
					return false;
				}
			}
			else
			{
				break;
			}
			k++;
		}
	}
	return true;
}
bool TetrisDesk::MoveFigureDown()
{
	//int k;
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown; i >= stepDown; i--)
	{
		//k = 0;
		for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
		{
			if (figureMatrix[i - stepDown][0] || figureMatrix[i - stepDown][1] || figureMatrix[i - stepDown][2] || figureMatrix[i - stepDown][3])
			{
				if ((i + 1 - zeroLines > 23))//!!!!!!!!!!!!
				{
					return false;
				}
				if ((figureMatrix[i - stepDown][j - stepSide] && desk[i + 1 - zeroLines][j]))
				{
					return false;
				}
			}
			else
			{
				break;
			}
			//k++;
		}
	}
	SetStepDown(++stepDown);
	return true;
}
bool TetrisDesk::MoveFigureRight() {
	//int k;
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int j = FIGURE_MATRIX_SIZE - 1 + stepSide; j >= stepSide; j--)
	{
		//k = 0;
		for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown; i >= stepDown; i--)
		{
			if (figureMatrix[0][j - stepSide] || figureMatrix[1][j - stepSide] || figureMatrix[2][j - stepSide] || figureMatrix[3][j - stepSide])
			{
				if (j + 1 > TABLE_WIDTH - 1)
				{
					return false;
				}
				if ((figureMatrix[i - stepDown][j - stepSide] && desk[i - zeroLines][j + 1]))
				{
					return false;
				}
			}
			else
			{
				break;
			}
			//k++;
		}

	}
	SetStepSide(++stepSide);
	return true;
}
bool TetrisDesk::MoveFigureLeft() {
	//int k;
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
	{
		//k = 0;
		for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown; i >= stepDown; i--)
		{
			if (figureMatrix[0][j - stepSide] || figureMatrix[1][j - stepSide] || figureMatrix[2][j - stepSide] || figureMatrix[3][j - stepSide])
			{
				if (j - 1 < 0)
				{
					return false;
				}
				if ((figureMatrix[i - stepDown][j - stepSide] && desk[i - zeroLines][j - 1]))
				{
					return false;
				}
			}
			else
			{
				break;
			}
			//k++;
		}
	}
	SetStepSide(--stepSide);
	return true;
}
bool TetrisDesk::TurnFigure() {
	//Figure* buffFigure = *&figure;
	

	figure->TurnMatrix();

	if (CurrentFigureOnDesk())
	{
		return true;
	}
	else 
	{
		SelectFigurePosition(figure, 3);
		//figure = buffFigure;
		return false;
	}
}
void TetrisDesk::WriteFigureOnDesk() {
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();
	int k;
	for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown - zeroLines; i >= stepDown; i--)
	{
		k = 0;
		for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
		{
			if (figureMatrix[i - stepDown + zeroLines][0] || figureMatrix[i - stepDown + zeroLines][1] || figureMatrix[i - stepDown + zeroLines][2] || figureMatrix[i - stepDown + zeroLines][3])
			{
				if (figureMatrix[i - stepDown + zeroLines][k])
				{
					this->desk[i][j] = figureMatrix[i - stepDown + zeroLines][k];
				}
			}
			k++;
		}
	}

}
bool TetrisDesk::FullLineCheck() {
	for (int i = 0; i < TABLE_WIDTH; i++)
	{
		if (!desk[TABLE_LENGTH - 1][i])
		{
			return false;
		}
	}
	return true;
}
void TetrisDesk::ClearFullLine() {
	bool** oldDesk = new bool* [TABLE_LENGTH];
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		oldDesk[i] = new bool[TABLE_WIDTH];
		for (int j = 0; j < TABLE_WIDTH; j++)
		{
			oldDesk[i][j] = this->desk[i][j];
		}
	}

	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		for (int j = 0; j < TABLE_WIDTH; j++)
		{
			if (i == 0)
			{
				this->desk[i][j] = false;
			}
			else 
			{
				this->desk[i][j] = oldDesk[i - 1][j];
			}
		}
	}
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		delete[] oldDesk[i];
	}
	delete[] oldDesk;
}
void TetrisDesk::PrintFigureAndDesk()
{
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();
	//int k;
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		//k = 0;
		for (int j = 0; j < TABLE_WIDTH; j++)
		{
			if ((i >= stepDown - zeroLines) && (i < stepDown + FIGURE_MATRIX_SIZE - zeroLines) && (j >= /*(TABLE_WIDTH - FIGURE_MATRIX_SIZE) / 2*/stepSide) && (j < (/*(TABLE_WIDTH - FIGURE_MATRIX_SIZE) / 2*/stepSide + FIGURE_MATRIX_SIZE)))
			{
				if (figureMatrix[i - stepDown + zeroLines][j - stepSide])
				{
					cout << Cube(true) /*<< " "*/;
				}
				else
				{
					cout << Cube(desk[i][j]) /*<< " "*/;
				}
				//k++;
			}
			else
			{
				cout << Cube(desk[i][j]) /*<< " "*/;
			}
		}
		cout << endl;
	}
}
TetrisDesk::~TetrisDesk() {
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		delete[] desk[i];
	}
	delete[] desk;
}



void PrintGame(TetrisDesk* myTetris)
{
	while (true)
	{
		myTetris->SetFigure(FigureCall());
		if (myTetris->CurrentFigureOnDesk())
		{
			do
			{
				system("CLS");
				myTetris->PrintFigureAndDesk();
				Sleep(700);
			} while (myTetris->MoveFigureDown());
			myTetris->WriteFigureOnDesk();
			myTetris->SetStepDown(0);
			myTetris->SetStepSide((TABLE_WIDTH - FIGURE_MATRIX_SIZE) / 2);
			while (myTetris->FullLineCheck())
			{
				myTetris->ClearFullLine();
			}
		}
		else
		{
			system("CLS");
			cout << "noob" << endl;
			break;
		}
	}
};

void CommandsPanel(TetrisDesk* myTetris)
{
	char command;
	//getch();
	while (true)
	{
		command = _getch();
		switch (command)
		{
			case ',':
			{
				myTetris->MoveFigureLeft();
				break;
			}
			case '.':
			{
				myTetris->MoveFigureRight();
				system("CLS");
				myTetris->PrintFigureAndDesk();
				break;
			}
			case 'v':
			{
				myTetris->MoveFigureDown();
				system("CLS");
				myTetris->PrintFigureAndDesk();
				break;
			}
			case 'c':
			{
				myTetris->TurnFigure();
				system("CLS");
				myTetris->PrintFigureAndDesk();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}