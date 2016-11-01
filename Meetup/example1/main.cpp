#include <iostream>
#include <cstdlib>
#include "Fib2584/BitBoard.h"
#include "Fib2584/GameBoardte.h"

using namespace std;

int main(int argc, char* argv[])
{
	int i=0;
	BitBoard qq= 10;
	qq.show();
	GameBoardte gameBoard;
	gameBoard.board_=qq;
	cout<<"=======split_line======"<<endl;
	gameBoard.showBoard();
	cout<<"[0,1,2,3,5,8,13,21,34,55,89,.....]"<<endl;

	cout<<"=======take a break==="<<endl;

	cin>>i;
	unsigned long long temp=0;	
	for(int i=0;i<16;i++){
		temp+=i;
		if(i!=15){
			temp<<=5;
		}
	}
	qq=temp;
	qq.show();
	gameBoard.board_=qq;
	cout<<"=======split_line==="<<endl;
	gameBoard.showBoard();
	return 0;
}
