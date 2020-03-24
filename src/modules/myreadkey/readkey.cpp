#include "myReadkey.hpp"

int myReadkey::ReadKey()
{
    struct termios orig_options;
    char buf[16];
    int num_read;

    if (tcgetattr(STDIN_FILENO, &orig_options) != 0)
        return -1;
    if (SwitchRegime(0, 0, 1, 0, 1) != 0)
        return -1;
    num_read = read(STDIN_FILENO, buf, 15);
    if (num_read < 0)
        return -1;
    buf[num_read] = '\0';
    if (strcmp(buf, "l") == 0)
        lastkey = l;
    else if (strcmp(buf, "s") == 0)
        lastkey = s;
    else if (strcmp(buf, "r") == 0)
        lastkey = r;
    else if (strcmp(buf, "t") == 0)
        lastkey = t;
    else if (strcmp(buf, "i") == 0)
        lastkey = i;
    else if (strcmp(buf, "q") == 0)
        lastkey = q;
    else if (strcmp(buf, "\n") == 0)
        lastkey = enter;
    else if (strcmp(buf, "\033[15~") == 0)
        lastkey = f5;
    else if (strcmp(buf, "\033[17~") == 0)
        lastkey = f6;
    else if (strcmp(buf, "\033[A") == 0)
        lastkey = up;
    else if (strcmp(buf, "\033[B") == 0)
        lastkey = down;
    else if (strcmp(buf, "\033[C") == 0)
        lastkey = right;
    else if (strcmp(buf, "\033[D") == 0)
        lastkey = left;
    else
        lastkey = other;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0)
        return -1;

    return 0;
}