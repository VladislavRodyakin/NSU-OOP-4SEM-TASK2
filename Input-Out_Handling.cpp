#include "Input-Out_Handling.hpp"

Parser::~Parser()
{
}

void Parser::parse(std::string fileName)
{
    FILE* file = fopen(fileName.c_str(), "r");
    
    int ch;
    while((ch = fgetc(file)) != EOF)
    {
        if (ch == '1')
        {
            m_labirynth.push_back(std::vector<int>());
        }
        else if (ch == '\n')
        {
            continue;
        }
        else
        {
            m_labirynth.back().push_back(ch - '0');
        }
    }
    
    fclose(file);}
