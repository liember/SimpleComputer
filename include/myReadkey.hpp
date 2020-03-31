#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

class myReadkey
{
public:
private:
    char lastkey[16];

public:
    int ReadKey();
    int SwitchRegime(int regime, int vtime, int vmin, int echo, int sigint);

    int SaveTerm();
    int RestoreTerm();

    char *GetKey() { return lastkey; }
};