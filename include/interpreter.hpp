#pragma once

#define READ 0x10
#define WRITE 0x11

#define LOAD 0x20
#define STORE 0x21

#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33

#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43

enum comands
{
    Read = 0x10,
    Write = 0x11,
    load = 0x20,
    store = 0x21,
    add = 0x30,
    sub = 0x31,
    divide = 0x32,
    mul = 0x33,
    jump = 0x40,
    jneg = 0x41,
    jz = 0x42,
    halt = 0x43
};

class interpreter
{
private:
    const int comands_list[12] = {READ, WRITE, LOAD, STORE, ADD, SUB, DIVIDE, MUL, JUMP, JNEG, JZ, HALT};

public:
    int Encode(int command, int operand, int *value);
    int Decode(int value, int *command, int *operand);
};
