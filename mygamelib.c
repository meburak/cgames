#include <stdio.h>
#include "mygamelib.h"

void tc_move_cursor(int X, int Y) {
    printf("\033[%d;%dH", Y, X);
}
