#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Labirynth.hpp"


//rename as io handling
class Parser{
    int m_row_lenght;
    int* m_input_data;
    int* m_output_data;
    Labirynth m_labirynth;
    int charToInt(char ch);

public:
    Parser() = default;
    ~Parser();

    // take everything by const ref
    void parse(std::istream& input_stream);
    Labirynth getLabirynth();

    //void prepareOutputData(Labirynth labirynth);
    void writeOutput(std::ostream& output_stream, const Labirynth& labirynth);
};

