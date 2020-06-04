#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int16_t standart_line_size = 100;
const int16_t max_mem = 100;
const int16_t read = 0x10, write = 0x11,
              load = 0x20,
              store = 0x21,
              add = 0x30,
              sub = 0x31,
              divide = 0x32,
              mul = 0x33,
              jump = 0x40,
              jneg = 0x41,
              jz = 0x42,
              halt = 0x43,
              AND = 0x52,
              Hal = 0x60,
              SET_VARIABLE = 0xfff;

typedef struct asm_cmd
{
    int16_t addres;
    int16_t comand;
    int16_t operand;
} asm_cmd;

int Encode(int16_t prevaddr, asm_cmd *asm_cmd, int16_t *value)
{
    if (prevaddr >= asm_cmd->addres)
        perror("АДРЕСАЦИЯ ХУЕВАЯ ЕБЛАН"), exit(1);
    if (asm_cmd->comand == SET_VARIABLE)
        if (asm_cmd->operand > 0x3fff || asm_cmd->operand < -0x3fff)
            perror("ЧИСЛО ОГРОМНОЕ"), exit(1);
        else
            *value = asm_cmd->operand;
    else if (asm_cmd->operand < max_mem)
        *value = ((asm_cmd->comand << 7) | asm_cmd->operand) | 0x4000;
    else
        perror("АДДРЕС В ОПЕРАНДЕ БОЛЬШЕ ПАМЯТИ УСТРОЙСТВА"), exit(1);
    return 0;
}

asm_cmd *AddCmdCode(asm_cmd *asm_cmd, const char *cmd)
{
    if (!strcmp(cmd, "READ"))
        asm_cmd->comand = read;
    else if (!strcmp(cmd, "HALT"))
        asm_cmd->comand = halt;
    else if (!strcmp(cmd, "AND"))
        asm_cmd->comand = AND;
    else if (!strcmp(cmd, "HALT"))
        asm_cmd->comand = Hal;
    else if (!strcmp(cmd, "WRITE"))
        asm_cmd->comand = write;
    else if (!strcmp(cmd, "LOAD"))
        asm_cmd->comand = load;
    else if (!strcmp(cmd, "STORE"))
        asm_cmd->comand = store;
    else if (!strcmp(cmd, "ADD"))
        asm_cmd->comand = add;
    else if (!strcmp(cmd, "SUB"))
        asm_cmd->comand = sub;
    else if (!strcmp(cmd, "DIVIDE"))
        asm_cmd->comand = divide;
    else if (!strcmp(cmd, "MUL"))
        asm_cmd->comand = mul;
    else if (!strcmp(cmd, "JUMP"))
        asm_cmd->comand = jump;
    else if (!strcmp(cmd, "JNEG"))
        asm_cmd->comand = jneg;
    else if (!strcmp(cmd, "JZ"))
        asm_cmd->comand = jz;
    else if (!strcmp(cmd, "="))
        asm_cmd->comand = SET_VARIABLE;
    else
        printf("%s НЕТ ТАКОЙ КОМАНДЫ", cmd), exit(1);
    return asm_cmd;
}

asm_cmd ToAsmCmdStructure(char *buf)
{
    asm_cmd cmd;
    char *pch = strtok(buf, " ");
    int word_counter = 0;
    while (pch != NULL)
    {
        ++word_counter;
        if (pch[0] == ';' && word_counter < 4)
            perror("КОМЕНТАРИЙ НЕ К МЕСТУ"), exit(1);
        switch (word_counter)
        {
        case 1:
            cmd.addres = atoi(pch);
            if (cmd.addres > max_mem)
                perror("ADDRES MORE MEMORY"), exit(1);
            break;
        case 2:
            cmd = *AddCmdCode(&cmd, pch);
            break;
        case 3:
            cmd.operand = atoi(pch);
            break;
        case 4:
            if (pch[0] != ';')
                perror(" ЛИШНИЕ БУКВЫ УБЕРИ БЛЯТЬ"), exit(1);
            break;
        }
        pch = strtok(NULL, " ");
    }
    return cmd;
}

int main(int argc, char **argv)
{
    unsigned int comands_counter = 0;
    int prev_addr = -1;
    char buf[standart_line_size];
    int16_t program[max_mem];

    for (size_t i = 0; i < max_mem; i++)
        program[i] = 0;

    FILE *fp = fopen("test", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
            if (fgets(buf, standart_line_size, fp) != NULL)
            {
                int16_t temp_cmd;
                asm_cmd lol = ToAsmCmdStructure(buf);
                if (!Encode(prev_addr, &lol, &temp_cmd))
                    program[lol.addres] = temp_cmd, ++comands_counter;
                else
                    perror("ПРОБЛЕМНЫЙ КОД У ТЕБЯ СУКА"), exit(1);
                prev_addr = lol.addres;
            }
        FILE *out = fopen("test.bin", "wb");
        if (out != NULL)
            fwrite(program, sizeof(int16_t), max_mem, out);
        else
            perror("НЕ МОГУ ФАЙЛ СОЗДАТЬ");
        fclose(out);
    }
    else
        perror("NET TAKOGA FAILA");
    fclose(fp);
}