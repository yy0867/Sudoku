#include "UserDataManagement.hpp"

UserDataManagement::UserDataManagement(string filePath){ //  filePath must end /
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

void UserDataManagement::saveData(dataType &userData, double userTime, int saveSlotNumber){
    saveData(userData, userTime, makeSlotPath(saveSlotNumber));
}

void UserDataManagement::saveData(dataType &userData, double userTime, string filePath) {
    int fd = openFile(filePath, O_CREAT | O_TRUNC | O_WRONLY);
    if (write(fd, &userData, sizeof(userData)) == -1) {
        perror("write() error");
    }
    if (write(fd, &userTime, sizeof(double)) == -1) {
        perror("write() error");
    }
    close(fd);
}

int UserDataManagement::openFile(string filePath, int flags) {
    int fd = open(filePath.c_str(), flags, 0777);
    if (fd == -1) {
        perror("open() error");
    }
    return fd;
}

void UserDataManagement::loadData(dataType &sudokuSource, double &timeSource){
    sudokuSource = this->userData;
    timeSource = this->userTime;
}

UserDataManagement::~UserDataManagement(){
    //delete saveFileName;
}
