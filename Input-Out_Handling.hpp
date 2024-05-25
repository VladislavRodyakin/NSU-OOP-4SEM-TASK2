#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Labirynth.hpp"


class LabirynthIO final{
public:
    Labirynth parse(std::istream& input_stream);
    void writeOutput(std::ostream& output_stream, const Labirynth& labirynth);
};

