#include <iostream>
#include <random>      // srand()
#include <ctime>        // time()
using namespace std;
 
/* ==== For generating map ==== */
void showMap(int map[9][9]);
bool isMapLegal();
bool isMapFull();
bool checkIsNumberFull(int arr[9]);
int getRandNumber();
int generateMap(int curIndex);
void generateRow1();
/* ==== For generating puzzle ==== */
int getRandNumberForEmptyIndex();
int determine_emptyCnt(int level);
void gen_puzzle(int emptyCnt);
/* ==== For finding solution ==== */
bool SameRow(int, int);
bool SameCol(int, int);
bool SameBlock(int, int);
void solveSudoku(int[9][9], int[9][9], int[1]);
void checkValidation(int[9][9], int, int);

const int SIZE = 9;
int map[9][9] = {0};              // initialise original map.
int puzzle[9][9] = {0};   // for generating puzzle.
 
int main()
{
  srand(time(nullptr));
 
  // generate the original map
  generateRow1();
  generateMap(9);
  cout << "This is the original map:\n";
  showMap(map);
 
  // let the user type in the difficulty (can be edited on GUI)
  int level = 0;
  cout << "Key in the level of difficulty you want. 1 for easy, 2 for normal, 3 for hard: ";
  cin >> level;
  
  // generate the puzzle and check solutions
  int emptyCnt = determine_emptyCnt(level);
  int genNum = 0;  // how much puzzle generated before we get a valid one
  checkValidation(puzzle, emptyCnt, genNum);
 
  return 0;
}
 
// print out the whole map
void showMap(int map[9][9])
{
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
      cout << map[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}
 
// check whether the map is legal (used after adding a entry)
bool isMapLegal()
{
  // check the row
  for(int i = 0; i < 9; i++)
  {
    int tempArr[10] = {0};  // recording whether the number is used in this row
    for(int j = 0; j < 9; j++)
      if(map[i][j] != 0)
        if(tempArr[map[i][j]] == 0)
          tempArr[map[i][j]] = 1;
        else
          return false;
  }
 
  //check the col
  for(int j = 0; j < 9; j++)
  {
    int tempArr[10] = {0};
    for(int i = 0; i < 9; i++)
      if(map[i][j] != 0)
        if(tempArr[map[i][j]] == 0)
          tempArr[map[i][j]] = 1;
        else
          return false;
  }
 
  //check the 9-box
  for(int m = 0; m < 9; m += 3)
    for(int n = 0; n < 9; n += 3)
    {
      int tempArr[10] = {0};
      for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
          if(map[m + i][n + j] != 0)
            if(tempArr[map[m + i][n + j]] == 0)
              tempArr[map[m + i][n + j]] = 1;
            else
              return false;
    }
  return true;
}
 
// check whether the map has been filled in
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
  return rand() % 9 + 1;
}
 
int generateMap(int curIndex)
{
  // if the map hasn't been filled out, then continue cram number in
  if(isMapFull())
    return 0;
 
  // try assign number 1~9 to the empty entry
  for(int i = 1; i < 10; i++)
  {
    int jd = 1;
    map[(int)(curIndex / 9)][curIndex % 9] = i;
    if(isMapLegal())  // if after adding curNumber, the map is legal
      jd = generateMap(curIndex + 1);
    if(jd == 0)
      return 0;
  }
 
  map[(int)(curIndex / 9)][curIndex % 9] = 0;
  return 1;
}
 
// assign numbers to the first row
void generateRow1()
{
  int numberFlag[10] = {0};
  numberFlag[0] = 1;
  int curNumber;
  int counter = 0;
 
  while(!checkIsNumberFull(numberFlag))
  {
    curNumber = getRandNumber();
    if(numberFlag[curNumber] == 0)
    {
      numberFlag[curNumber] = 1;
      map[counter / 9][counter % 9] = curNumber;  // ** why not change "counter / 9" to 0?
      counter++;
    }
  }
}
int getRandNumberForEmptyIndex()
{
  return rand() % (SIZE * SIZE);
}
int determine_emptyCnt(int level)
{
  int min = 0, max = 0;
 
  if(level == 1){
    min = SIZE * 3;
    max = SIZE * 4;
  }
  else if(level == 2){
    min = SIZE * 4 + 1;
    max = SIZE * 5;
  }
  else if(level == 3){
    min = SIZE * 5 + 1;
    max = SIZE * 6;
  }
 
  return rand() % (max - min + 1) + min;
}
void copy(int puzzle[9][9], int map[9][9])
{
  // copy.
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      puzzle[i][j] = map[i][j];
}

void gen_puzzle(int emptyCnt)
{
  // copy.
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      puzzle[i][j] = map[i][j];
  
 // Generate puzzle.
  for(int i = 0; i < emptyCnt; i++)
  {
    int emptyIndex = getRandNumberForEmptyIndex();
    while(puzzle[emptyIndex / 9][emptyIndex % 9] == 0)
      emptyIndex = getRandNumberForEmptyIndex();
    puzzle[emptyIndex / 9][emptyIndex % 9] = 0;
  }
}

bool SameRow(int x[2], int y[2])
{
  return (x[0] == y[0]);
}

bool SameCol(int x[2], int y[2])
{
  return (x[1] == y[1]);
}

bool SameBlock(int x[2], int y[2])
{
  return (x[0] / 3 == y[0] / 3 and x[1] / 3 == y[1] / 3);
}

// check the solution
void solveSudoku(int board[9][9], int ans[9][9], int ans_num[1])
{
	int idx[2] = {-1};
	
	for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
	    if(board[i][j] == 0){
        idx[0] = i;
        idx[1] = j;
        break;
		  }

	if(idx[0] != -1 and idx[1] != -1){
		int exclude[9] = {0};
    	int exclude_num = 0;

        for(int i = 0; i < 9; i++)
	    	for(int j = 0; j < 9; j++){
	    		int loc[2] = {i, j}; 
	    		
	    		if((SameRow(idx, loc) or SameCol(idx, loc) or SameBlock(idx, loc)) and (board[i][j] != 0)){
            int count = exclude_num;
            
						for(int k = 0; k <= count; k++){
							if(exclude[k] == board[i][j])
	              break;
	            else
	            	if(k == count){
	            		exclude[exclude_num] = board[i][j];
	                exclude_num += 1;
						    }
						}
				  }
			  }
		
		for(int m = 1; m <= 9; m++)
			for(int l = 0; l < exclude_num; l++){
			    if(m == exclude[l])
			      break;
          else
          	if(l == exclude_num - 1){
          		int new_board[9][9] = {0};
          		
          		for(int i = 0; i < 9; i++)
        		    for(int j = 0; j < 9; j++)
        		      new_board[i][j] = board[i][j];
        		      
	          	new_board[idx[0]][idx[1]] = m;
	            solveSudoku(new_board, ans, ans_num);
					  }
			}
	}

	else{
		for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
	      ans[i][j] = board[i][j];

		ans_num[0] += 1;
	}
}

void checkValidation(int puzzle[9][9], int emptyCnt, int genNum)
{
  gen_puzzle(emptyCnt);
  genNum += 1;
	
	// check the solution
	int ans[9][9] = {0};
	int ans_num[1] = {0};

	solveSudoku(puzzle, ans, ans_num);

	if(ans_num[0] != 1)
    checkValidation(puzzle, emptyCnt, genNum);
	else{
		cout << "This is the " << genNum << "-th puzzle:\n";
		showMap(puzzle);
    cout << "This is the solution:\n";
    showMap(ans);
  }
}

