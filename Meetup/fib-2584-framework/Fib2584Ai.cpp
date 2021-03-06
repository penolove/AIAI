#include "Fib2584Ai.h"
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/GameBoardte.h"
#include "Fib2584/BitBoard.h"
#include <algorithm>
#include <iterator>
#include <map> //used to store parameters
#include <limits> // used to get double minimum
#include <math.h> // used pow
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
	
	//-----------------n-serachtree---------------------------
	int score;
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

//------------------------project2-----------------------------



void Fib2584Ai::generateMoveSet(int board[4][4],double output[4]){
	for(int i=0;i<4;i++)
	{
		int output_i[4];
		output_i[0]=i;
		double score=Evaluate(board,output_i);
		output[i]=score;
		//cout<<score<<" ";
	}
	//cout<<endl;
};

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
				gb.getArrayBoard(afsBoard);
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
	return estimateScoreV(afsBoard,0)+r;
};


double Fib2584Ai::MakeMove(int board[4][4],int output[4],int afsBoard[4][4],int adRnBoard[4][4]){
	int r= computeAfterState(board,output,afsBoard,1);
	GameBoardte gb;
	BitBoard parse= parseArray(afsBoard);
	gb.board_=parse;
	if(!gb.terminated()){
		gb.addRandomTile();
	}
	gb.getArrayBoard(adRnBoard);
	return r;
};


void Fib2584Ai::LearnEvaluation_serach(int afsBoard[4][4],int adRnBoard[4][4]){
	GameBoardte gb;
	//
	BitBoard parse= parseArray(adRnBoard);
	gb.board_=parse;
	MoveDirection moveDirection = generateMove(adRnBoard);
	int r=gb.move(moveDirection);
	int afsBoard_next[4][4];
	gb.getArrayBoard(afsBoard_next);
	double afs_next_score;
	if(gb.terminated()){
		afs_next_score=0;
	}else{
		afs_next_score=estimateScoreV(afsBoard_next,0);
	}
	double afs_score=estimateScoreV(afsBoard,0);
	double delta_=(r+afs_next_score-afs_score);
	double weightdecay=0.99995;
	double lR=0.005;
	updateWeights(afsBoard,delta_,lR,weightdecay,0);
//	cout<< "--reward r : "<<r <<", afs_next : "<<afs_next_score<<", afs :"<<afs_score<<", delta : "<<delta_<<endl;
};


void Fib2584Ai::LearnEvaluation(int afsBoard[4][4],int adRnBoard[4][4])
{	
	double input[4];
	int output[4];
	double delta_;

	GameBoardte gb;
	//arg_max action
	generateMoveSet(adRnBoard,input);
	getArrayRank(input,output);

	//compute_state->afsBoard_next;
	int afsBoard_next[4][4];
	int r=computeAfterState(adRnBoard,output,afsBoard_next,1);


	//check if the terminated()/ final afterstate_next
	double afs_next_score=0;
	double afs_score=0;
	BitBoard parse= parseArray(afsBoard_next);
	gb.board_=parse;
	if(gb.terminated()){
		afs_next_score=0;
	}else{
		afs_next_score=estimateScoreV(afsBoard_next,0);
	}
	double weightdecay=0.99995;
	double lR=0.005;
	afs_score=estimateScoreV(afsBoard,0);
	delta_=(r+afs_next_score-afs_score);
	updateWeights(afsBoard,delta_,lR,weightdecay,0);
//	cout<< "reward r : "<<r <<", afs_next : "<<afs_next_score<<", afs :"<<afs_score<<", delta : "<<delta_<<endl;
}	
void Fib2584Ai::updateWeights(int board[4][4],double delta_,double learningRate,double weightdecay,int verbose)
{
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	BitBoard parse_row;
	std::map<unsigned long long ,double>::iterator it ;
	//++++++++++++++++update col++++++++++++++++
	if(verbose==1) cout<<"++++++++up-col+++++++++ "<<endl;
	parse_row= gb.getColumn(0);
	it = para_col_1.find(int(parse_row));
	if(it!= para_col_1.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1) cout<< it->second<<" ";
	}else{
		para_col_1[int(parse_row)]=(delta_*learningRate);
		if(verbose==1) cout<< delta_*learningRate<<"* ";
	}

	parse_row= gb.getColumn(1);
	it = para_col_2.find(int(parse_row));
	if(it!= para_col_2.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1) cout<< it->second<<" ";
	}else{
		para_col_2[int(parse_row)]=(delta_*learningRate);
		if(verbose==1) cout<< delta_*learningRate<<"* ";
	}

	parse_row= gb.getColumn(2);
	it = para_col_3.find(int(parse_row));
	if(it!= para_col_3.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1)cout<< it->second<<" ";
	}else{
		para_col_3[int(parse_row)]=(delta_*learningRate);
		if(verbose==1)cout<< delta_*learningRate<<"* ";
	}
	parse_row= gb.getColumn(3);
	it = para_col_4.find(int(parse_row));
	if(it!= para_col_4.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1)cout<< it->second<<endl;
	}else{
		para_col_4[int(parse_row)]=delta_*learningRate;
		if(verbose==1)cout<< delta_*learningRate<<"* "<<endl;
	}
	//++++++++++++++++update row++++++++++++++++
	if(verbose==1) cout<<"++++++++up-row++++++++ "<<endl;
	parse_row= gb.getRow(0)&1048575;
	it = para_row_1.find(int(parse_row));
	if(it!= para_row_1.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1)cout<< it->second<<" ";
	}else{
		para_row_1[int(parse_row)]=delta_*learningRate;
		if(verbose==1)cout<< delta_*learningRate<<"* ";
	}
	parse_row= gb.getRow(1)&1048575;
	it = para_row_2.find(int(parse_row));
	if(it!= para_row_2.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1)cout<< it->second<<" ";
	}else{
		para_row_2[int(parse_row)]=(delta_*learningRate);
		if(verbose==1)cout<< delta_*learningRate<<"* ";
	}
	parse_row= gb.getRow(2)&1048575;
	it = para_row_3.find(int(parse_row));
	if(it!= para_row_3.end())
	{
		it->second*=weightdecay;
		it->second+=(delta_*learningRate);
		if(verbose==1)cout<< it->second<<" ";
	}else{
		para_row_3[int(parse_row)]=delta_*learningRate;
		if(verbose==1)cout<< delta_*learningRate<<"* ";
	}
	parse_row= gb.getRow(3)&1048575;
	it = para_row_4.find(int(parse_row));
	if(it!= para_row_4.end())
	{
		it->second*=weightdecay;
		it->second+=delta_*learningRate;
		if(verbose==1)cout<< it->second<<endl;
	}else{
		para_row_4[int(parse_row)]=delta_*learningRate;
		if(verbose==1)cout<< delta_*learningRate<<"* "<<endl;
	}
};	

void Fib2584Ai::updateWeights_v_td(vector<BitBoard>& afs_v,vector<int>& scores_v,double lambda){

	//TD(lambda)
	GameBoardte gb;
	int afsBoard[4][4];
	int afsBoard_next[4][4];
	
	double weightdecay=0.99995;
	double lR=0.005;
	double afs_score;
	double afs_next_score;
	//for the first term;
	//double delta_ = 0;
	for(int i=0; i < afs_v.size(); i++){
		gb.board_=afs_v[i];
		gb.getArrayBoard(afsBoard);
		//cout<<"============"<<endl;
		//gb.showBoard();
		//cout<<"============"<<endl;
		afs_score=estimateScoreV(afsBoard,0);
		double delta=0;
		double r_final=0;
		double r=0;
		double count=0;
		for(int j=i+1;j<afs_v.size();j++){
			gb.board_=afs_v[j];
			gb.getArrayBoard(afsBoard_next);
			afs_next_score=estimateScoreV(afsBoard_next,0);
			r_final+=scores_v[j-1];
			delta+=(r_final+afs_next_score-afs_score)*pow(lambda,count);
			count+=1;
			/*
			if(j==i+1){
				cout<<"current i,j,afs_next,delta : "<<i<<", "<<j\
				<<", "<<afs_next_score\
				<<", "<<delta<<endl;
			}*/
		}
			//cout<<"current i : "<<i<<endl;
		delta*=(1-lambda);
		r_final+=scores_v.back();
			//cout<<"current r_final,afs_score : "<<r_final<<", "<<afs_score<<endl;
		delta+=(pow(lambda,count)*(r_final-afs_score));
			//cout<<"current delta : "<<delta<<endl;
		
		updateWeights(afsBoard,delta,lR,weightdecay,0);
	}
};

void Fib2584Ai::updateWeights_v_td1(vector<BitBoard>& afs_v,vector<int>& scores_v)
{
	//TD(0)
	GameBoardte gb;
	BitBoard afsBoard_B;
	int afsBoard[4][4];

	//before while steal the end of game;
	double afs_score=0;
	double weightdecay=0.99995;
	double lR=0.001;
	double r=0;
	while (!afs_v.empty())
	{	
		//get next action
		afsBoard_B=afs_v.back();
		afs_v.pop_back();
		//get reward
		r+=scores_v.back();
		scores_v.pop_back();

		gb.board_=afsBoard_B;
		gb.getArrayBoard(afsBoard);
		afs_score=estimateScoreV(afsBoard,0);
		double delta_=(r-afs_score);
		updateWeights(afsBoard,delta_,lR,weightdecay,0);
	}	
};
void Fib2584Ai::updateWeights_v(vector<BitBoard>& afs_v,vector<int>& scores_v)
{
	//TD(0)
	GameBoardte gb;
	BitBoard afsBoard_B;
	BitBoard afsBoard_B_next;
	int afsBoard[4][4];
	int afsBoard_next[4][4];

	//before while steal the end of game;
	double afs_next_score=0;
	double afs_score=0;
	double weightdecay=0.99995;
	double lR=0.00025;
	afsBoard_B=afs_v.back();
	afs_v.pop_back();
	gb.board_=afsBoard_B;
	gb.getArrayBoard(afsBoard);
	afs_score=estimateScoreV(afsBoard,0);
	//the final reward
	double r=scores_v.back();
	scores_v.pop_back();
	//calcualte delta
	double delta_=(r+afs_next_score-afs_score);
	updateWeights(afsBoard,delta_,lR,weightdecay,0);
	afsBoard_B_next=afsBoard_B;
	//cout<< "reward r : "<<r <<", afs_next : "<<afs_next_score<<", afs :"<<afs_score<<", delta : "<<delta_<<endl;
	while (!afs_v.empty())
	{	
		//get next action
		afsBoard_B=afs_v.back();
		afs_v.pop_back();
		//get reward
		r=scores_v.back();
		scores_v.pop_back();

		//parse board
		gb.board_=afsBoard_B;
		gb.getArrayBoard(afsBoard);
		gb.board_=afsBoard_B_next;
		gb.getArrayBoard(afsBoard_next);


		afs_next_score=estimateScoreV(afsBoard_next,0);
		afs_score=estimateScoreV(afsBoard,0);

		delta_=(r+afs_next_score-afs_score);
		updateWeights(afsBoard,delta_,lR,weightdecay,0);
		afsBoard_B_next=afsBoard_B;
		//cout<< "reward r : "<<r <<", afs_next : "<<afs_next_score<<", afs :"<<afs_score<<", delta : "<<delta_<<endl;
	}	
};


double Fib2584Ai::estimateScoreV(int board[4][4],int verbose){
	GameBoardte gb;
	BitBoard parse= parseArray(board);
	gb.board_=parse;
	double score=0;
	BitBoard parse_row;
	std::map<unsigned long long ,double>::iterator it ;
	//-----parse column--------
	parse_row= gb.getColumn(0);
	it = para_col_1.find(int(parse_row));
	if(it!= para_col_1.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_col_1 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_col_1[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getColumn(1);
	it = para_col_2.find(int(parse_row));
	if(it!= para_col_2.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_col_2 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_col_2[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getColumn(2);
	it = para_col_3.find(int(parse_row));
	if(it!= para_col_3.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_col_3 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_col_3[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getColumn(3);
	it = para_col_4.find(int(parse_row));
	if(it!= para_col_4.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_col_4 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_col_4[int(parse_row)]=temp;
		score+=temp;
	}
	//-----parse row-------
	parse_row= gb.getRow(0)&0x1048575;
	it = para_row_1.find(int(parse_row));
	if(it!= para_row_1.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_row_1 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_row_1[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getRow(1)&1048575;
	it = para_row_2.find(int(parse_row));
	if(it!= para_row_2.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_row_2 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_row_2[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getRow(2)&1048575;
	it = para_row_3.find(int(parse_row));
	if(it!= para_row_3.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_row_3 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_row_3[int(parse_row)]=temp;
		score+=temp;
	}
	parse_row= gb.getRow(3)&1048575;
	it = para_row_4.find(int(parse_row));
	if(it!= para_row_4.end()){
		score+=it->second;
		if(verbose==1)cout<<"para_row_4 : "<<it->second<<endl;
	}else{
		double temp=random01();
		para_row_4[int(parse_row)]=temp;
		score+=temp;
	}
	return score;
};
/**********************************
You can implement any additional functions
you may need.
**********************************/
