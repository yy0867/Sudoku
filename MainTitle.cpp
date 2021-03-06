#include "MainTitle.hpp"

void printTitle() {
    printTitle("./Artworks/MainTitle.txt", "Press Any Key");
}

void printGameOver(){
    printTitle("./Artworks/GameOver.txt", "Press Any Key");
}

void printGameClear(){
    printTitle("./Artworks/Clear.txt", "Press Any Key");
}

void printPause(){
    printTitle("./Artworks/Pause.txt", "Press Enter key");
}

void printTitle(const string path, const string ment){
    struct winsize console;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &console);

    printTitle(((console.ws_col) - getLargestWidth(path))/2, 3, path);// middle sorting
    printBlinkingComment(((console.ws_col) - ment.length()) / 2, 15, 37, ment);
    gotoxy(1000, 1000);
}

void printTitle(int xPadding, int yPadding, const string path){ //It has screen clear serv
    ifstream title(path);
    int strlen = 0;
    system("clear");
    for (int i = 0; i < yPadding; i++){
        cout << endl; //y padding
    }

    while (!title.eof()) {
        string buf;
        getline(title, buf);
        for (int i = 0; i < xPadding; i++) {
            cout << " "; //x padding
        }
        cout << buf << endl;
    }
    title.close();
}

int getLargestWidth(const string path){
    ifstream target(path);
    string buf;
    int largestWidth = 0;

    while (!target.eof()){
        getline(target, buf);
        if (largestWidth < buf.length()) {
            largestWidth = buf.length();
        }
    }
    cout << largestWidth << endl;
    target.close();
    return largestWidth;
}

void printBlinkingComment(int x, int y, int color, const string comment){
    gotoxy(x, y);
    printf("%c[5;%dm", 27, color);
    cout << comment;
    printf("%c[0m\n", 27);
}
