#include "Fib2584Ai.h"
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/GameBoardte.h"
#include "Fib2584/BitBoard.h"
#include <algorithm>
#include <iterator>
#include <map>
#include <limits> // used to get double minimum

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
	MoveDirection Move = static_cast<MoveDirection>(rand() % 4);
	//MoveDirection Move= SerachTree(board,2);
	
	/*-----------------n-serachtree---------------------------
	int score;
	SerachTree_true(board,3,score,Move);
	*/

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

//------------------------project2-----------------------------

void Fib2584Ai::getArrayRank(double input[4],int output[4]){
	for (int i=0;i<4;i++){
		int idx=distance(input, max_element(input, input + 4));
		input[idx]=std::numeric_limits<double>::lowest();
		output[i]=idx;
	}
};

double Fib2584Ai::random01()
{
	return (double)rand() / ((double)RAND_MAX + 1);
};


int Fib2584Ai::computeAfterState(int board[4][4],int output[4],int afsBoard[4][4],int mustMove)
{
	GameBoardte gb;
	BitBoard parse = parseArray(board);
	gb.board_ = parse;
	int score = 0;	
	int count = 0;
	GameBoardte originalBoard = gb;
	if(!gb.terminated()){
		MoveDirection action = static_cast<MoveDirection>(output[count]);
		score = gb.move(action);
		while(gb==originalBoard){
			if(mustMove==1){
				count+=1;
				MoveDirection action = static_cast<MoveDirection>(output[count]);
				score = gb.move(action);
			}else{
				return score;
			}
		}
	}else{
		gb.getArrayBoard(afsBoard);
		return score;
	}
	gb.getArrayBoard(afsBoard);
	return score;
};

double Fib2584Ai::Evaluate(int board[4][4],int output[4])
{	int afsBoard[4][4];
	int r= computeAfterState(board,output,afsBoard,0);
	//cout<<" r is :"<<r<<endl;
	//cout<<"estimateScoreV is :"<<estimateScoreV(afsBoard)<<endl;
	return estimateScoreV(afsBoard)+r;
};


double Fib2584Ai::MakeMove(int board[4][4],int output[4],int afsBoard[4][4],int adRnBoard[4][4]){
	int r= computeAfterState(board,output,afsBoard,1);
	GameBoardte gb;
	BitBoard parse= parseArray(afsBoard);
	gb.board_=parse;
	if(!gb.terminated()){
		gb.addRandomTile();
	}else{
		gb.getArrayBoard(adRnBoard);
		return 0;
	}
	gb.getArrayBoard(adRnBoard);
	return r;
};

void Fib2584Ai::LearnEvaluation(int afsBoard[4][4],int adRnBoard[4][4])
{	
	double input[4];
	int output[4];
	//arg_max
	for(int ix=0;ix<4;ix++)
	{
		int output_i[4];
		output_i[0]=ix;
		double score=Evaluate(adRnBoard,output_i);
		input[ix]=score;
	}
	getArrayRank(input,output);
	//compute_state
	int afsBoard_next[4][4];
	int r=computeAfterState(adRnBoard,output,afsBoard_next,1);
	//loss=r-score_max;
	double delta_=(r+estimateScoreV(afsBoard_next)-estimateScoreV(afsBoard));
	updateWeights(afsBoard,delta_,0.0001);
}	
void Fib2584Ai::updateWeights(int board[4][4],double delta_,double learningRate)
{
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	BitBoard parse_row;
	std::map<unsigned long long ,double>::iterator it ;
	//++++++++++++++++update col++++++++++++++++
	parse_row= gb.getColumn(0);
	it = para_col_1.find(int(parse_row));
	if(it!= para_col_1.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_1[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getColumn(1);
	it = para_col_2.find(int(parse_row));
	if(it!= para_col_2.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_2[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getColumn(2);
	it = para_col_3.find(int(parse_row));
	if(it!= para_col_3.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_3[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getColumn(3);
	it = para_col_4.find(int(parse_row));
	if(it!= para_col_4.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_4[int(parse_row)]=delta_*learningRate;
	}
	//++++++++++++++++update row++++++++++++++++
	parse_row= gb.getRow(0)&1048575;
	it = para_row_1.find(int(parse_row));
	if(it!= para_row_1.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_1[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getRow(1)&1048575;
	it = para_row_2.find(int(parse_row));
	if(it!= para_row_2.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_2[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getRow(2)&1048575;
	it = para_row_3.find(int(parse_row));
	if(it!= para_row_3.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_3[int(parse_row)]=delta_*learningRate;
	}
	parse_row= gb.getRow(3)&1048575;
	it = para_row_4.find(int(parse_row));
	if(it!= para_row_4.end()){
		it->second+=delta_*learningRate;
	}else{
		para_col_4[int(parse_row)]=delta_*learningRate;
	}
};	
double Fib2584Ai::estimateScoreV(int board[4][4]){
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	if(gb.terminated()){
		return 0;
	}
	double score=0;
	BitBoard parse_row;
	std::map<unsigned long long ,double>::iterator it ;
	//-----parse column--------
	parse_row= gb.getColumn(0);
	it = para_col_1.find(int(parse_row));
	if(it!= para_col_1.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getColumn(1);
	it = para_col_2.find(int(parse_row));
	if(it!= para_col_2.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getColumn(2);
	it = para_col_3.find(int(parse_row));
	if(it!= para_col_3.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getColumn(3);
	it = para_col_4.find(int(parse_row));
	if(it!= para_col_4.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	//parse row
	parse_row= gb.getRow(0)&1048575;
	it = para_row_1.find(int(parse_row));
	if(it!= para_row_1.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getRow(1)&1048575;
	it = para_row_2.find(int(parse_row));
	if(it!= para_row_2.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getRow(2)&1048575;
	it = para_row_3.find(int(parse_row));
	if(it!= para_row_3.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	parse_row= gb.getRow(3)&1048575;
	it = para_row_4.find(int(parse_row));
	if(it!= para_row_4.end()){
		score+=it->second;
	}else{
		it->second=random01();
		score+=it->second;
	}
	return score;
};
/*
{
	
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	GameBoardte gb_row;
	//BitBoard parse_row= gb.getrow(2)&1048575;
	BitBoard parse_row= gb.getColumn(2);
	gb_row.board_=parse_row;
	cout<<"====current===="<<endl;
	gb.showBoard();
	cout<<"====getrow======"<<endl;
	gb_row.showBoard();
	int stop;
	std::map<unsigned long long ,double>::iterator it = qqo.find(int(parse_row));
	if(it!= qqo.end()){
		it->second= it->second+1.0;
	}
	cout<<"key: "<<int(parse_row)<<", value: "<<qqo[int(parse_row)]<<endl;
	cin>>stop;
}*/	
/**********************************
You can implement any additional functions
you may need.
**********************************/
