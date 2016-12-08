#fndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/BitBoard.h"
#include <map>
#include <vector>

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
	void getArrayRank(double input[4],int output[4]);
	//e.g getArrayRank([5,3,4,9])=>[3,0,2,1];
	
	double random01();
	//create random numbers in (0,1);

	//================take actions==================
	// ----output is a action set that the first-element
	// with highest prediction score. Used to prevent cursh.
	// i.e output[0]=argmax_a(Evalute)
	// i.e output[1]=argsecond_a(Evalute)
	double MakeMove(int board[4][4],int output[4],int afsBoard[4][4],int adRnBoard[4][4]);
	//+++retrun double r , afsBoard ,adRnBoard++++//
	int computeAfterState(int board[4][4],int output[4],int afsBoard[4][4],int mustMove);
	//+++return int r , afsBoard ++++++++++++++++//
	double Evaluate(int board[4][4],int output[4]);
	//+++ return double r , Move action++++++++++//
	//================take actions==================
	
	
	void generateMoveSet(int board[4][4],double output[4]);
	double estimateScoreV(int board[4][4],int verbose);
	//estimate the current board score using parameter_set;

	void LearnEvaluation_serach(int afsBoard[4][4],int adRnBoard[4][4]);

	void LearnEvaluation(int afsBoard[4][4],int adRnBoard[4][4]);
	//used to calculate loss and update parameter;
	void updateWeights(int board[4][4],double delta_,double learningRate,double weightdecay,int verbose);
	//used in LearnEvaluation to update parameter;	
	void updateWeights_v(vector<BitBoard>& afs_v,vector<int>& scores_v);
	void updateWeights_v_td1(vector<BitBoard>& afs_v,vector<int>& scores_v);
	void updateWeights_v_td(vector<BitBoard>& afs_v,vector<int>& scores_v,double lambda);
	//used in main() to update parameter;
		
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
