#include <stack>
#include <string>
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

    char lc = -1;
    size_t ct = 0;

    for (char c = fgetc(pfile); c != EOF; c = fgetc(pfile)) 
    {
        if (!(c == '.' || c == ',' || c == '<' || c == '>' || c == '[' || c == ']' || c == '+' || c == '-')) continue;
        
        if (c == '<' || c == '>' || c == '+' || c == '-')
        {
            if (!ct) lc = c;
            if (lc == c) ct++;
            else {
                if (ct > 1) {
                    std::string ns = std::to_string(ct);
                    instr_mem.insert(instr_mem.end(), ns.cbegin(), ns.cend());
                }
                instr_mem.push_back(lc);
                ct = 1, lc = c;
            }
        }
        else {
            if (!ct) instr_mem.push_back(c);
            else if (lc != c)
            {
                if (ct > 1) {
                    std::string ns = std::to_string(ct);
                    instr_mem.insert(instr_mem.cend(), ns.cbegin(), ns.cend());
                }
                instr_mem.insert(instr_mem.cend(), {(unsigned char)lc, (unsigned char)c});
                ct = 0, lc = -1;
            }
        }

    }

    fclose(pfile); 
    if (instr_mem.size() > 0) pByte = static_cast<unsigned char*>(malloc(sizeof(unsigned char)));
}

Brainfuck::~Brainfuck()
{
    if (pByte != nullptr) free(pByte);
}

int Brainfuck::execute(BF_on_dot_func on_dot, BF_on_comma_func on_comma)
{
    std::stack<std::vector<unsigned char>::const_iterator> loops;
    for (std::vector<unsigned char>::const_iterator pIM = instr_mem.cbegin(); pIM != instr_mem.cend(); pIM++)
    {
        switch (*pIM)
        {
            case '>':
                if (pIM > instr_mem.cbegin() && isdigit(*(pIM-1))) {
                    std::vector<unsigned char>::const_iterator fdc = pIM -1, ldc = fdc;
                    while (fdc > instr_mem.cbegin() && isdigit(*(--fdc)));
                    if (!isdigit(*fdc)) fdc++;
                    size_t n = stosz(fdc.base(), ldc.base()); // static_cast<size_t>(std::strtoll((char*)fdc.base(), nullptr, 10));
                    data_mem += n;
                    break;
                }
                data_mem++;
                break;

            case '<':
                if (pIM > instr_mem.cbegin() && isdigit(*(pIM-1))) {
                    std::vector<unsigned char>::const_iterator fdc = pIM -1, ldc = fdc;
                    while (fdc > instr_mem.cbegin() && isdigit(*(--fdc)));
                    if (!isdigit(*fdc)) fdc++;
                    size_t n = stosz(fdc.base(), ldc.base());// static_cast<size_t>(std::strtoll((char*)fdc.base(), nullptr, 10));
                    data_mem -= n;
                    break;
                }
                data_mem--;
                break;

            case '+':
                if (pIM > instr_mem.cbegin() && isdigit(*(pIM-1))) {
                    std::vector<unsigned char>::const_iterator fdc = pIM -1, ldc = fdc;
                    while (fdc > instr_mem.cbegin() && isdigit(*(--fdc)));
                    if (!isdigit(*fdc)) fdc++;
                    size_t n = stosz(fdc.base(), ldc.base());// static_cast<size_t>(std::strtoll((char*)fdc.base(), nullptr, 10));
                    (*data_mem) += n;
                    break;
                }
                (*data_mem)++;
                break;
            
            case '-':
                if (pIM > instr_mem.cbegin() && isdigit(*(pIM-1))) {
                    std::vector<unsigned char>::const_iterator fdc = pIM -1, ldc = fdc;
                    while (fdc > instr_mem.cbegin() && isdigit(*(--fdc)));
                    if (!isdigit(*fdc)) fdc++;
                    size_t n = stosz(fdc.base(), ldc.base());// static_cast<size_t>(std::strtoll((char*)fdc.base(), nullptr, 10));
                    (*data_mem) -= n;
                    break;
                }
                (*data_mem)--;
                break;

            case '.':
                if (on_dot == nullptr) _on_dot(data_mem.getData());
                else on_dot(data_mem.getData());
                break;

            case ',':
                if (on_comma == nullptr) _on_comma(pByte);
                else on_comma(pByte);
                data_mem.setData(*pByte);
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
    if (!loops.empty()) {
        fprintf(stderr, "error: UNBALANCED `[` BRACKETS.\n");
        return -1;
    }
    return 0;
}

inline size_t Brainfuck::stosz(const unsigned char* first, const unsigned char* last) const
{
    size_t res = *first - '0';
    while (first++ != last) res = res*10 + *first - '0';
    return res;
}

void Brainfuck::_on_dot(unsigned char data)
{
    printf("%c", data);
}

void Brainfuck::_on_comma(unsigned char* pByte)
{
    scanf("%c", pByte);
}
