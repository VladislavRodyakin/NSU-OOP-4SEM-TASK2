#include "Input-Out_Handling.hpp"
#include <exception>

int Parser::charToInt(char ch)
{
    return static_cast<int>(ch) - static_cast<int>('0');
}


Parser::~Parser()
{
    delete [] m_input_data;
    delete [] m_output_data;
}

void Parser::parse(std::istream& input_stream)
{
    // we have to assume that the first line is always only 1
    // otherwise we will have to somehow get dimensions for the labirynth
    int x_dim = 0;
    int y_dim = 0;
    std::vector<int> labir;
    std::string line;
    std::getline(input_stream, line);
    std::istringstream string_stream(line);
    int field = 1;
    while (field == 1){
        string_stream >> field;
        labir.push_back(field);
    }
    x_dim = labir.size()-1;
    while (string_stream >> field){
        labir.push_back(field);
    }
    y_dim = labir.size()/x_dim;    

    m_labirynth = Labirynth(x_dim, y_dim, labir);
}

Labirynth Parser::getLabirynth()
{
    return m_labirynth;
}

void Parser::writeOutput(std::ostream& output_stream, const Labirynth& labirynth){
    m_labirynth = labirynth;
    int max_x, max_y = 0;
    m_labirynth.getDimensions(max_x, max_y);
    int field = 0;
    for (int i = 0; i < max_x; i++){
        for (int j = 0; j < max_y; j++){
            field = m_labirynth.accessXY(i, j);
            output_stream << (field == -1 ? '*' : field) << " ";
            // because path needs to be marked with *
        }
    }
    output_stream << "\n";

}

