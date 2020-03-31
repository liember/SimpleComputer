#include "myReadkey.hpp"

int myReadkey::SaveTerm()
{
    struct termios options;
    FILE *save;

    if (tcgetattr(STDIN_FILENO, &options) != 0)
        return -1;
    if ((save = fopen("termsettings", "wb")) == NULL)
        return -1;
    fwrite(&options, sizeof(options), 1, save);
    fclose(save);

    return 0;
}
int myReadkey::SwitchRegime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios options;

    if (tcgetattr(STDIN_FILENO, &options) != 0)
        return -1;
    if (regime == 1)
        options.c_lflag |= ICANON;
    else if (regime == 0)
        options.c_lflag &= ~ICANON;
    else
        return -1;
    if (regime == 0)
    {
        options.c_cc[VTIME] = vtime;
        options.c_cc[VMIN] = vmin;
        if (echo == 1)
            options.c_lflag |= ECHO;
        else if (echo == 0)
            options.c_lflag &= ~ECHO;
        else
            return -1;
        if (sigint == 1)
            options.c_lflag |= ISIG;
        else if (sigint == 0)
            options.c_lflag &= ~ISIG;
        else
            return -1;
    }
    if (tcsetattr(STDIN_FILENO, TCSANOW, &options) != 0)
        return -1;

    return 0;
}
int myReadkey::RestoreTerm()
{
    struct termios options;
    FILE *save;

    if ((save = fopen("termsettings", "rb")) == NULL)
        return -1;
    if (fread(&options, sizeof(options), 1, save) > 0)
    {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &options) != 0)
            return -1;
        else
            return -1;
    }

    return 0;
}
int myReadkey::ReadKey()
{
    struct termios orig_options;
    int num_read;

    if (tcgetattr(STDIN_FILENO, &orig_options) != 0)
        return -1;
    if (SwitchRegime(0, 0, 1, 0, 1) != 0)
        return -1;
    num_read = read(STDIN_FILENO, lastkey, 15);
    if (num_read < 0)
        return -1;
    lastkey[num_read] = '\0';
    if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0)
        return -1;

    return 0;
}