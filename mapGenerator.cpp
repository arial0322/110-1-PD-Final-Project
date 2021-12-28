  #include <iostream>
  #include <stdlib.h>      // srand()
  #include <time.h>        // time()
  using namespace std;

  void showMap(int map[9][9]);
  bool isMapLegal();
  bool isMapFull();
  bool checkIsNumberFull(int arr[9]);
  int getRandNumber();
  int generateMap(int curIndex);
  void generateRow1();

  int map[9][9] = {0};      // initialise map

  int main()
  {
    generateRow1();
    generateMap(9);
    showMap(map);
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
        {
          if(tempArr[map[i][j]] == 0)
            tempArr[map[i][j]] = 1;
          else
            return false;
        }
    }

    //check the col
    for(int j = 0; j < 9; j++)
    {
      int tempArr[10] = {0};
      for(int i = 0; i < 9; i++)
        if(map[i][j] != 0)
        {
          if(tempArr[map[i][j]] == 0)
            tempArr[map[i][j]] = 1;
          else
            return false;
        }
    }

    //check the 9-box
    for(int m = 0; m < 9; m += 3)
      for(int n = 0; n < 9; n += 3)
      {
        int tempArr[10] = {0};
        for(int i = 0; i < 3; i++)
          for(int j = 0; j < 3; j++)
            if(map[m + i][n + j] != 0)
            {
              if(tempArr[map[m + i][n + j]] == 0)
                tempArr[map[m + i][n + j]] = 1;
              else
                return false;
            }
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
    srand((unsigned int)time(0));
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

    srand((unsigned)time(NULL));
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
