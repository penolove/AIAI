#include "Fib2584Ai.h"
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/GameBoardte.h"
#include "Fib2584/BitBoard.h"
#include <algorithm>
#include <iterator>
int Fib2584Ai::fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	return;
}

BitBoard Fib2584Ai::parseArray(int board[4][4]){
	unsigned long long q=0;
	BitBoard parse= BitBoard(q);
	for(int i = 15;i >=0 ;i--) {
		auto result =find(fibonacci_,fibonacci_+31,board[3-(i/4)][3-(i%4)]);
		int idx=std::distance( std::begin( fibonacci_ ), result );
		/*
		cout<<idx<<" ";
		if(i%4==0){
		    cout<<endl;
		}*/
		BitBoard temp=BitBoard(idx);
		temp<<=5*i;
		parse|=temp;
	}
	return parse;
}

MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	//MoveDirection Move= SerachTree(board,2);
	int score;
	MoveDirection Move = static_cast<MoveDirection>(rand() % 4);
	SerachTree_true(board,3,score,Move);
	return Move;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

MoveDirection Fib2584Ai::SerachTree(int board[4][4],int iteration)
{
	MoveDirection randomMove = static_cast<MoveDirection>(rand() % 4);
	//SerachTree(board,0) means find the first layer soultions
	//SerachTree(board,1) means find the first~second layer soultions	
	//SerachTree(board,2) means find the first~third layer soultions
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	int simuScore[4]={0};
	int temp_simu=0;
	int temp_count=0;
	for(int i =0;i<4;i++){
		BitBoard parse_temp=parse;
		gb.board_=parse_temp;
		MoveDirection TrialMove = static_cast<MoveDirection>(i);
		GameBoardte originalBoard = gb;
		simuScore[i]+=gb.move(TrialMove);
		
		if(originalBoard == gb){
			continue;
		}
		gb.addRandomTile();
		for (int ix=0;ix<iteration;ix++){
			int temp_board[4][4];
			gb.getArrayBoard(temp_board);	
			MoveDirection Move= SerachTree(temp_board,iteration-1);
			GameBoardte originalBoard = gb;
			simuScore[i] += gb.move(Move);
			if(originalBoard == gb){
				break;
			}
			if(!gb.terminated()){
				gb.addRandomTile();
			}else{
				break;
			}
		}
		
		if(simuScore[i]>temp_simu){
			randomMove=TrialMove;
			temp_simu=simuScore[i];
			temp_count=i;
			//cout<<"score is : "<< temp_simu<<endl;
		}
	}
	//cout<<"action is : "<< temp_count<<endl;
	return randomMove;
}

void Fib2584Ai::SerachTree_true(int board[4][4],int iteration,int &score,MoveDirection &direction)
{
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	int tempScore[4];
	int temp_max=0;
	if(iteration>0)
	{
		for(int i=0;i<4;i++)
		{
			gb.board_=parse;
			int board_temp[4][4];
			MoveDirection TrialMove = static_cast<MoveDirection>(i);
			GameBoardte originalBoard = gb;
			tempScore[i]=gb.move(TrialMove);
			if(originalBoard == gb){
				continue;
			}
			if(!gb.terminated()){
				gb.addRandomTile();
			}else{
				continue;
			}
			gb.getArrayBoard(board_temp);
			SerachTree_true(board_temp,iteration-1,tempScore[i],TrialMove);
			if(tempScore[i]>temp_max){
				temp_max=tempScore[i];
				direction = static_cast<MoveDirection>(i);
			}
		}
		score+=temp_max;
	}

}	
/**********************************
You can implement any additional functions
you may need.
**********************************/
