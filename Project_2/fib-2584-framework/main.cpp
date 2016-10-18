#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/GameBoardte.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include "GameBoy.h"
#include <bitset>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round
	/*
	GameBoardte gb;
	gb.initialize();
	gb.showBoard();
	unsigned long long q=0;
	BitBoard parse= BitBoard(q);
	int qpArray[4][4];
	gb.getArrayBoard(qpArray);
	for(int i = 15;i >=0 ;i--) {
		int* result =find(fibon_lookup,fibon_lookup+31,qpArray[3-(i/4)][3-(i%4)]);
		cout <<*result<<" ";
		if(i%4==0){
		    cout<<endl;
		}
		BitBoard temp=BitBoard(*result);
		temp<<=5*i;
		parse|=temp;
	}
	
	gb.board_=parse;
	gb.showBoard();
	MoveDirection randomMove = static_cast<MoveDirection>(0);
	//gb.move(randomMove);
	//gb.showBoard();
	//q+=gb.getRow(0);
	//cout<<"++++++++++++++++++++"<<endl;
	*/	
	
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while(!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			//cout<<"====current gameboard===="<<endl;
			//gameBoard.showBoard();
			MoveDirection moveDirection = ai.generateMove(arrayBoard);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if(originalBoard == gameBoard)
				continue;
			statistic.increaseOneMove();

			gameBoard.addRandomTile();
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());
	}
	statistic.setFinishTime();

	// output statistic data
	statistic.show();

	return 0;
}
