#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/BitBoard.h"

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

	BitBoard parseArray(int board[4][4]);	
	MoveDirection SerachTree(int board[4][4],int iteration);	
	void SerachTree_true(int board[4][4],int iteration,int &score,MoveDirection &direction);	

	static int fibonacci_[32];
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
};

#endif
