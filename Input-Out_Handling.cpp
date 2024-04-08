#include "Input-Out_Handling.hpp"
#include <exception>

int Parser::charToInt(char ch)
{
    return static_cast<int>(ch) - static_cast<int>('0');
}


Parser::~Parser()
{
}

void Parser::parse(std::string fileName)
{
    FILE* file = fopen(fileName.c_str(), "r");
    
    int ch = fgetc(file);
    // we have to assume that the first line is always only 1
    // otherwise we will have to somehow get dimensions for the labirynth
    while (ch == '1' || ch == ' '){
        if (ch == ' '){
            continue;
        }
        m_labirynth[0].push_back(1);
        m_row_lenght++;
        ch = fgetc(file);
    }
    m_row_lenght--;
    m_labirynth[0].pop_back();
    m_labirynth[1].push_back(1);
    m_labirynth[1].push_back(ch - '0'); // check if it works seeing that we have ' ' separators

    int counter = 0;
    int row = 1;
    while((ch = fgetc(file)) != EOF)
    {
        if (ch == ' '){
            continue;
        }
        if (counter == m_row_lenght){
            row++;
            counter = 0;
        }
        m_labirynth[row].push_back(ch - '0');
        counter++;
    }
    
    if(counter != m_row_lenght){
        throw std::invalid_argument("Got invalid labirynth from file");
    }

    fclose(file);
}

Labirynth Parser::getLabirynth()
{
    return m_labirynth;
}

void Parser::prepareOutputData(Labirynth labirynth)
{
    m_output_data = new int[labirynth.size() * labirynth[0].size()];
    for (int i = 0; i < labirynth.size(); i++)
    {
        for (int j = 0; j < labirynth[0].size(); j++)
        {
            m_output_data[i * labirynth[0].size() + j] = labirynth[i][j];
        }
    }
}

void Parser::writeOutput(std::string fileName)
{
    FILE* file = fopen(fileName.c_str(), "w");
    for (int i = 0; i < m_labirynth.size(); i++){
        for (int j = 0; j < m_labirynth[0].size(); j++){
            fprintf(file, "%d ", m_output_data[i * m_labirynth[0].size() + j]);
        }
    }
    fprintf(file, "\n");
}
