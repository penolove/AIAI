#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/BitBoard.h"
#include <map>

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);

	//---------Project1 : members-I-created--------------//
	BitBoard parseArray(int board[4][4]);	
	MoveDirection SerachTree(int board[4][4],int iteration);	
	void SerachTree_true(int board[4][4],int iteration,int &score,MoveDirection &direction);	
	static int fibonacci_[32];
	
	//--------- Project2: members-I-created-------------//
	double random01();
	double MakeMove(int board[4][4],MoveDirection action,int afsBoard[4][4],int adRnBoard[4][4]);
	//+++retrun double r , afsBoard ,adRnBoard++++//
	int computeAfterState(int board[4][4],MoveDirection action,int afsBoard[4][4] );
	//+++return int r , afsBoard ++++++++++++++++//
	double estimateScoreV(int board[4][4]);
	double Evaluate(int board[4][4],MoveDirection action);
	//+++ return double r , Move action++++++++++//
	void LearnEvaluation(int afsBoard[4][4],int adRnBoard[4][4]);
	void updateWeights(int board[4][4],double loss,double learningRate);	
	//----------Project2 : parameter_set----------------//
	std::map<unsigned long long ,double> para_row_1;	
	std::map<unsigned long long ,double> para_row_2;	
	std::map<unsigned long long ,double> para_row_3;	
	std::map<unsigned long long ,double> para_row_4;	

	std::map<unsigned long long ,double> para_col_1;	
	std::map<unsigned long long ,double> para_col_2;	
	std::map<unsigned long long ,double> para_col_3;	
	std::map<unsigned long long ,double> para_col_4;	
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
};

#endif
