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
#define KEY_ENTER 10

// get 2 bytes of temp value before real key value
#define KEY_ESCAPE1 27
#define KEY_ESCAPE2 91

extern int getch();
extern int get_key();

#endif
