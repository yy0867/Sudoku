#include "Sudoku.hpp"
#include "getkey.hpp"
#include <iostream>

using namespace std;

Sudoku::Sudoku(int level) {
    x = 3, y = 2;
    row = 0, col = 0;
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

bool out_of_bound(const int row, const int col, const int num = 3) {
    if (row < 0 || row >= N || col < 0 || col >= N || num <= 0 || num > N) {
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
            continue;
        if (sudoku[row][i] != 0 && sudoku[row][i] == num)
            return false;
    }

    // check vertical
    for (int i = 0; i < N; i++) {
        if (i == row)
            continue;
        if (sudoku[i][col] != 0 && sudoku[i][col] == num)
            return false;
    }

    // check square
    for (int i = sq_row; i < sq_row + 3; i++) {
        for (int j = sq_col; j < sq_row + 3; j++) {
            if (i == row && j == col)
                continue;
            if (sudoku[i][j] == num)
                return false;
        }
    }

    return true;
}

bool Sudoku::remove(const int row, const int col) {
    // row, col out of bound or can't remove
    if (out_of_bound(row, col) || origin[row][col])
        return false;

    sudoku[row][col] = 0;
    return true;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

void Sudoku::print_form() const {
    for (int i = 0; i < FORM_SIZE; i++) {
        if (i % 4 == 0) {
            printf("\033[94m");
            cout << "+ + + + + + + + + + + + +" << endl;
            printf("\033[0m");
        }
        for (int j = 0; i % 4 != 0 && j < FORM_SIZE; j++) {
            if (j % 4 == 0) {
                printf("\033[94m");
                cout << "+ ";
                printf("\033[0m");
            } else
                cout << "  ";
        }
        if (i % 4 != 0)
            cout << endl;
    }
}

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

bool Sudoku::cursor_possible(const int new_x, const int new_y) const {
    if ((new_x % 2 == 0 || new_x < 1 || new_x > 24 || (new_x - 1) % 8 == 0) ||
        (new_y < 1 || new_y > 12 || (new_y - 1) % 4 == 0))
        return false;
    return true;
}

bool is_digit(int key) { return (1 <= key - KEY_NUM && key - KEY_NUM <= 9); }

void Sudoku::cursor() {
    int num = sudoku[row][col];

    gotoxy(x, y);
    printf("\033[7m");
    if (num)
        cout << num;
    printf("\033[0m");

    int key = get_key();
    gotoxy(1, 15);
    cout << "                       ";

    if (is_digit(key)) {
        if (!origin[row][col]) {
            if (!value_possible(row, col, key - KEY_NUM)) {
                gotoxy(1, 15);
                printf("\033[32m");
                cout << "Can't insert number!" << endl;
                printf("\033[0m");
            } else
                sudoku[row][col] = key - KEY_NUM;
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
            col++;
        } else if (cursor_possible(x + 4, y)) {
            x += 4;
            col++;
        }
        break;
    case KEY_LEFT:
        if (cursor_possible(x - 2, y)) {
            x -= 2;
            col--;
        } else if (cursor_possible(x - 4, y)) {
            x -= 4;
            col--;
        }
        break;
    case KEY_DELETE:
        remove(row, col);
        break;
    }
}
