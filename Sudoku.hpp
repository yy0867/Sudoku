#ifndef __SUDOKU_HPP__
#define __SUDOKU_HPP__

#include "getkey.hpp"
#include <string>

#define N 9
#define MOVE 2
#define FORM_SIZE 13
#define LOW 60
#define MEDIUM 40
#define HIGH 20
#define FRAME_INTERVAR 4
#define ROW_FRAME_INTERVAR 3
#define COLUMN_FRAME_INTERVAR 3
#define X_PADDING 5
#define Y_PADDING 3

enum FLAG { ROW_LINE = 1, COL_LINE, ROW_GROUP, COL_GROUP, NUM };
/*#define COLOR_DEFAULT 0
#define COLOR_BLACK 40
#define COLOR_RED 41     // Z
#define COLOR_GREEN 42   // S
#define COLOR_BROWN 43   // O
#define COLOR_BLUE 44    // J
#define COLOR_MAGENTA 45 // T
#define COLOR_CYAN 46    // I
#define COLOR_GRAY 47    // L*/

using namespace std;

class Sudoku {
  public:
    Sudoku(int level = MEDIUM);

    void set_sudoku(const int row, const int col, const int num) {
        sudoku[row][col] = num;
    }
    void randomize_sudoku();
    int random(const int n = N); // random() -> 1 ~ 9, random(n) -> 1 ~ n
    bool value_possible(const int row, const int col, const int num) const;
    bool remove(const int row, const int col);
    void print_form() const;
    void print() const;
    void printBoard() const;
    void printCursor() const;
    void printColorCursor(int x, int y, int color, const string str) const;
    void printColorCursor(int x, int y, int color, const char str) const;
    void printColorCursor(int x, int y, int color, const char *str) const;
    void printColorCursor(int x, int y, int color, const int str) const;
    char *convertNumberToFullChar(int num) const;

    bool cursor_possible(const int new_x, const int new_y) const;
    bool isCursorPossible(const int new_x, const int new_y) const;
    bool isInside(const int new_x, const int new_y) const;
    void cursor();
    void moveCursor();
    void moveCursor(int key);
    bool isFrameCursor(int cursor) const;
    bool isFrameCursor(const int new_x, const int new_y) const;
    int sudoku[N][N];

    // first & second must be in the same group [1, 2, 3 | 4, 5, 6 | 7, 8, 9]
    // flag -> ROW_LINE / COL_LINE
    void swap_line(int first, int second, int flag);

    // first, second = [0, 1, 2]
    // flag -> ROW_GROUP / COL_GROUP
    void swap_group(int first, int second, int flag);

    // first & second must not be same
    void swap_number(int first, int second);

  private:
    int x, y;
    int row, column;
    bool origin[N][N];
};

extern void gotoxy(int x, int y);
extern bool is_digit(int key);
extern bool out_of_bound(const int row, const int column, const int num = 3);

#endif
