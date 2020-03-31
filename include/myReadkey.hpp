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
    enum keys
    {
        l,
        s,
        r,
        t,
        i,
        q,
        f5,
        f6,
        up,
        down,
        left,
        right,
        enter,
        other
    };

private:
    enum keys lastkey;

public:
    int ReadKey();
    int SwitchRegime(int regime, int vtime, int vmin, int echo, int sigint);

    int SaveTerm();
    int RestoreTerm();

    keys GetKey() { return lastkey; }
};
