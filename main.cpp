#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2,fma")

#include <stdio.h>
#include <ios>
#include "brainfuck.hpp"

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    if (argc == 1)
    {
        fprintf(stderr, "%s: fatal error: no input file.\ncompilation terminated.\n", argv[0]);
        return -1;
    }
    Brainfuck program(argv[1]);
    return program.execute();
}