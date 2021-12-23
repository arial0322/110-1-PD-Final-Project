#include <iostream>
#include <stdlib.h>      // srand()
#include <time.h>        // time()
using namespace std;

void showMap();

int map[9][9] = {0};      // initialise map
int counter = 1;          // the number of map already generated
int maxMapNumber = 1;     // how many map you want to generate

// print out the whole map
void showMap()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

// check if the entry is legal
bool check()
{
	// check the row
	for(int i = 0; i < 9; i++)
	{
		int tempArr[9] = {0};

		for(int j = 0; j < 9; j++)
		{
			if(map[i][j] != 0)
			{
				if(tempArr[map[i][j] - 1] == 0)
				{
					tempArr[map[i][j] - 1] = 1;
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
			if(map[i][j] != 0)
			{
				if(tempArr[map[i][j] - 1] == 0)
				{
					tempArr[map[i][j] - 1] = 1;
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
					if(map[m + i][n + j] != 0)
					{
						if(tempArr[map[m + i][n + j] - 1] == 0)
						{
							tempArr[map[m + i][n + j] - 1] = 1;
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
  for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
          if(map[i][j] == 0)
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
		showMap();
		return;
	    }
	}

    // try assign number 1~9 to the empty entry
    srand((unsigned int)time(0));
    for(int i = 1; i < 10; i++)
    {
	map[(int)(curIndex / 9)][curIndex % 9] = i;
	if(check())	// if curNumber is legal.
	{
	    // cout << "curLevel:" << curIndex << endl;
	    // showMap();
	    generateMap(curIndex + 1);
	}
    }
    map[(int)(curIndex / 9)][curIndex % 9] = 0;

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
	    map[counter / 9][counter % 9] = curNumber;  // ** why not change "counter / 9" to 0?
	    counter++;
	}
    }
}

int main()
{
    cout << "enter the number of map you want to generate: ";
    cin >> maxMapNumber;
    cout << "generating first line of the map..." << endl;
    generateRow1();
    cout << "generating the full map..." << endl;
    generateMap(9);

    return 0;
}
