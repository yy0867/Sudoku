#include "Sudoku.hpp"
#include "ConsoleCursor.hpp"
#include "Frame.hpp"
#include "string"
#include "timeattack.hpp"
#include "getkey.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

bool is_inMenu = false;
int current_menu = 0;

/*//Replace to ConsoleCursor
void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
*/

//void signalHandler(int signum);

bool is_digit(int key) { return (1 <= key - KEY_NUM && key - KEY_NUM <= 9); }

bool out_of_bound(const int row, const int column, const int num) {
    if (row < 0 || row >= N || column < 0 || column >= N || num <= 0 ||
        num > N) {
        // perror("value out of range!");
        return true;
    }
    return false;
}

bool is_same_group(int first, int second) { return (first / 3 == second / 3); }

Sudoku::Sudoku(int level) {
    x = 1 + X_PADDING, y = 1 + Y_PADDING;
    row = 0, column = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sudoku[i][j] = 0;
            origin[i][j] = true;
        }
    }

    // set up basic sudoku
    for (int i = 0; i < N; i++)
        sudoku[0][i] = i + 1;

    for (int i = 1; i < 3; i++)
        for (int j = 0; j < N; j++)
            sudoku[i][j] = (sudoku[i - 1][j] >= 7) ? sudoku[i - 1][j] - 6
                                                   : sudoku[i - 1][j] + 3;

    for (int i = 3; i < N; i++)
        for (int j = 0; j < N; j++)
            sudoku[i][j] = (sudoku[i - 3][j] == 9)
                               ? sudoku[i][j] = 1
                               : sudoku[i][j] = sudoku[i - 3][j] + 1;

    // randomize basic sudoku
    //randomize_sudoku();
    make_blank(level);
}

void Sudoku::randomize_sudoku() {
    int count = random(1500) + 600;
    int first, second;
    for (int t = 0; t < count; t++) {
        first = random() - 1;
        second = random() - 1;

        if (first == second)
            continue;

        int rand = random(5);
        switch (rand) {
        case ROW_LINE:
            if (is_same_group(first, second))
                swap_line(first, second, ROW_LINE);
            break;
        case COL_LINE:
            if (is_same_group(first, second))
                swap_line(first, second, COL_LINE);
            break;
        case ROW_GROUP:
            if (is_same_group(first, second))
                break;
            swap_group(first % 3, second % 3, ROW_GROUP);
            break;
        case COL_GROUP:
            if (is_same_group(first, second))
                break;
            swap_group(first % 3, second % 3, COL_GROUP);
            break;
        case NUM:
            swap_number(first + 1, second + 1);
            break;
        }
    }
}

void Sudoku::make_blank(int level) {
    while (level > 0) {
        int r = random();
        int c = random();
        if (!origin[r][c])
            continue;
        sudoku[r][c] = 0;
        origin[r][c] = false;
        level--;
    }
}

int Sudoku::random(const int n) {
    // n should be bigger than 0
    // generate random number 1 ~ n
    if (n <= 0) {
        // perror("n must be positive!");
        return -1;
    }
    return ((rand() % n) + 1);
}

bool Sudoku::value_possible(const int row, const int column,
                            const int num) const {
    // check row, column, num in range
    if (out_of_bound(row, column, num))
        return false;

    // check coord has value
    if (sudoku[row][column] != 0)
        return false;

    const int sq_row = (row / 3) * 3, sq_col = (column / 3) * 3;

    // check horizon
    for (int i = 0; i < N; i++) {
        if (i == column)
            continue;
        if (sudoku[row][i] != 0 && sudoku[row][i] == num)
            return false;
    }

    // check vertical
    for (int i = 0; i < N; i++) {
        if (i == row)
            continue;
        if (sudoku[i][column] != 0 && sudoku[i][column] == num)
            return false;
    }

    // check square
    for (int i = sq_row; i < sq_row + 3; i++) {
        for (int j = sq_col; j < sq_col + 3; j++) {
            if (i == row && j == column)
                continue;
            if (sudoku[i][j] == num)
                return false;
        }
    }

    return true;
}

bool Sudoku::remove(const int row, const int column) {
    // row, column out of bound or can't remove
    if (out_of_bound(row, column) || origin[row][column])
        return false;

    sudoku[row][column] = 0;
    return true;
}

/* Replace to Frame
void Sudoku::printFrame(int x, int y, int width, int height, string multiColor,
string rowEdge, string columnEdge) const { int xOffset, yOffset;
    printColorCursor(X_PADDING + x, y + Y_PADDING, multiColor, "┏");
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor,
rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor, "┓");
    for (yOffset = 1; yOffset <= height; yOffset++){
        printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor,
columnEdge); printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset,
multiColor, columnEdge);
    }
    printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor, "┗");
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset,
multiColor, rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset,
multiColor, "┛");
}

void Sudoku::printFrame(int x, int y, int width, int height, int color) const {
    printFrame(x, y, width, height, to_string(color),  "━", "┃");
}

void Sudoku::printFrameCursor(int x, int y, int width, int height, int color)
const { string blink = "5;"; //blink option printFrame(x, y, width, height,
blink.append(to_string(color)), " ", " ");
}
*/
void Sudoku::print_form() const {
    for (int y = 0; y < FORM_SIZE; y++) {
        if (y % 4 == 0) {
            for (int i = 1; i < 21; i++) {
                printColorCursor(X_PADDING + i, y + Y_PADDING, 94, "━");
            }
        }
        for (int x = 0; x < 4; x++) { //┏┓┗┛┫┣
            if (y == 0) {
                if (x == 0) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┏");
                } else if (x == 3) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┓");
                } else {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┳");
                }
            } else if (y == 12) {
                if (x == 0) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┗");
                } else if (x == 3) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┛");
                } else {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┻");
                }
            } else if (y % 4 == 0) {
                if (x == 0) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┣");
                } else if (x == 3) {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┫");
                } else {
                    printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "╋");
                }
            } else {
                printColorCursor(X_PADDING + x * 7, y + Y_PADDING, 94, "┃");
            }
        }
    }
}

bool Sudoku::isFrameCursor(int cursor) const {
    if (cursor % FRAME_INTERVAR == 0) {
        return true;
    } else {
        return false;
    }
}

void Sudoku::printBoard() const {
    print_form();
    for (int column = 0, columnFrame = 0; column < 9; column++) {
        if (!(column % ROW_FRAME_INTERVAR)) {
            columnFrame++;
        }
        for (int row = 0, rowFrame = 0; row < 9; row++) {
            if (!(row % COLUMN_FRAME_INTERVAR)) {
                rowFrame++;
            }
            if (sudoku[column][row]) {
                if(origin[column][row]){
                    printColorCursor(row * 2 + rowFrame + X_PADDING,
                                 column + columnFrame + Y_PADDING,
                                 DEFAULT_FONT_COLOR,
                                 convertNumberToFullChar(sudoku[column][row]));
                } else {
                    printColorCursor(row * 2 + rowFrame + X_PADDING,
                                 column + columnFrame + Y_PADDING,
                                 CUSTOM_FONT_COLOR,
                                 convertNumberToFullChar(sudoku[column][row]));
                }

            }
        }
    }
    gotoxy(X_PADDING, 15);
}

void Sudoku::moveCursor() {
    int num = sudoku[row][column];
    if (num)
        printColorCursor(x, y, 7, convertNumberToFullChar(num));
    else
        printColorCursor(x, y, 7, "  ");
    gotoxy(50 + X_PADDING, 0);
    moveCursor(get_key());
}

void Sudoku::moveCursor(int key) {
    if (is_digit(key)) {
        if (!origin[row][column]) {
            if (!value_possible(row, column, key - KEY_NUM)) {
                printColorCursor(X_PADDING, 14 + Y_PADDING, CUSTOM_FONT_COLOR,
                                 "Can't insert number!");
            } else
                sudoku[row][column] = key - KEY_NUM;
        }
        return;
    }
    printColorCursor(X_PADDING, 14 + Y_PADDING, DEFAULT_FONT_COLOR,
                     "                     ");
    int fontColor;
    if (origin[row][column]) {
        fontColor = DEFAULT_FONT_COLOR;
    } else {
        fontColor = CUSTOM_FONT_COLOR;
    }

    if (sudoku[row][column])
        printColorCursor(x, y, fontColor,
                         convertNumberToFullChar(sudoku[row][column]));
    else
        printColorCursor(x, y, DEFAULT_FONT_COLOR, "  ");
    switch (key) {
    case KEY_UP:
        if (is_inMenu == true) {
            if (current_menu != 0) {
                removeFrame(29, 9 - (3 - current_menu) * 5, 20, 3);
                printFrameCursor(29, 9 - (4 - current_menu) * 5, 20, 3, 94);
                current_menu--;
            }
        } else {
            if (isCursorPossible(x, y - 1)) {
                y -= 1;
                row--;
            } else if (isCursorPossible(x, y - 2)) {
                y -= 2;
                row--;
            }
        }
        break;
    case KEY_DOWN:
        if (is_inMenu == true) {
            if (current_menu != 3) {
                removeFrame(29, -6 + current_menu * 5, 20, 3);
                printFrameCursor(29, -6 + (1 + current_menu) * 5, 20, 3, 94);
                current_menu++;
            }
        } else {
            if (isCursorPossible(x, y + 1)) {
                y += 1;
                row++;
            } else if (isCursorPossible(x, y + 2)) {
                y += 2;
                row++;
            }
        }
        break;
    case KEY_RIGHT:
        if (is_inMenu == false) {
            if (isCursorPossible(x + 2, y)) {
                x += 2;
                column++;
            } else if (isCursorPossible(x + 3, y)) {
                x += 3;
                column++;
            } else {
                printFrameCursor(29, -6, 20, 3, 94);
                is_inMenu = true;
            }
        }
        break;
    case KEY_LEFT:
        if (is_inMenu == true) {
            removeFrame(29, -6 + current_menu * 5, 20, 3);
            current_menu = 0;
            is_inMenu = false;
        } else {
            if (isCursorPossible(x - 2, y)) {
                x -= 2;
                column--;
            } else if (isCursorPossible(x - 3, y)) {
                x -= 3;
                column--;
            }
        }
        break;
    case KEY_ENTER:
        if (is_inMenu == true) {
            if (current_menu == 0) {
                // pause time
                gotoxy(20, 30);
                cout << getTimePid() << endl;

                
                while(get_key() != KEY_ENTER) {}
            } else if (current_menu == 1) {
                // reset
                out = true;
                is_reset = true;
                is_inMenu = false;
                current_menu = 0;
            } else if (current_menu == 2) {
                // save
            } else {
                // return to menu
                out = true;
                is_inMenu = false;
                current_menu = 0;
            }
        }
        break;
    case KEY_DELETE:
        remove(row, column);
        break;
    }
}
/* Alternated
char *Sudoku::convertNumberToFullChar(int num) const { // input 0 ~ 9
integer char fullNum[] = "０"; fullNum[2] += num; char *result = fullNum;
    return result;
}
*/

string Sudoku::convertNumberToFullChar(int num) const { // input 0 ~ 9 integer
    char fullNum[] = "０";
    fullNum[2] += num;
    string result = fullNum;
    return result;
}

// Replace to ConsoleCursor
/*
void Sudoku::printColorCursor(int x, int y, string multiColor, const string
str) const { gotoxy(x, y); cout << "\033[" << multiColor << "m" << str <<
"\033[0m"
<< flush;
}

void Sudoku::printColorCursor(int x, int y, int color, const string str)
const { gotoxy(x, y); cout << "\033[" << color << "m" << str << "\033[0m" <<
flush;
}


void Sudoku::printColorCursor(int x, int y, int color, const char *str)
const { gotoxy(x, y); const char *temp = str; printf("\033[%dm%s\033[0m",
color, temp);
}


/*
void Sudoku::printColorCursor(int x, int y, int color, const char str) const
{ gotoxy(x, y); printf("\033[%dm%c \033[0m", color, str);
}


void Sudoku::printColorCursor(int x, int y, int color, const int str) const
{ gotoxy(x, y); printf("\033[%dm%d \033[0m", color, str);
}
*/

bool Sudoku::isCursorPossible(const int xPos, const int yPos) const {
    return isInside(xPos, yPos) && isFrameCursor(xPos, yPos);
}

bool Sudoku::isInside(const int xPos, const int yPos) const {
    if (xPos < X_PADDING ||
        xPos > (20 + X_PADDING)) { // x position out, 21 = 3*(1+3*2)
        return false;
    }
    if (yPos < Y_PADDING ||
        yPos > (12 + Y_PADDING)) { // y position out , 12 = 3*(1+3)
        return false;
    }
    return true;
}

bool Sudoku::isFrameCursor(const int xPos, const int yPos) const {
    if (xPos == (6 + X_PADDING) || xPos == (7 + X_PADDING) ||
        xPos == (13 + X_PADDING) ||
        xPos == (14 + X_PADDING)) { // x position out, 21 = 3*(1+3*2)
        return false;
    }
    if ((yPos - Y_PADDING) % 4 == 0) { //
        return false;
    }
    return true;
}

void Sudoku::swap_line(int first, int second, int flag) {
    int temp[N];
    for (int i = 0; i < N; i++) {
        temp[i] = (flag == ROW_LINE) ? sudoku[i][first] : sudoku[first][i];
    }
    for (int i = 0; i < N; i++) {
        if (flag == ROW_LINE)
            sudoku[i][first] = sudoku[i][second];
        else
            sudoku[first][i] = sudoku[second][i];
    }
    for (int i = 0; i < N; i++) {
        if (flag == ROW_LINE)
            sudoku[i][second] = temp[i];
        else
            sudoku[second][i] = temp[i];
    }
}

void Sudoku::swap_group(int first, int second, int flag) {
    flag -= 2;
    for (int i = 0; i < 3; i++)
        swap_line(first * 3 + i, second * 3 + i, flag);
}

void Sudoku::swap_number(int first, int second) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sudoku[i][j] == first)
                sudoku[i][j] = second;
            else if (sudoku[i][j] == second)
                sudoku[i][j] = first;
        }
    }
}