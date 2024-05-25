#include <stdexcept>
#include "Labirynth.hpp"


Labirynth::Labirynth(const Labirynth& other): m_max_x(other.m_max_x), 
                m_max_y(other.m_max_y), m_labirynth(other.m_labirynth)
{
}

Labirynth::Labirynth(int x_dim, int y_dim, const std::vector<int>& labirynth):
        m_max_x(x_dim), m_max_y(y_dim), m_labirynth(labirynth)
{
}

std::vector<int> Labirynth::get1DLabirynth() const{
    return m_labirynth;
}

void Labirynth::setXY(int x, int y, int val){
    m_labirynth[(y-1)*m_max_x + x] = val;
}

int Labirynth::getXY(int x, int y) const{
    return m_labirynth[(y-1)*m_max_x + x];
}

// int& Labirynth::accessXY(int x, int y){return m_labirynth[(y-1)*m_max_x + x];}

void Labirynth::getDimensions(int& x, int& y) const{
    x = m_max_x;
    y = m_max_y;
}

void LabirynthSolver::init_work_field(const Labirynth& m_labirynth){
    int max_x = 0, max_y = 0;
    work_field.getDimensions(max_x, max_y);
    for(int i = 0; i < max_x; i++){
        for(int j = 0; j < max_y; j++){
            if(m_labirynth.getXY(i, j) == 1){
                work_field.setXY(i, j, -1);
            }
            if(m_labirynth.getXY(i, j) == 2){
                work_field.setXY(i, j, 0);
                x_start = i;
                y_start = j;
            }
            if(m_labirynth.getXY(i, j) == 3){
                work_field.setXY(i, j, 0);
                x_finish = i;
                y_finish = j;
            }
        }
    }
}

int LabirynthSolver::check_if_near_exit(int x, int y){
    int max_x = 0, max_y = 0;
    work_field.getDimensions(max_x, max_y);
    if (x - 1 >= 0 && x - 1 == x_finish && y == y_finish){
        work_field.setXY(x-1, y, current_step + 1);
        return 1;
    }
    if (x + 1 < max_x && x + 1 == x_finish && y == y_finish){
        work_field.setXY(x+1,y, current_step + 1);
        return 1;
    }
    if (y - 1 >= 0 && y - 1 == y_finish && x == x_finish){
        work_field.setXY(x,y-1, current_step + 1);
        return 1;
    }
    if (y + 1 < max_y && y + 1 == y_finish && x == x_finish){
        work_field.setXY(x,y+1, current_step + 1);
        return 1;
    }
    return 0;
}


int LabirynthSolver::update_work_field(bool& solvable){
    int max_x = 0, max_y = 0;
    work_field.getDimensions(max_x, max_y);
    solvable = false;

    for (int i = 0; i < max_x; i++){
        for (int j = 0; j < max_y; j++){
            if (work_field.getXY(i, j) == current_step){
                if (check_if_near_exit(i, j) == 1){
                    solvable = true;
                    return 1;
                }
                if ((i - 1 >= 0) && (work_field.getXY(i-1,j) == 0)){
                    work_field.setXY(i-1,j, current_step + 1);
                    solvable = true;
                }
                if ((i + 1 < max_x) && (work_field.getXY(i+1,j) == 0)){
                    work_field.setXY(i+1,j, current_step + 1);
                    solvable = true;
                }
                if ((j - 1 >= 0) && (work_field.getXY(i,j-1) == 0)){
                    work_field.setXY(i,j-1, current_step + 1);
                    solvable = true;
                }
                if ((j + 1 < max_y) && (work_field.getXY(i,j+1) == 0)){
                    work_field.setXY(i,j+1, current_step + 1);
                    solvable = true;
                }
                if (solvable == false){
                    return -1;
                }
            }
        }
    }
    return 0;
}

LabirynthSolver::LabirynthSolver(const Labirynth& labirynth): work_field(labirynth){
    init_work_field(labirynth);
}

LabirynthSolver::~LabirynthSolver(){}

int LabirynthSolver::solve(){
    bool solvable = true;
    while(true){
        int solvable_int = update_work_field(solvable);
        if(solvable_int == 0){
            current_step++;
        }
        // if... by int
    }
    if (solvable == false){
        return 0;
    }
    return 1;
}

Labirynth LabirynthSolver::getAnswer(){
    if (this->solve() == 0){
        throw std::runtime_error("Labirynth is not solvable.");
    }

    int max_x = 0, max_y = 0;
    work_field.getDimensions(max_x, max_y);
    Labirynth answer(work_field);
    int x = x_finish;
    int y = y_finish;
    int aim_val = current_step;

    while (aim_val > 0){
        if (x - 1 >= 0 && work_field.getXY(x-1,y) == aim_val){
            x = x - 1;
            answer.setXY(x-1, y, -1);
            aim_val--;
            continue;
        }
        if (x + 1 < max_x && work_field.getXY(x+1,y) == aim_val){
            x = x + 1;
            answer.setXY(x+1, y, -1);
            aim_val--;
            continue;
        }
        if (y - 1 >= 0 && work_field.getXY(x,y-1) == aim_val){
            y = y - 1;
            answer.setXY(x, y-1, -1);
            aim_val--;
            continue;
        }
        if (y + 1 < max_y && work_field.getXY(x,y+1) == aim_val){
            y = y + 1;
            answer.setXY(x, y+1, -1);
            aim_val--;
            continue;
        }
    }

    return answer;
}





/*
void LabirynthSolver::restore_way(){
    int x = x_finish;
    int y = y_finish;
    int aim_val = current_step;
    while (aim_val > 0){
        if (x - 1 >= 0 && work_field.getXY(x-1,y) == aim_val){
            x = x - 1;
            m_labirynth.setXY(x-1, y, -1);
            aim_val--;
            continue;
        }
        if (x + 1 < m_x && work_field.getXY(x+1,y) == aim_val){
            x = x + 1;
            m_labirynth.setXY(x+1, y, -1);
            aim_val--;
            continue;
        }
        if (y - 1 >= 0 && work_field.getXY(x,y-1) == aim_val){
            y = y - 1;
            m_labirynth.setXY(x, y-1, -1);
            aim_val--;
            continue;
        }
        if (y + 1 < m_y && work_field.getXY(x,y+1) == aim_val){
            y = y + 1;
            m_labirynth.setXY(x, y+1, -1);
            aim_val--;
            continue;
        }
    }
}
*/

// std::vector<std::vector<int>> Labirynth::get2DLabirynth() const{
//     std::vector<std::vector<int>> _2Dlabirynth(m_max_y, std::vector<int>(m_max_x, 0));
//     for(int i = 0; i < m_max_y; i++){
//         for(int j = 0; j < m_max_x; j++){
//             _2Dlabirynth[i][j] = m_labirynth[(i*m_max_x) + j];
//         }
//     }
//     return _2Dlabirynth;
// }

/*
int LabirynthSolver::check_neighbour(int x, int y, int neigh_val){
    if ((x - 1 >= 0) && (work_field.accessXY(x-1,y) == neigh_val)){
        work_field.accessXY(x-1,y) = current_step + 1;
        solvable = true;
    }
    if ((x + 1 < m_x) && (work_field.accessXY(x+1,y) == neigh_val)){
        work_field.accessXY(x+1,y) = current_step + 1;
        solvable = true;
    }
    if ((y - 1 >= 0) && (work_field.accessXY(x,y-1) == neigh_val)){
        work_field.accessXY(x,y-1) = current_step + 1;
        solvable = true;
    }
    if ((y + 1 < m_y) && (work_field.accessXY(x,y+1) == neigh_val)){
        work_field.accessXY(x,y+1) = current_step + 1;
        solvable = true;
    }
    if (solvable == false){
        return -1;
    }
    return 0;
}
*/