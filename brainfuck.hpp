#pragma once

#include <vector>

class Brainfuck
{
    unsigned char* pByte = nullptr;
    std::vector<unsigned char> data_mem, instr_mem;

public:

    Brainfuck(const char* filename);
    ~Brainfuck();

    int execute();
    void on_dot(unsigned char data);
    void on_comma(unsigned char* pByte);
};