#pragma once

#include "bfBuffer.hpp"

class Brainfuck
{
    unsigned char* pByte = nullptr;
    bf_buffer<unsigned char> data_mem;
    std::vector<unsigned char> instr_mem;

public:

    Brainfuck(const char* filename);
    ~Brainfuck();

    int execute();
    void on_dot(unsigned char data);
    void on_comma(unsigned char* pByte);
};