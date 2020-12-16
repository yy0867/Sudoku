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


    int openFile(string filePath, int flags);
    string makeSlotPath(int saveSlotNumber);
    void loadSave(string filePath);
    void loadData(int saveSlotNumber);




  public:
    dataType userData;
    double userTime;
    UserDataManagement(dataType &presentSudoku, double &presentTime, string filePath = "./Save/");
    ~UserDataManagement();
    void saveData();


    void saveData(dataType &userData, double userTime,
                                  int saveSlotNumber);
    void saveData(int saveSlotNumber);
    void loadData(dataType &sudokuSource, double &timeSource, int saveSlotNumber);
    void loadData(int saveSlotNumber);
    dataType &getData();
    int getTime();

    void saveData(dataType userData, double userTime); //bring data
    void saveData(dataType &userData, double userTime, string filePath);
};
