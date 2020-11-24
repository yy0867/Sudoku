#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void printTitle(int xPadding, int yPadding, string path);

int main() {
    string path = "./Artworks/MainTitle.txt";
    printTitle(3, 3, path);
    return 0;
}
void printTitle(int xPadding, int yPadding, string path){ //It has screen clear serv
    ifstream title(path);
    system("clear");
    for (int i = 0; i < yPadding; i++){
        cout << endl; //y padding
    }

    while (!title.eof()) {
        string buf;
        getline(title, buf);
        for (int i = 0; i < xPadding; i++){
            cout << " "; //x padding
        }
        cout << buf << endl;
    }
    title.close();
}
