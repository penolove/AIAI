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
#include <vector>

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
	int search_mean=0;
	int mean=0;	
	int Statistic=0;	
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoardte gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		int afsBoard[4][4];
		int adRnBoard[4][4];
		int output[4];
		double input[4];
		int search_cout;
		int h_cout;

		if(i%2==0){	
			//for each step calculate once
			while(!gameBoard.terminated()) {
				gameBoard.getArrayBoard(arrayBoard);
				ai.generateMoveSet(arrayBoard,input);
				ai.getArrayRank(input,output);
				iScore+=ai.MakeMove(arrayBoard,output,afsBoard,adRnBoard);
				statistic.increaseOneMove();
				if(1==1){
					ai.LearnEvaluation(afsBoard,adRnBoard);
				}
				BitBoard parse= ai.parseArray(adRnBoard);
				gameBoard.board_=parse;
				//gameBoard.showBoard();
				//cout<<"-------------------------------"<<endl;
				
			}
			mean+=iScore;
		}else if(i%2==1){
			//try to using search as initail guide	
			while(!gameBoard.terminated()) {
				gameBoard.getArrayBoard(arrayBoard);
				MoveDirection moveDirection = ai.generateMove(arrayBoard);
				GameBoardte originalBoard = gameBoard;
				iScore += gameBoard.move(moveDirection);
				gameBoard.getArrayBoard(afsBoard);

				if(originalBoard == gameBoard)
					continue;
				statistic.increaseOneMove();
				gameBoard.addRandomTile();
				gameBoard.getArrayBoard(adRnBoard);
				if(1==1){
					ai.LearnEvaluation_serach(afsBoard,adRnBoard);
				}

			}
			search_mean+=iScore;
		}else if(1==1){
			//trying to construct updates parameter until game endup.
			//what I need is storing all AfsBoard, and all scores;
			//create two vectors.
			std::vector<BitBoard> afs_v;
			std::vector<int> scores_v;
			GameBoardte gb;
			BitBoard parse;
			int score_temp;
			while(!gameBoard.terminated()) {
				gameBoard.getArrayBoard(arrayBoard);
				ai.generateMoveSet(arrayBoard,input);
				ai.getArrayRank(input,output);
				//=====push score======
				score_temp=ai.MakeMove(arrayBoard,output,afsBoard,adRnBoard);
				scores_v.push_back(score_temp);
				iScore+=score_temp;
				//=====push score======
				
				//======push board------
				parse=ai.parseArray(afsBoard);
				afs_v.push_back(parse);
				//======push board------
				

				statistic.increaseOneMove();
				BitBoard parse= ai.parseArray(adRnBoard);
				gameBoard.board_=parse;
			}
			//Td0
			ai.updateWeights_v(afs_v,scores_v);
			//Td1
			//ai.updateWeights_v_td1(afs_v,scores_v);
			//Td(lambda)
			//ai.updateWeights_v_td(afs_v,scores_v,0.5);
		
			mean+=iScore;
		
		}

		if(i%1000==0){
				cout<<"for game "<<i<<": "<<mean/500<<endl;
				cout<<"for game serach "<<i<<": "<<search_mean/500<<endl;
			mean=0;
			search_mean=0;
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
