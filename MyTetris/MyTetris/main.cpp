#include <iostream>
#include "Frame.h"
#include <thread>
#include <chrono>
using namespace std;

int main() {
	TetrisDesk* myTetris = new TetrisDesk;
	thread commands(CommandsPanel,myTetris);
	commands.detach();
	PrintGame(myTetris);
	return 0;
}