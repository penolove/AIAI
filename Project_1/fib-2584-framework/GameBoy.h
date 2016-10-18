#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"

using namespace std;

class GameBoy:public GameBoard
{
    public:
	int kerker =3;
        void initialize(){
		GameBoard::initialize();
	};
	void showBoard(){
		GameBoard::showBoard();
	};
};
