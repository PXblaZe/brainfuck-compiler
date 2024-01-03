#pragma GCC target ("avx,avx2,fma")

#include <stdio.h>
#include "brainfuck.hpp"


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "%s: fatal error: no input file.\ncompilation terminated.\n", argv[0]);
        return -1;
    }
    Brainfuck program(argv[1]);
    return program.execute();
}
