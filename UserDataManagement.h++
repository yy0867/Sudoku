#include <fcntl.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SAVE_DATA_NUM = 3
typedef int dataType;

using namespace std;

class UserDataManagement {
  private:
    int &UserDataManagement::openFile(string filePath, int pipe);

  public:
    dataType &loadData(string filePath);
    void saveData(dataType &userData, string filePath);
};
