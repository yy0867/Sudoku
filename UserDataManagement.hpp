#include <fcntl.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Sudoku.hpp"

#define SAVE_DATA_NUM = 3
typedef Sudoku dataType;

using namespace std;

class UserDataManagement {
  private:
    string filePath;
    string saveFileName[3] = {"sudoku_save_0", "sudoku_save_1", "sudoku_save_2"};
    dataType userData;
    double userTime;

    int openFile(string filePath, int flags);
    string makeSlotPath(int saveSlotNumber);
    void loadSave(string filePath);
    void loadData(int saveSlotNumber);

    void saveData(dataType &userData, double userTime, string filePath);
    void saveData(dataType &userData, double userTime, int saveSlotNumber);

  public:
    UserDataManagement(dataType &presentSudoku, double &presentTime, string filePath = "./Save/");
    ~UserDataManagement();

    void saveData(int saveSlotNumber);
    void loadData(dataType &sudokuSource, double &timeSource);
    //dataType &getData();
    //int getTime();
};
