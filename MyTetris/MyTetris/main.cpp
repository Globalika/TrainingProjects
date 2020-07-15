#include <iostream>
#include "Frame.h"
#include <thread>
using namespace std;

int main() {
	PrintStart();
	TetrisDesk* myTetris = new TetrisDesk;
	thread commands(CommandsPanel,myTetris);
	PrintGame(myTetris);
	commands.detach();
	return 0;
}