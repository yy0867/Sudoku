#include"ConsoleCursor.hpp"

using namespace std;

void gotoxy(int x, int y) {
    cout << "\033[" << y << ";" << x << "f" << flush;
}

void printColorCursor(int x, int y, string multiColor, const string str) {
    gotoxy(x, y);
    cout << "\033[" << multiColor << "m" << str << "\033[0m" << flush;
}

void printColorCursor(int x, int y, int color, const string str) {
    gotoxy(x, y);
    cout << "\033[" << color << "m" << str << "\033[0m" << flush;
}

/*
void printColorCursor(int x, int y, int color, const char *str) {
    gotoxy(x, y);
    const char *temp = str;
    printf("\033[%dm%s\033[0m", color, temp);
}
*/

void printColorCursor(int x, int y, int color, const int str) {
    gotoxy(x, y);
    printf("\033[%dm%d \033[0m", color, str);
}
