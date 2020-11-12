<<<<<<< HEAD
=======
#include <string>

>>>>>>> Optimize map, cursor printing
#define N 9
#define MOVE 2
#define FORM_SIZE 13
#define LOW 60
#define MEDIUM 40
#define HIGH 20
<<<<<<< HEAD
=======
#define FRAME_INTERVAR 4

#define COLOR_DEFAULT 0
#define COLOR_BLACK 40
#define COLOR_RED 41     // Z
#define COLOR_GREEN 42   // S
#define COLOR_BROWN 43   // O
#define COLOR_BLUE 44    // J
#define COLOR_MAGENTA 45 // T
#define COLOR_CYAN 46    // I
#define COLOR_GRAY 47    // L

using namespace std;
>>>>>>> Optimize map, cursor printing

class Sudoku {
  public:
    Sudoku(int level = MEDIUM);

    void set_sudoku(const int row, const int col, const int num) {
        sudoku[row][col] = num;
    }
    int random(const int n = N); // random() -> 1 ~ 9, random(n) -> 1 ~ n
    bool value_possible(const int row, const int col, const int num) const;
    bool remove(const int row, const int col);
    void print_form() const;
    void print() const;
<<<<<<< HEAD

    bool cursor_possible(const int new_x, const int new_y) const;
    void cursor();

  private:
    int x, y;
    int row, col;
=======
    void printBoard() const;
    void printCursor() const;
    void printColorCursor(int x, int y, int color, const string str) const;
    void printColorCursor(int x, int y, int color, const char str) const;
    void printColorCursor(int x, int y, int color, const int str) const;

    bool cursor_possible(const int new_x, const int new_y) const;
    void cursor();
    void moveCursor();
    void moveCursor(int key);
    bool isFrameCursor(int cursor) const;

  private:
    int x, y;
    int row, column;
>>>>>>> Optimize map, cursor printing
    int sudoku[N][N];
    bool origin[N][N];
};
