#include <stack>
#include <stdio.h>
#include <stdlib.h>

#include "brainfuck.hpp"


Brainfuck::Brainfuck(const char *filename)
{
    FILE* pfile = fopen(filename, "r");
    if (pfile == nullptr) 
    {
        fprintf(stderr, "error: invalid filename {%s}.\n", filename);
        exit(-1);
    }


    for (char c = fgetc(pfile); c != EOF; c = fgetc(pfile)) 
    {
        if (c == '.' || c == ',' || c == '<' || c == '>' || c == '[' || c == ']' || c == '+' || c == '-')
            instr_mem.push_back(c);
    }

    fclose(pfile);
 
    if (instr_mem.size() > 0) pByte = static_cast<unsigned char*>(malloc(sizeof(unsigned char)));
    
}

Brainfuck::~Brainfuck()
{
    if (pByte != nullptr) free(pByte);
}

int Brainfuck::execute()
{
    std::stack<std::vector<unsigned char>::const_iterator> loops;
    for (std::vector<unsigned char>::const_iterator pIM = instr_mem.cbegin(); pIM != instr_mem.cend(); pIM++)
    {
        switch (*pIM)
        {
            case '>':
                data_mem++;
                break;

            case '<':
                data_mem--;
                break;

            case '+':
                (*data_mem)++;
                break;
            
            case '-':
                (*data_mem)--;
                break;

            case '.':
                on_dot(data_mem.getData());
                break;

            case ',':
                on_comma(pByte), data_mem.setData(*pByte);
                break;

            case '[':
            {
                if (*data_mem) 
                {
                    loops.push(pIM);
                    continue;
                }
                size_t bn = 1;
                while ( bn && pIM != instr_mem.cend())
                {
                    pIM++;
                    if (*pIM == ']') bn--;
                    else if (*pIM == '[') bn++;
                }
                if (pIM == instr_mem.cend()) 
                {
                    fprintf(stderr, "error: UNBALANCED `[` BRACKETS.\n");
                    return -1;
                }
            } break;

            case ']':
            {
                if (loops.empty())
                {
                    fprintf(stderr, "error: UNBALANCED `]` BRACKETS.\n");
                    return -1;
                }
                if (*data_mem) pIM = loops.top();
                else loops.pop();
            } break;

        }
    }
    return 0;
}

void Brainfuck::on_dot(unsigned char data)
{
    printf("%c", data);
}

void Brainfuck::on_comma(unsigned char* pByte)
{
    scanf("%c", pByte);
}
