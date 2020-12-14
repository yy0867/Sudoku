#include "UserDataManagement.h++"

dataType &UserDataManagement::loadData(string filePath) {
    dataType userData;
    int fd = openFile(filePath, O_RDONLY);
    if (read(fd, &userData, sizeof(dataType)) == -1) {
        perror("read() error");
    }
    return userData;
}

void UserDataManagement::saveData(dataType &userData, string filePath) {
    int fd = openFile(filePath, O_CREAT | O_APPEND | O_WRONLY);
    if (write(fd, &userData, sizeof(userData)) == -1) {
        perror("write() error");
    }
    close(fd);
}

int &UserDataManagement::openFile(string filePath, int pipe) {
    int fd = open(filePath.c_str(), pipe, 0644);
    if (fd == -1) {
        perror("open() error");
    }
    return fd;
}
