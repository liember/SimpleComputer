#pragma once

class Registers
{
private:
    static int flag;

public:
    static int Init();
    static int Get(int regist, int *value);
    static int Set(int regist, int value);
};
