#include <iostream>
#include "Frame.h"
#include <string>
#include "windows.h"
#include <conio.h>
#include <mutex>
using namespace std;
#define TABLE_LENGTH 20
#define TABLE_WIDTH 12
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
			this->M[i][j] = false;
		}
	}
}
Figure::Figure(const Figure& other) {
	this->figureZeroLines = other.figureZeroLines;
	this->k = other.k;
	this->M = new bool* [other.k];
	for (int i = 0; i < k; i++)
	{
		this->M[i] = other.M[i];
		for (int j = 0; j < k; j++)
		{
			this->M[i][j] = other.M[i][j];
		}
	}
}
void Figure::TurnMatrix()
{
	bool** oldM = new bool*[k];
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
void TetrisDesk::SetNextFigure(Figure* figure)
{
	this->nextFigure = figure;
}
Figure* TetrisDesk::GetNextFigure()
{
	return this->nextFigure;
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
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int i = FIGURE_MATRIX_SIZE - 1 + stepDown; i >= stepDown; i--)
	{
		for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
		{
			if (figureMatrix[i - stepDown][0] || figureMatrix[i - stepDown][1] || figureMatrix[i - stepDown][2] || figureMatrix[i - stepDown][3])
			{
				if ((i + 1 - zeroLines > TABLE_LENGTH - 1))
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
		}
	}
	SetStepDown(++stepDown);
	return true;
}
bool TetrisDesk::MoveFigureRight() {
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int j = FIGURE_MATRIX_SIZE - 1 + stepSide; j >= stepSide; j--)
	{
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
		}

	}
	SetStepSide(++stepSide);
	return true;
}
bool TetrisDesk::MoveFigureLeft() {
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();

	for (int j = stepSide; j < stepSide + FIGURE_MATRIX_SIZE; j++)
	{
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
bool TetrisDesk::FullLineCheck(int lineId) {

	for (int j = 0; j < TABLE_WIDTH; j++)
	{
		if (!desk[lineId][j])
		{
			return false;
		}
	}
	return true;
}
void TetrisDesk::ClearFullLine(int lineId) {
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
			else if ( i <= lineId)
			{
				this->desk[i][j] = oldDesk[i - 1][j];
			}
			else 
			{
				this->desk[i][j] = oldDesk[i][j];
			}
		}
	}
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		delete[] oldDesk[i];
	}
	delete[] oldDesk;
}
mutex mtx;
void TetrisDesk::PrintFigureAndDesk()
{
	mtx.lock();
	system("CLS");
	bool** nextMatrix = nextFigure->GetFigureMatrix();
	bool** figureMatrix = figure->GetFigureMatrix();
	int zeroLines = figure->GetZerolines();
	for (int i = 0; i < TABLE_LENGTH + 2; i++)
	{
		for (int j = 0; j < TABLE_WIDTH + 2; j++)
		{
			if (i == 0 && j == 0)
			{
				cout << "  ";
			}
			else if(i == 0 && j == 1)
			{
				cout << char(201) << char(205);
			}
			else if (i == 0 && j == TABLE_WIDTH + 1)
			{
				cout << char(205) << char(205) << char(187) << "\t" << char(201) << char(205)  << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187);//
			}
			else if (i == 1 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(177) << char(177) << char(178) << char(178) << "TETRIS" << char(178) << char(178) << char(177) << char(177) << char(176) << char(186);
			}
			else if (i == 2 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
			}
			else if (i == 3 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << Cube(nextMatrix[0][0])+ Cube(nextMatrix[0][1])+ Cube(nextMatrix[0][2])+ Cube(nextMatrix[0][3]) << char(176) << char(176) << char(186);
			}
			else if (i == 4 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << Cube(nextMatrix[1][0]) + Cube(nextMatrix[1][1]) + Cube(nextMatrix[1][2]) + Cube(nextMatrix[1][3]) << char(176) << char(176) << char(186);
			}
			else if (i == 5 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << Cube(nextMatrix[2][0]) + Cube(nextMatrix[2][1]) + Cube(nextMatrix[2][2]) + Cube(nextMatrix[2][3]) << char(176) << char(176) << char(186);
			}
			else if (i == 6 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << Cube(nextMatrix[3][0]) + Cube(nextMatrix[3][1]) + Cube(nextMatrix[3][2]) + Cube(nextMatrix[3][3]) << char(176) << char(176) << char(186);
			}
			else if (i == 7 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
			}
			else if (i == 8 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "NEXT  FIGURE" << char(176) << char(176) << char(186);
			}
			else if (i == 9 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << "                " << char(186);
			}
			else if (i == 10 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << " MOVE LEFT :  < " << char(186);
			}
			else if (i == 11 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << "                " << char(186);
			}
			else if (i == 12 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << " MOVE RIGHT : > " << char(186);
			}
			else if (i == 13 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << "                " << char(186);
			}
			else if (i == 14 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << " MOVE DOWN :  v " << char(186);
			}
			else if (i == 15 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << "                " << char(186);
			}
			else if (i == 16 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << " ROTATE :     c " << char(186);
			}
			else if (i == 17 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(186) << "                " << char(186);
			}
			else if (i == 18 && j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  " << "\t" << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);//
			}
			else if (i == TABLE_LENGTH + 1 && j == 0)
			{
				cout <<"  ";
			}
			else if (i == TABLE_LENGTH + 1 && j == 1)
			{
				cout << char(200) << char(205);
			}
			else if (i == TABLE_LENGTH + 1 && j == TABLE_WIDTH + 1)
			{
				cout << char(205) << char(205) << char(188);
			}

			else if (i == 0 || i == TABLE_LENGTH + 1)
			{
				cout << char(205) << char(205) << char(205);
			}
			else if (j == 0)
			{
				cout << "  " << char(186);
			}
			else if (j == TABLE_WIDTH + 1)
			{
				cout << char(186) << "  ";
			}
			else if ((i >= stepDown - zeroLines + 1) && (i < stepDown + FIGURE_MATRIX_SIZE - zeroLines + 1) && (j >= stepSide + 1) && (j < (stepSide + FIGURE_MATRIX_SIZE + 1)))
			{
				if (figureMatrix[i - stepDown + zeroLines - 1][j - stepSide - 1])
				{
					cout << Cube(true);
				}
				else
				{
					cout << Cube(desk[i - 1][j - 1]);
				}
			}
			else
			{
				cout << Cube(desk[i - 1][j - 1]);
			}
		}
		cout << endl;
	}
	mtx.unlock();
}
TetrisDesk::~TetrisDesk() {
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		delete[] desk[i];
	}
	delete[] desk;
}
void PrintStart()
{
	for (int i = 0; i < TABLE_LENGTH + 2; i++)
	{
		if (i == 0)
		{
			cout << "  " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << "   \t" << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187);
		}
		else if (i == 1)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(177) << char(177) << char(178) << char(178) << "TETRIS" << char(178) << char(178) << char(177) << char(177) << char(176) << char(186);
		}
		else if (i == 2)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
		}
		else if (i == 3)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 4)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 5)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 6)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}

		else if (i == 7)
		{
			cout << "  " << char(186) << "           PRESS ANY KEY            " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
		}
		else if (i == 8)
		{
			cout << "  " << char(186) << "              TO START              " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "NEXT  FIGURE" << char(176) << char(176) << char(186);
		}

		else if (i == 9)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 10)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " MOVE LEFT :  < " << char(186);
		}
		else if (i == 11)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 12)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " MOVE RIGHT : > " << char(186);
		}
		else if (i == 13)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 14)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " MOVE DOWN :  v " << char(186);
		}
		else if (i == 15)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 16)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " ROTATE :     c " << char(186);
		}
		else if (i == 17)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 18)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);//
		}
		else if (i == 19)
		{
			cout << "  " << char(186) << "                                    " << char(186);
		}
		else if (i == 20)
		{
			cout << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
		}

		cout << endl;
	}	
	 _getch();	
}
void TetrisDesk::PrintEnd(TetrisDesk* nextTetris)
{
	for (int i = 0; i < TABLE_LENGTH + 2; i++)
	{
		if (i == 0)
		{
			cout << "  " << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << "   \t" << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187);
		}
		else if (i == 1)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(177) << char(177) << char(178) << char(178) << "TETRIS" << char(178) << char(178) << char(177) << char(177) << char(176) << char(186);
		}
		else if (i == 2)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
		}
		else if (i == 3)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 4)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 5)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}
		else if (i == 6)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "            " << char(176) << char(176) << char(186);
		}

		else if (i == 7)
		{
			cout << "  " << char(186) << "                 GAME               " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(186);
		}
		else if (i == 8)
		{
			cout << "  " << char(186) << "                 OVER               " << char(186) << "  " << "\t" << char(186) << char(176) << char(176) << "NEXT  FIGURE" << char(176) << char(176) << char(186);
		}

		else if (i == 9)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 10)
		{
			cout << "  " << char(186) << "                PRESS R             " << char(186) << "  " << "\t" << char(186) << " MOVE LEFT :  < " << char(186);
		}
		else if (i == 11)
		{
			cout << "  " << char(186) << "               TO RESTART           " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 12)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " MOVE RIGHT : > " << char(186);
		}
		else if (i == 13)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 14)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " MOVE DOWN :  v " << char(186);
		}
		else if (i == 15)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 16)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << " ROTATE :     c " << char(186);
		}
		else if (i == 17)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(186) << "                " << char(186);
		}
		else if (i == 18)
		{
			cout << "  " << char(186) << "                                    " << char(186) << "  " << "\t" << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);//
		}
		else if (i == 19)
		{
			cout << "  " << char(186) << "                                    " << char(186);
		}
		else if (i == 20)
		{
			cout << "  " << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
		}

		cout << endl;
	}
	char ch;
	ch = _getch();
	switch (ch)
	{
		case 'r':
		{
			PrintGame(nextTetris);
			break;
		}
		case 'R':
		{
			PrintGame(nextTetris);
			break;
		}
		default:
		{
			break;
		}
	}
}

void TetrisDesk::ClearDesk() 
{
	for (int i = 0; i < TABLE_LENGTH; i++)
	{
		for (int j = 0; j < TABLE_WIDTH; j++)
		{
			this->desk[i][j] = false;
		}
	}
}
void PrintGame(TetrisDesk* myTetris)
{
	system("CLS");
	myTetris->SetFigure(FigureCall());
	while (true)
	{
		myTetris->SetNextFigure(FigureCall());
		if (myTetris->CurrentFigureOnDesk())
		{
			do
			{
				myTetris->PrintFigureAndDesk();
				Sleep(700);
			} while (myTetris->MoveFigureDown());
			myTetris->WriteFigureOnDesk();
			myTetris->SetStepDown(0);
			myTetris->SetStepSide((TABLE_WIDTH - FIGURE_MATRIX_SIZE) / 2);
			for (int i = 0; i < TABLE_LENGTH; i++)
			{
				while (myTetris->FullLineCheck(i))
				{
					myTetris->ClearFullLine(i);
				}
			}
			myTetris->SetFigure(myTetris->GetNextFigure());
		}
		else
		{
			system("CLS");
			//TetrisDesk* nextTetris = new TetrisDesk;
			myTetris->ClearDesk();
			myTetris->PrintEnd(myTetris);
			break;
		}
	}
};

void CommandsPanel(TetrisDesk* myTetris)
{
	char command;
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