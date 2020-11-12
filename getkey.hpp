#ifndef __GETKEY_HPP__
#define __GETKEY_HPP__

#include <iostream>
#include <termios.h>

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define KEY_NUM 48
#define KEY_DELETE 100
<<<<<<< HEAD
=======
//#define ESCAPE_SEQENCE 27 
//OCODOAOB
>>>>>>> Optimize map, cursor printing

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
<<<<<<< HEAD
    ch = getch();

=======
    struct tm *first, second;

    ch = getch();
    const time_t f = time(NULL);
    first = localtime(&f);
>>>>>>> Optimize map, cursor printing
    // up down left right
    if (ch == 27) {
        ch = getch();
        if (ch == 91) {
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

#endif
