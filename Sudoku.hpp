#define N 9
#define MOVE 2
#define FORM_SIZE 13
#define LOW 60
#define MEDIUM 40
#define HIGH 20

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

    bool cursor_possible(const int new_x, const int new_y) const;
    void cursor();

  private:
    int x, y;
    int row, col;
    int sudoku[N][N];
    bool origin[N][N];
};
