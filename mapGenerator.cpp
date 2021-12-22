#include <iostream>
#include <stdlib.h>			// srand()
#include <time.h>			// time()
using namespace std;

void showBoard();

int board[9][9] = {0};		// initialise map
int counter = 1;			// the number of map already generated
int maxMapNumber = 1;			// how many map you want to generate

// print out the whole board
void showBoard()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}


bool check()
{
	// check the row
	for(int i = 0; i < 9; i++)
	{
		int tempArr[9] = {0};

		for(int j = 0; j < 9; j++)
		{
			if(board[i][j] != 0)
			{
				if(tempArr[board[i][j] - 1] == 0)
				{
					tempArr[board[i][j] - 1] = 1;
				}
				else
				{
					return false;
				}
			}
		}
	}

	//check the col
	for(int j = 0; j < 9; j++)
	{
		int tempArr[9] = {0};

		for(int i = 0; i < 9; i++)
		{
			if(board[i][j] != 0)
			{
				if(tempArr[board[i][j] - 1] == 0)
				{
					tempArr[board[i][j] - 1] = 1;
				}
				else
				{
					return false;
				}
			}
		}
	}

	//check the 9-box
	for(int m = 0; m < 9; m += 3)
	{
		for(int n = 0; n < 9; n += 3)
		{
			int tempArr[9] = {0};

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					if(board[m + i][n + j] != 0)
					{
						if(tempArr[board[m + i][n + j] - 1] == 0)
						{
							tempArr[board[m + i][n + j] - 1] = 1;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

// check if the map has been filled out
bool isMapFull()
{
  /*
	int flag[9*9] = {0};

	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			if(board[i][j] != 0)
				flag[i*9 + j] = 1;

	for(int i = 0; i < 81; i++)
		if(flag[i] == 0)
			return false;

	return true;*/

  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      if(board[i][j] == 0)
        return false;
  return true;
}

// check if all the numbers in one-dimension array are non-zero
bool checkIsNumberFull(int arr[9])
{
	for(int i = 0; i < 9; i++)
		if(arr[i] == 0)
			return false;
	return true;
}

// return a random number between [1, 9]
int getRandNumber()
{
	return rand()%9 + 1;
}

void generateMap(int curIndex)
{
  // if the map hasn't been filled out, then continue cram number in
	if(isMapFull())
	{
		if(counter <= maxMapNumber)
		{
			cout << "SudoMap " << counter++ << endl;
			showBoard();
			return;
		}
	}

	srand((unsigned int)time(0));
	for(int i = 1; i < 10; i++)
	{
		board[(int)(curIndex / 9)][curIndex % 9] = i;
		if(check())	// if curNumber is legal.
		{
			// cout << "curLevel:" << curIndex << endl;
			// showBoard();
			generateMap(curIndex + 1);
		}
	}
	board[(int)(curIndex / 9)][curIndex % 9] = 0;

	return;
}

// assign numbers to the first row
void generateRow1()
{
	int numberFlag[9] = {0};
	int curNumber;
	int counter = 0;

	srand((unsigned)time(NULL));
	while(!checkIsNumberFull(numberFlag))
	{
		curNumber = getRandNumber();
		if(numberFlag[curNumber - 1] == 0)
		{
			numberFlag[curNumber - 1] = 1;
			board[counter / 9][counter % 9] = curNumber;  // ** why not change "counter / 9" to 0?
			counter++;
		}
	}
}

int main()
{
	cout << "enter the number of board you want to generate: ";
	cin >> maxMapNumber;
	cout << "generating first line of the map..." << endl;
	generateRow1();
	cout << "generating the full board..." << endl;
	generateMap(9);

	return 0;
}
