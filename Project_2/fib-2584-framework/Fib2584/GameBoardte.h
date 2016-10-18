#ifndef __GAMEBOARDTE_H__
#define __GAMEBOARDTE_H__

#include <iostream>
#include "MoveDirection.h"
#include "MoveTable.h"
#include "BitBoard.h"
#include "Random.h"

using namespace std;

class GameBoardte
{
public:
	static const int fibonacci_[32];
private:
	static Random random_;
public:
	GameBoardte();
	void initialize();
	int move(MoveDirection moveDirection);
	void addRandomTile();
	bool terminated();
	void getArrayBoard(int board[4][4]);
	int getMaxTile();
	void showBoard();
	bool operator==(GameBoardte gameBoard);
	BitBoard board_;
private:
	BitBoard getRow(int row);
	BitBoard getColumn(int column);
	BitBoard restoreRow(BitBoard rowBits, int row);
	BitBoard restoreColumn(BitBoard columnBits, int column);
	int countEmptyTile();
	int getTile(int row, int column);
	int getFibonacci(int index);
};

#endif
