#include "Sudoku.hpp"
#include "getkey.hpp"
#include <iostream>

using namespace std;

Sudoku::Sudoku(int level) {
    x = 3, y = 2;
<<<<<<< HEAD
    row = 0, col = 0;
=======
    row = 0, column = 0;
>>>>>>> Optimize map, cursor printing
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sudoku[i][j] = 0;
            origin[i][j] = false;
        }
    }

    while (level > 0) {
        int rand_row = random() - 1, rand_col = random() - 1,
            rand_num = random();

        if (value_possible(rand_row, rand_col, rand_num)) {
            set_sudoku(rand_row, rand_col, rand_num);
            origin[rand_row][rand_col] = true;
            level--;
        }
    }
}

<<<<<<< HEAD
bool out_of_bound(const int row, const int col, const int num = 3) {
    if (row < 0 || row >= N || col < 0 || col >= N || num <= 0 || num > N) {
=======
bool out_of_bound(const int row, const int column, const int num = 3) {
    if (row < 0 || row >= N || column < 0 || column >= N || num <= 0 ||
        num > N) {
>>>>>>> Optimize map, cursor printing
        // perror("value out of range!");
        return true;
    }
    return false;
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

<<<<<<< HEAD
bool Sudoku::value_possible(const int row, const int col, const int num) const {
    // check row, col, num in range
    if (out_of_bound(row, col, num))
        return false;

    // check coord has value
    if (sudoku[row][col] != 0)
        return false;

    const int sq_row = (row / 3) * 3, sq_col = (col / 3) * 3;

    // check horizon
    for (int i = 0; i < N; i++) {
        if (i == col)
=======
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
>>>>>>> Optimize map, cursor printing
            continue;
        if (sudoku[row][i] != 0 && sudoku[row][i] == num)
            return false;
    }

    // check vertical
    for (int i = 0; i < N; i++) {
        if (i == row)
            continue;
<<<<<<< HEAD
        if (sudoku[i][col] != 0 && sudoku[i][col] == num)
=======
        if (sudoku[i][column] != 0 && sudoku[i][column] == num)
>>>>>>> Optimize map, cursor printing
            return false;
    }

    // check square
    for (int i = sq_row; i < sq_row + 3; i++) {
        for (int j = sq_col; j < sq_row + 3; j++) {
<<<<<<< HEAD
            if (i == row && j == col)
=======
            if (i == row && j == column)
>>>>>>> Optimize map, cursor printing
                continue;
            if (sudoku[i][j] == num)
                return false;
        }
    }

    return true;
}

<<<<<<< HEAD
bool Sudoku::remove(const int row, const int col) {
    // row, col out of bound or can't remove
    if (out_of_bound(row, col) || origin[row][col])
        return false;

    sudoku[row][col] = 0;
=======
bool Sudoku::remove(const int row, const int column) {
    // row, column out of bound or can't remove
    if (out_of_bound(row, column) || origin[row][column])
        return false;

    sudoku[row][column] = 0;
>>>>>>> Optimize map, cursor printing
    return true;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

void Sudoku::print_form() const {
    for (int y = 0; y < FORM_SIZE; y++) {
        if (y % 4 == 0) {
            for (int i = 0; i < FORM_SIZE * 2; i++) {
                printColorCursor(X_PADDING + i, y + 1, 94, "━");
            }
        }
        for (int x = 0; x < 4; x++) {
            if (y == 0) {
                printColorCursor(X_PADDING + x * 8, y + 1, 94, "┳┳");
            } else if (y == 12) {
                printColorCursor(X_PADDING + x * 8, y + 1, 94, "┻┻");
            } else if (y % 4 == 0) {
                printColorCursor(X_PADDING + x * 8, y + 1, 94, "╋╋");
            } else {
                printColorCursor(X_PADDING + x * 8, y + 1, 94, "┃┃");
            }
        }
    }
}

<<<<<<< HEAD
void Sudoku::print() const {
    gotoxy(1, 1);
    print_form();
    int r = 0, c = 0;
    for (int i = 0; i < FORM_SIZE; i++) {
        c = 0;
        for (int j = 0; i % 4 != 0 && j < FORM_SIZE; j++) {
            if (j % 4 != 0) {
                gotoxy(j * 2 + 1, i + 1);
                if (sudoku[r][c]) {
                    if (!origin[r][c]) {
                        printf("\033[33m");
                        cout << sudoku[r][c] << " ";
                        printf("\033[0m");
                    } else {
                        printf("\033[34m");
                        cout << sudoku[r][c] << " ";
                        printf("\033[0m");
                    }
                }
                c++;
            }
        }
        if (i % 4 != 0)
            r++;
    }

    gotoxy(1, 15);
}

=======
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
                        /*printf("\033[33m");
                        cout << (char)(sudoku[row][column] + 48) << " ";
                        printf("\033[0m");*/
                    } else {
                        printColorCursor(j * 2 + 1, i + 1, 34,
                                         (char)(sudoku[row][column] + 48));
                        /*printf("\033[34m");
                        cout << (char)(sudoku[row][column] + 48) << " ";
                        printf("\033[0m");*/
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

bool Sudoku::isFrameCursor(int cursor) const {
    if (cursor % FRAME_INTERVAR == 0) {
        return true;
    } else {
        return false;
    }
}

void Sudoku::printBoard() const {
    gotoxy(X_PADDING, 1);
    print_form();
    for (int i = 0, row = 0; i < FORM_SIZE; i++) {
        for (int j = 0, column = 0; !isFrameCursor(i) && j < FORM_SIZE; j++) {
            if (!isFrameCursor(j)) {
                if (sudoku[row][column]) {
                    // printColorCursor(j * 2 + 1, i + 1, 34,
                    // sudoku[row][column]);
                    printColorCursor(
                        j * 2 + 1, i + 1, 34,
                        convertNumberToFullChar(sudoku[row][column]));
                }
                column++;
            }
        }
        if (!isFrameCursor(i))
            row++;
    }
    gotoxy(X_PADDING, 15);
}

void Sudoku::printColorCursor(int x, int y, int color, const string str) const {
    gotoxy(x, y);
    cout << "\033[" << color << "m" << str << "\033[0m";
}

void Sudoku::printColorCursor(int x, int y, int color, char *str) const {
    gotoxy(x, y);
    char *temp = str;
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

<<<<<<< HEAD
void Sudoku::printCursor() const {}

>>>>>>> Optimize map, cursor printing
=======
>>>>>>> Optimize board, number printing
bool Sudoku::cursor_possible(const int new_x, const int new_y) const {
    if ((new_x % 2 == 0 || new_x < 1 || new_x > 24 || (new_x - 1) % 8 == 0) ||
        (new_y < 1 || new_y > 12 || (new_y - 1) % 4 == 0))
        return false;
    return true;
}

bool is_digit(int key) { return (1 <= key - KEY_NUM && key - KEY_NUM <= 9); }

<<<<<<< HEAD
<<<<<<< HEAD
void Sudoku::cursor() {
    int num = sudoku[row][col];
=======
=======
char *Sudoku::convertNumberToFullChar(int num) const { // input 0 ~ 9 integer
    char fullNum[] = "０";
    fullNum[2] += num;
    char *result = fullNum;
    return result;
}

>>>>>>> Optimize board, number printing
void Sudoku::moveCursor() {
    int num = sudoku[row][column];
    if (num)
        printColorCursor(x, y, 7, convertNumberToFullChar(num));
    else
        printColorCursor(x, y, 7, "  ");

    gotoxy(23, 15);
    // cout << "                       ";
    moveCursor(get_key());
}

void Sudoku::moveCursor(int key) {
    if (is_digit(key)) {
        if (!origin[row][column]) {
            if (!value_possible(row, column, key - KEY_NUM)) {
                printColorCursor(X_PADDING, 15, 33, "Can't insert number!");
            } else
                sudoku[row][column] = key - KEY_NUM;
        }
        return;
    }

    if (sudoku[row][column])
        printColorCursor(x, y, 33,
                         convertNumberToFullChar(sudoku[row][column]));
    else
        printColorCursor(x, y, 33, "  ");

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
}

void Sudoku::cursor() { // Alternated
    int num = sudoku[row][column];
>>>>>>> Optimize map, cursor printing

    gotoxy(x, y);
    printf("\033[7m");
    if (num)
        cout << num;
    printf("\033[0m");

    int key = get_key();
    gotoxy(1, 15);
    cout << "                       ";

    if (is_digit(key)) {
<<<<<<< HEAD
        if (!origin[row][col]) {
            if (!value_possible(row, col, key - KEY_NUM)) {
=======
        if (!origin[row][column]) {
            if (!value_possible(row, column, key - KEY_NUM)) {
>>>>>>> Optimize map, cursor printing
                gotoxy(1, 15);
                printf("\033[32m");
                cout << "Can't insert number!" << endl;
                printf("\033[0m");
            } else
<<<<<<< HEAD
                sudoku[row][col] = key - KEY_NUM;
=======
                sudoku[row][column] = key - KEY_NUM;
>>>>>>> Optimize map, cursor printing
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
<<<<<<< HEAD
            col++;
        } else if (cursor_possible(x + 4, y)) {
            x += 4;
            col++;
=======
            column++;
        } else if (cursor_possible(x + 4, y)) {
            x += 4;
            column++;
>>>>>>> Optimize map, cursor printing
        }
        break;
    case KEY_LEFT:
        if (cursor_possible(x - 2, y)) {
            x -= 2;
<<<<<<< HEAD
            col--;
        } else if (cursor_possible(x - 4, y)) {
            x -= 4;
            col--;
        }
        break;
    case KEY_DELETE:
        remove(row, col);
=======
            column--;
        } else if (cursor_possible(x - 4, y)) {
            x -= 4;
            column--;
        }
        break;
    case KEY_DELETE:
        remove(row, column);
>>>>>>> Optimize map, cursor printing
        break;
    }
}
