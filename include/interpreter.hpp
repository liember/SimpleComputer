#pragma once

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33
#define JUMP 40
#define JNEG 41
#define JZ 42
#define HALT 43

class interpreter
{
private:
    const int comands_list[12] = {READ, WRITE, LOAD, STORE, ADD, SUB, DIVIDE, MUL, JUMP, JNEG, JZ, HALT};

public:
    int Encode(int command, int operand, int *value);
    int Decode(int value, int *command, int *operand);
};
