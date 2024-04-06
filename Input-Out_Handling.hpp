#include <iostream>
#include "Labirynth.hpp"

class Parser{
int row_lenght;
int* m_input_data;
int* m_output_data;
Labirynth m_labirynth;
public:
    Parser() = default;
    ~Parser();

    void parse(std::string fileName);
    Labirynth getLabirynth();

    void prepareOutputData(Labirynth labirynth);
    void writeOutput(std::string fileName);
};

