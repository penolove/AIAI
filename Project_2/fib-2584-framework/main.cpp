#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/BitBoard.h"
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
	int mean=0;	
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoardte gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		int afsBoard[4][4];
		int adRnBoard[4][4];

		while(!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection;
			//cout<<"evalutation"<<endl;
			double score_max=0;
			int temp=0;
			for(int i=0;i<4;i++)
			{
				MoveDirection TrialMove = static_cast<MoveDirection>(i);
				double score=ai.Evaluate(arrayBoard,TrialMove);
				if(score>score_max)
				{
					score_max=score;
					moveDirection=TrialMove;
					temp=i;
				}
			}
			//cout<<"current move:"<<temp<<endl;
			//cout<<"Make"<<endl;
			iScore+=ai.MakeMove(arrayBoard,moveDirection,afsBoard,adRnBoard);
			statistic.increaseOneMove();
			if(1==1){
			//	cout<<"Learn"<<endl;
				ai.LearnEvaluation(afsBoard,adRnBoard);
			}
			//cout<<"parse"<<endl;
			BitBoard parse= ai.parseArray(adRnBoard);
			gameBoard.board_=parse;
			
		}
		mean+=iScore;
		if(i%300==0){
			cout<<"for game "<<i<<": "<<mean/300<<endl;
			mean=0;
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
