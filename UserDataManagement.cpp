#include "UserDataManagement.hpp"

UserDataManagement::UserDataManagement(dataType presentSudoku, double presentTime, string filePath){
    this->userTime = presentTime;
    this->userData = presentSudoku;
    this->filePath = filePath;
    mkdir(filePath.c_str(), 0777);
}

string UserDataManagement::makeSlotPath(int saveSlotNumber){
    string filePath = this->filePath;
    return filePath.append(saveFileName[saveSlotNumber]);
}

void UserDataManagement::loadData(int saveSlotNumber){ //path + file name
    loadSave(makeSlotPath(saveSlotNumber));
}

void UserDataManagement::loadSave(string filePath) {
    int fd = openFile(filePath, O_RDONLY);
    if (read(fd, &(this->userData), sizeof(dataType)) == -1) {
        perror("read() error");
    }
    if (read(fd, &(this->userTime), sizeof(double)) == -1) {
        perror("read() error");
    }
}

void UserDataManagement::loadData(dataType &sudokuSource, double &timeSource, int saveSlotNumber){
    loadData(saveSlotNumber);
    sudokuSource = this->userData;
    timeSource = this->userTime;
}

/*
void UserDataManagement::saveData(dataType &userData, double userTime, int saveSlotNumber){
    saveData(userData, userTime, makeSlotPath(saveSlotNumber));
}
*/

/*
void UserDataManagement::saveData() {
    int fd = openFile(this->filePath, O_CREAT | O_TRUNC | O_WRONLY);
    if (write(fd, &this->userData, sizeof(userData)) == -1) {
        perror("write() error");
    }
    if (write(fd, &this->userTime, sizeof(double)) == -1) {
        perror("write() error");
    }
    close(fd);
}
*/


int UserDataManagement::openFile(string filePath, int flags) {
    int fd = open(filePath.c_str(), flags, 0777);
    if (fd == -1) {
        perror("open() error");
    }
    return fd;
}


UserDataManagement::~UserDataManagement(){
    //delete saveFileName;
}


/*void UserDataManagement::saveData(int saveSlotNumber){//p
    //saveData(this->userData, this->userTime, saveSlotNumber);
    saveData(this->userData, this->userTime, makeSlotPath(saveSlotNumber));
}*/



void UserDataManagement::saveData(dataType userData, double userTime, int saveSlotNumber) {
     int fd = openFile(makeSlotPath(saveSlotNumber), O_CREAT | O_TRUNC | O_WRONLY);
    if (write(fd, &userData, sizeof(userData)) == -1) {
        perror("write() error");
    }
    if (write(fd, &userTime, sizeof(double)) == -1) {
        perror("write() error");
    }
    close(fd);
}
/*
void UserDataManagement::saveData(dataType &userData, double userTime, string filePath){

}
*/
