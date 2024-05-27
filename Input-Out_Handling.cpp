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
    x_dim = labir.size()-2; //-2 bc it cycles one more time before field != 1
    while (string_stream >> field){
        labir.push_back(field);
    }
    y_dim = labir.size()/x_dim;

    /*
    std::cout<<" x_dim = "<<x_dim<<" y_dim = "<<y_dim<< " labir.size() "<<labir.size()<<std::endl;
    for (int i = 0; i < labir.size(); i++){
        std::cout<<labir[i]<<" ";
    }
    std::cout<<std::endl;
    */
    
    if (labir.size() != x_dim * y_dim){
        throw std::invalid_argument("Invalid labirynth, inconsistent dimensions");
    }
    
    return Labirynth(x_dim, y_dim, labir);
}


void LabirynthIO::writeOutput(std::ostream& output_stream, const Labirynth& labirynth){
    int max_x, max_y = 0;
    labirynth.getDimensions(max_x, max_y);
    int field = 0;
    for (int i = 0; i < max_y; i++){
        for (int j = 0; j < max_x; j++){
            field = labirynth.getXY(j, i);
            //std::cout<<" field = "<<field<<std::endl;
            if (field == -1){
                output_stream<<"* ";
            }
            else {
                output_stream<<field<<" ";
            }
            // output_stream << (field == -1 ? '*' : field) << " "; // in this context '*' casts to int as 42
            // because path needs to be marked with *
        }
    }
    output_stream << "\n"; // is it good practice?

}




// int LabirynthIO::charToInt(char ch){return static_cast<int>(ch) - static_cast<int>('0');}
// Labirynth LabirynthIO::getLabirynth(){return m_labirynth;}
