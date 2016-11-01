#include <iostream>
#include <cstdlib>
#include "Fib2584/BitBoard.h"
#include "Fib2584/GameBoardte.h"

using namespace std;

int main(int argc, char* argv[])
{
	//the problem is that 64bit can't contain 5*16(80 bit);
	unsigned long long temp=0;	
	for(int i=0;i<16;i++){
		temp+=i;
		if(i!=15){
			temp<<=5;
		}
	}
	qq=temp;
	gameBoard.board_=qq;
	cout<<"=======split_line==="<<endl;
	gameBoard.showBoard();
	return 0;
}
