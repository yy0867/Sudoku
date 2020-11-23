﻿#include "Sudoku.hpp"
//#include "getkey.hpp"

#define DEFAULT_FONT_COLOR 32
#define CUSTOM_FONT_COLOR 37

using namespace std;

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

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
    randomize_sudoku();
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
        for (int j = sq_col; j < sq_row + 3; j++) {
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
                printColorCursor(row * 2 + rowFrame + X_PADDING,
                                 column + columnFrame + Y_PADDING,
                                 DEFAULT_FONT_COLOR,
                                 convertNumberToFullChar(sudoku[column][row]));
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
                printColorCursor(X_PADDING, 14 + Y_PADDING,
                                 DEFAULT_FONT_COLOR + X_PADDING,
                                 "Can't insert number!");
            } else
                sudoku[row][column] = key - KEY_NUM;
        }
        return;
    }
    printColorCursor(X_PADDING, 14 + Y_PADDING, DEFAULT_FONT_COLOR + X_PADDING,
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
        if (isCursorPossible(x, y - 1)) {
            y -= 1;
            row--;
        } else if (isCursorPossible(x, y - 2)) {
            y -= 2;
            row--;
        }
        break;
    case KEY_DOWN:
        if (isCursorPossible(x, y + 1)) {
            y += 1;
            row++;
        } else if (isCursorPossible(x, y + 2)) {
            y += 2;
            row++;
        }
        break;
    case KEY_RIGHT:
        if (isCursorPossible(x + 2, y)) {
            x += 2;
            column++;
        } else if (isCursorPossible(x + 3, y)) {
            x += 3;
            column++;
        }
        break;
    case KEY_LEFT:
        if (isCursorPossible(x - 2, y)) {
            x -= 2;
            column--;
        } else if (isCursorPossible(x - 3, y)) {
            x -= 3;
            column--;
        }
        break;
    case KEY_DELETE:
        remove(row, column);
        break;
    }
}

char *Sudoku::convertNumberToFullChar(int num) const { // input 0 ~ 9 integer
    char fullNum[] = "０";
    fullNum[2] += num;
    char *result = fullNum;
    return result;
}

/*
void Sudoku::printColorCursor(int x, int y, int color, const string str) const {
    gotoxy(x, y);
    cout << "\033[" << color << "m" << str << "\033[0m";
}*/

void Sudoku::printColorCursor(int x, int y, int color, const char *str) const {
    gotoxy(x, y);
    const char *temp = str;
    printf("\033[%dm%s\033[0m", color, temp);
}

void Sudoku::printColorCursor(int x, int y, int color, const char str) const {
    gotoxy(x, y);
    printf("\033[%dm%c \033[0m", color, str);
}

void Sudoku::printColorCursor(int x, int y, int color, const int str) const {
    gotoxy(x, y);
    printf("\033[%dm%d \033[0m", color, str);
}

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

/*
void Sudoku::print() const { // Alternated
    gotoxy(1, 1);
    print_form();
    int row = 0, column = 0;
    for (int i = 0; i < FORM_SIZE; i++) {
        column = 0;
        for (int j = 0; i % 4 != 0 && j < FORM_SIZE; j++) {
            if (j % 4 != 0) {
                // gotoxy(j * 2 + 1, i + 1);
                if (sudoku[row][column]) {
                    if (!origin[row][column]) {
                        printColorCursor(j * 2 + 1, i + 1, 33,
                                         (char)(sudoku[row][column] + 48));
                        printf("\033[33m");
                        cout << (char)(sudoku[row][column] + 48) << " ";
                        printf("\033[0m");
                    } else {
                        printColorCursor(j * 2 + 1, i + 1, 34,
                                         (char)(sudoku[row][column] + 48));
                        /*printf("\033[34m");
                        cout << (char)(sudoku[row][column] + 48) << " ";
                        printf("\033[0m");
                    }
                }
                column++;
            }
        }
        if (i % 4 != 0)
            row++;
    }

    gotoxy(1, 15);
}
*/

/*
bool Sudoku::cursor_possible(const int new_x,
                             const int new_y) const { // Alternated
    if ((new_x % 2 == 0 || new_x < 1 || new_x > 24 || (new_x - 1) % 8 == 0) ||
        (new_y < 1 || new_y > 12 || (new_y - 1) % 4 == 0))
        return false;
    return true;
}*/

/*
void Sudoku::cursor() { // Alternated
    int num = sudoku[row][column];

    gotoxy(x, y);
    printf("\033[7m");
    if (num)
        cout << num;
    printf("\033[0m");

    int key = get_key();
    gotoxy(1, 15);
    cout << "                       ";

    if (is_digit(key)) {
        if (!origin[row][column]) {
            if (!value_possible(row, column, key - KEY_NUM)) {
                gotoxy(1, 15);
                printf("\033[32m");
                cout << "Can't insert number!" << endl;
                printf("\033[0m");
            } else
                sudoku[row][column] = key - KEY_NUM;
        }
        return;
    }

    switch (key) {
    case KEY_UP:
        if (cursor_possible(x, y - 1)) {
            y -= 1;
            row--;
        } else if (cursor_possible(x, y - 2)) {
            y -= 2;
            row--;
        }
        break;
    case KEY_DOWN:
        if (cursor_possible(x, y + 1)) {
            y += 1;
            row++;
        } else if (cursor_possible(x, y + 2)) {
            y += 2;
            row++;
        }
        break;
    case KEY_RIGHT:
        if (cursor_possible(x + 2, y)) {
            x += 2;
            column++;
        } else if (cursor_possible(x + 4, y)) {
            x += 4;
            column++;
        }
        break;
    case KEY_LEFT:
        if (cursor_possible(x - 2, y)) {
            x -= 2;
            column--;
        } else if (cursor_possible(x - 4, y)) {
            x -= 4;
            column--;
        }
        break;
    case KEY_DELETE:
        remove(row, column);
        break;
    }
}*/
