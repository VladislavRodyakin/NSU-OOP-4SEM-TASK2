#include <iostream>
#include <sstream>
#include "Labirynth.hpp"
#include "Input-Out_Handling.hpp"

int main(){
    try{
    LabirynthIO labirynth_io;
    std::istringstream inp{
                "1 1 1 1 1 1 1 1 1 1 "
                "1 2 0 1 0 0 0 0 0 1 "
                "1 0 0 1 0 0 1 0 0 1 "
                "1 0 0 1 0 0 1 0 0 3 "
                "1 0 0 0 0 0 1 0 0 1 "
                "1 0 0 0 0 0 0 0 0 1 "
                "1 1 1 1 1 1 1 1 1 1 \n"};
    Labirynth labirynth = labirynth_io.parse(inp);

    try{
        int x = 0, y = 0;
        std::ostringstream out;
        labirynth.getDimensions(x, y);
        std::cout<<"x "<< x <<" y "<<y<<std::endl;
        if (x != 10 || y != 7){
            throw std::runtime_error("Wrong labirynth dimensions");
        }


        labirynth_io.writeOutput(out, labirynth);
        std::cout<<"inp "<<std::endl<<inp.str()<<std::endl;
        std::cout<<"out "<<std::endl<<out.str();//<<std::endl;
        

        std::cout <<"get1DLabirynth "<<std::endl;
        for (int i = 0; i < x*y; i++){
            std::cout<<labirynth.get1DLabirynth()[i]<<" ";
        }
        std::cout<<std::endl;

        std::cout <<"getXY "<<std::endl;
        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                std::cout<<labirynth.getXY(j,i)<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        
        std::cout <<"outERR "<<std::endl;
        if (out.str().compare(inp.str())!=0){
            std::cout<<out.str()<<std::endl;
            throw std::runtime_error("Wrong labirynth output");
        }
    }
    catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
        return 0;
    }



    std::cout<<"Hello, I work!"<<std::endl;
    LabirynthSolver solver(labirynth);

    std::cout<<"Solving..."<<std::endl;

    Labirynth solved = solver.getAnswer();

    std::cout<<"Solved!"<<std::endl;

    int x = 0, y = 0;
    solved.getDimensions(x, y);
    labirynth_io.writeOutput(std::cout, solved);
    int field = 0;
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++){
            field = solved.getXY(j, i);
            if (field == -1){
                std::cout<<" * ";
            }
            else if (field < 10){
                std::cout<<" "<<field<<" ";
            }
            else{
                std::cout<<field<<" ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    }
    catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}
