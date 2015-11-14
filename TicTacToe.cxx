#include<iostream>
#include<cstring>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;

#define MARK_NULL '.'
#define PLAYER1_MARK 'X'
#define PLAYER2_MARK 'O'
#define COMPUTER_MARK 'O'
#define TEST_NUM 2000
#define DRAW_POINTS 1
#define LOSE_POINTS 0
#define WIN_POINTS 2

/*    
 * Print the chess board*
 *
 */
void printBoard(char arr[9])
{
	cout<<"############ Tic-Toc-Tae ############\n";
	cout<<"***********************\n\n";
	for(int i = 0; i < 9; ++i)
	{
		if(i != 0 && i % 3 == 0)
		{
			cout<<"   ";
			cout<<i-2<<" "<<i-1<<" "<<i<<"\n";
		}
		cout<<arr[i]<<" ";
	}
	cout<<"   "<<7<<" "<<8<<" "<<9;
	cout<<"\n\n***********************\n";
}

/*
 * Check if the game is over
 *
 */
char checkGame(char arr[])
{
	if(arr[0] == arr[1] && arr[1] == arr[2]) return arr[2];
	if(arr[3] == arr[4] && arr[4] == arr[5]) return arr[5];
	if(arr[6] == arr[7] && arr[7] == arr[8]) return arr[8];
	if(arr[0] == arr[3] && arr[3] == arr[6]) return arr[6];
	if(arr[1] == arr[4] && arr[4] == arr[7]) return arr[7];
	if(arr[2] == arr[5] && arr[5] == arr[8]) return arr[8];
	if(arr[0] == arr[4] && arr[4] == arr[8]) return arr[8];
	if(arr[2] == arr[4] && arr[4] == arr[6]) return arr[6];

	return MARK_NULL;
}


/*
 * Get random free space
 *
 */
int getRandFree(char arr[9])
{
	int freeSpace[9];
	int freeSpaceCount = 0;
	for(int i = 0; i < 9; ++i)
	{
		if(arr[i] == MARK_NULL)  // free space
		{
			freeSpace[freeSpaceCount++] = i;
		}
	}

	if(freeSpaceCount == 0)   // No free space
		return -1;
	return freeSpace[rand() % freeSpaceCount];
}


/*
 * Computer select best move
 * return -1 denote has no free space
 */
int bestMove(char arr[9])
{
	bool hasFreeSpace = false;
	for(int i = 0; i < 9; ++i)
	{
		if(arr[i] == MARK_NULL)
		{
			hasFreeSpace = true;
			break;
		}
	}
	
	if(!hasFreeSpace)
		return -1;    // -1 denote has no free space

	int movePoints[9] = {0,};    // Record points

	for(int i = 0; i < TEST_NUM; ++i)
	{
		int firstMove = -1;
		char tmp[9] = {0,};
		strncpy(tmp,arr,9);
		char mark = COMPUTER_MARK;
		while(checkGame(tmp) == MARK_NULL)   //Game has not over
		{
			int pos = getRandFree(tmp);
			if(pos == -1)    // no free space
				break;
			if(firstMove == -1)
				firstMove = pos;
			tmp[pos] = mark;
			mark = (mark == COMPUTER_MARK) ? PLAYER1_MARK : COMPUTER_MARK;
		}

		if(checkGame(tmp) == MARK_NULL)    // Draw
			movePoints[firstMove] += DRAW_POINTS;
		else if(checkGame(tmp) == COMPUTER_MARK)   // Computer win
			movePoints[firstMove] += WIN_POINTS;
		else    // Computer lose
			movePoints[firstMove] += LOSE_POINTS;
	}

	int maxPoints = 0;
	// Find maximum point
	for(int j = 0; j < 9; ++j)
	{
		if(movePoints[j] > maxPoints)
			maxPoints = movePoints[j];
	}

	int candidateCount = 0;
	int candidate[9] = {0,};
	for(int j = 0; j < 9; ++j)
	{
		if(movePoints[j] == maxPoints)
			candidate[candidateCount++] = j;
	}
	
	return candidate[rand() % candidateCount];
}


/*
 * In Game: Human vs Computer
 *
 */
void playGame1(char arr[],int flag,int step)
{
	while(checkGame(arr) == MARK_NULL)   // The game is not over
	{
		++step;
		if(step == 10)
			break;
		if(!(flag & 1))
			printBoard(arr);
		cout<<"Note: Player1 use '"<<PLAYER1_MARK<<"' and Computer use '"<<PLAYER2_MARK<<"'\n\n";
		if(!(flag & 1))   // player1 move
		{
			cout<<"Player1's select [1-9]:";
			int select;
			cin>>select;

			// Check input is invalid or not
			while(true)
			{
				if(select <=0 || select > 9 || arr[select-1] != MARK_NULL)
					cout<<"Invalid select,please input again\n";
				else
					break;
				cin>>select;
			}

			arr[--select] = PLAYER1_MARK;
		}
		else    // Computer move
		{
			int select = bestMove(arr);
			if(select == -1)   // no free space 
				break;
			arr[select] = COMPUTER_MARK;
		}

		++flag;
		cout<<"\n";
	}
	printBoard(arr);
	if(checkGame(arr) == PLAYER1_MARK)
		cout<<"Player1 win.\n";
	else if(checkGame(arr) == COMPUTER_MARK)
		cout<<"Computer win.\n";
	else
		cout<<"Draw.\n";
	
}

/*
 * In Game: Player1 vs Player2
 *
 */
void playGame2(char arr[],int flag,int step)
{
	while(checkGame(arr) == MARK_NULL)   // The game is not over
	{
		++step;
		if(step == 10)
			break;
		printBoard(arr);
		cout<<"Note: Player1 use '"<<PLAYER1_MARK<<"' and Player2 use '"<<PLAYER2_MARK<<"'\n\n";
		if(!(flag & 1))   // player1 move
		{
			cout<<"Player1's select [1-9]:";
			int select;
			cin>>select;

			// Check input is invalid or not
			while(true)
			{
				if(select <=0 || select > 9 || arr[select-1] != MARK_NULL)
					cout<<"Invalid select,please input again\n";
				else
					break;
				cin>>select;
			}

			arr[--select] = PLAYER1_MARK;
		}
		else    // player2 move
		{
			cout<<"Player2's select [1-9]:";
			int select;
			cin>>select;

			// Check input is invalid or not
			while(true)
			{
				if(select <=0 || select > 9 || arr[select-1] != MARK_NULL)
					cout<<"Invalid select,please input again\n";
				else
					break;
				cin>>select;
			}

			arr[--select] = PLAYER2_MARK;
		}

		++flag;
		cout<<"\n";
	}
	printBoard(arr);
	if(checkGame(arr) == PLAYER1_MARK)
		cout<<"Player1 win.\n";
	else if(checkGame(arr) == PLAYER2_MARK)
		cout<<"Player2 win.\n";
	else
		cout<<"Draw.\n";
	
}

/*
 * Print the mode
 *
 */
void printMode()
{
	cout<<"############ Select The Mode ############\n\n";
	cout<<"1. Single Player Mode: Human vs Computer\n";
	cout<<"2. Double Players Mode: Player1 vs Player2\n\n";
	cout<<"#########################################\n";
	cout<<"Select your choic [1-2]:";
}

int main()
{
	char arr[] = {'.','.','.','.','.','.','.','.','.'};
	int flag = 0, step = 0;
	printMode();
	int choice;
	cin>>choice;
	while(choice != 1 && choice != 2)
	{
		cout<<"Invalid input,please select again[1-2]:";
		cin>>choice;
	}
	cout<<endl;
	switch(choice)
	{
		case 1:
			playGame1(arr,flag,step);
			break;
		case 2:
			playGame2(arr,flag,step);
			break;
	}
	return 0;
}
