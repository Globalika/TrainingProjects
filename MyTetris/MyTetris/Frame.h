#pragma once

class Figure {
public:
	Figure();
	void TurnMatrix();
	bool**& GetFigureMatrix();
	int GetZerolines();
	~Figure();
protected:
	void ZeroLinesCount();
	int k;
	bool** M;
	int figureZeroLines;
};
class Figure1 : public Figure {
public:
	Figure1();
};
class Figure2 : public Figure{
public:
	Figure2();
};
class Figure3 : public Figure{
public:
	Figure3();
};
class Figure4 : public Figure{
public:
	Figure4();
};
class Figure5 : public Figure{
public:
	Figure5();
};
class Figure6 : public Figure{
public:
	Figure6();
};
class Figure7 : public Figure{
public:
	Figure7();
};
void SelectFigurePosition(Figure*& myFigure, int position);
Figure*& FigureCall();
//class Cube {
//public:
//	void Result(bool a);
//private:
//	bool cube;
//};
std::string Cube(bool cube);
class TetrisDesk {
public:
	TetrisDesk();
	void SetFigure(Figure* figure);
	void SetStepDown(int stepDown);//??
	void SetStepSide(int stepSide);
	bool CurrentFigureOnDesk();//can i add new figure on desk?
	bool MoveFigureDown();//can i move this figure one line down?
	bool MoveFigureRight();
	bool MoveFigureLeft();
	bool TurnFigure();
	void PrintFigureAndDesk();//print everything at this moment
	void WriteFigureOnDesk();//write current figure on desk
	bool FullLineCheck();
	void ClearFullLine();
	bool** GetDesk();
	void PrintStep()
	{
		std::cout << this->stepDown << std::endl;
	}
	~TetrisDesk();
private:
	bool** desk;
	Figure* figure;
	int stepDown;
	int stepSide;
};

void PrintGame(TetrisDesk* myTetris);

void CommandsPanel(TetrisDesk* myTetris);