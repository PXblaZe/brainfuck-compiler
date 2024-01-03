#pragma once

#include <vector>
#include "bfBuffer.hpp"

class Brainfuck
{
    unsigned char* pByte = nullptr;
    bf_buffer<unsigned char> data_mem;
    std::vector<unsigned char> instr_mem;

    void _on_dot(unsigned char data);
    void _on_comma(unsigned char* pByte);
    inline size_t stosz(const unsigned char* first, const unsigned char* last) const;

public:

    Brainfuck(const char* filename);
    ~Brainfuck();

    typedef void (*BF_on_dot_func)(unsigned char data);
    typedef void (*BF_on_comma_func)(unsigned char* pByte);

    int execute(BF_on_dot_func on_dot = nullptr, BF_on_comma_func on_comma = nullptr);

};