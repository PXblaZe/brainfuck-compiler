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
 
    if (instr_mem.size() > 0) data_mem.push_back(0), pByte = static_cast<unsigned char*>(malloc(sizeof(unsigned char)));
    
}

Brainfuck::~Brainfuck()
{
    if (pByte != nullptr) free(pByte);
}

int Brainfuck::execute()
{
    std::vector<unsigned char>::iterator pDM = data_mem.begin();
    std::stack<std::vector<unsigned char>::const_iterator> loops;
    for (std::vector<unsigned char>::const_iterator pIM = instr_mem.cbegin(); pIM != instr_mem.cend(); pIM++)
    {
        if (*pIM == '>'){
            if (pDM+1 == data_mem.end())
            { 
                data_mem.push_back('\0'), pDM = data_mem.end()-1;
                continue;
            }
            pDM++;
        }
        else if (*pIM == '<') {
            if (pDM == data_mem.begin())
            {
                fprintf(stderr, "error: data pointer is at the beginning of the array.\n");
                return -1;
            }
            pDM--;
        }
        else if (*pIM == '+') (*pDM)++;
        else if (*pIM == '-') (*pDM)--;
        else if (*pIM == '.') on_dot(*pDM);
        else if (*pIM == ',') on_comma(pByte), *pDM = *pByte;
        else if (*pIM == '[') {
            if (*pDM) 
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
        }
        else if (*pIM == ']') {
            if (loops.empty())
            {
                fprintf(stderr, "error: UNBALANCED `]` BRACKETS.\n");
                return -1;
            }
            if (*pDM) pIM = loops.top();
            else loops.pop();
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
