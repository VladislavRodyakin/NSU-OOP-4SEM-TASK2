#include "Input-Out_Handling.hpp"
#include <exception>


Labirynth LabirynthIO::parse(std::istream& input_stream)
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

    if (labir.size() != x_dim * y_dim){
        throw std::invalid_argument("Invalid labirynth, inconsistent dimensions");
    }
    
    return Labirynth(x_dim, y_dim, labir);
}


void LabirynthIO::writeOutput(std::ostream& output_stream, const Labirynth& labirynth){
    int max_x, max_y = 0;
    labirynth.getDimensions(max_x, max_y);
    int field = 0;
    for (int i = 0; i < max_x; i++){
        for (int j = 0; j < max_y; j++){
            field = labirynth.getXY(i, j);
            output_stream << (field == -1 ? '*' : field) << " ";
            // because path needs to be marked with *
        }
    }
    output_stream << "\n";

}




// int LabirynthIO::charToInt(char ch){return static_cast<int>(ch) - static_cast<int>('0');}
// Labirynth LabirynthIO::getLabirynth(){return m_labirynth;}
