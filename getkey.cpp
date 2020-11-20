#include "getkey.hpp"

int getch() {
    int ch;
    struct termios buf, save;

    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);

    return ch;
}

int get_key() {
    int ch;
    ch = getch();

    // up down left right
    if (ch == KEY_ESCAPE1) {
        ch = getch();
        if (ch == KEY_ESCAPE2) {
            ch = getch();
            switch (ch) {
            case 65:
                return KEY_UP;
                break;
            case 66:
                return KEY_DOWN;
                break;
            case 67:
                return KEY_RIGHT;
                break;
            case 68:
                return KEY_LEFT;
                break;
            default:
                break;
            }
        }
    }

    // delete
    if (ch == 100)
        return KEY_DELETE;

    return ch;
}
