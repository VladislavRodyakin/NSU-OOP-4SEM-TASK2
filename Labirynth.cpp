#include "Labirynth.hpp"

std::vector<int> Labirynth::get1DLabirynth() const{
    return m_labirynth;
}

Labirynth::Labirynth(const Labirynth& other): m_max_x(other.m_max_x), m_max_y(other.m_max_y), m_labirynth(other.m_labirynth)
{
}

Labirynth::Labirynth(int x_dim, int y_dim, const std::vector<int>& labirynth): m_max_x(x_dim), m_max_y(y_dim), m_labirynth(labirynth)
{
}

int& Labirynth::accessXY(int x, int y){
    return m_labirynth[(y-1)*m_max_x + x];
}

void Labirynth::getDimensions(int& x, int& y) const{
    x = m_max_x;
    y = m_max_y;
}

void LabirynthSolver::init_work_field(){
    //Labirynth work_field;
    //int x_start, y_start, x_finish, y_finish;
    for(int i = 0; i < m_x; i++){
        for(int j = 0; j < m_y; j++){
            if(m_labirynth.accessXY(i, j) == 1){
                work_field.accessXY(i, j) = -1;
            }
            if(m_labirynth.accessXY(i, j) == 2){
                work_field.accessXY(i, j) = 0;
                x_start = i;
                y_start = j;
            }
            if(m_labirynth.accessXY(i, j) == 3){
                m_labirynth.accessXY(i, j) = 0;
                x_finish = i;
                y_finish = j;
            }
        }
    }
}

int LabirynthSolver::check_if_near_exit(int x, int y){
    if (x - 1 >= 0 && x - 1 == x_finish && y == y_finish){
        work_field.accessXY(x-1,y) = current_step + 1;
        return 1;
    }
    if (x + 1 < m_x && x + 1 == x_finish && y == y_finish){
        work_field.accessXY(x+1,y) = current_step + 1;
        return 1;
    }
    if (y - 1 >= 0 && y - 1 == y_finish && x == x_finish){
        work_field.accessXY(x,y-1) = current_step + 1;
        return 1;
    }
    if (y + 1 < m_y && y + 1 == y_finish && x == x_finish){
        work_field.accessXY(x,y+1) = current_step + 1;
        return 1;
    }
    return 0;
}

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

int LabirynthSolver::update_work_field(){
    solvable = false;
    for (int i = 0; i < m_x; i++){
        for (int j = 0; j < m_y; j++){
            if (work_field.accessXY(i, j) == current_step){
                if (check_if_near_exit(i, j) == 1){
                    solvable = true;
                    return 1;
                }
                if ((i - 1 >= 0) && (work_field.accessXY(i-1,j) == 0)){
                    work_field.accessXY(i-1,j) = current_step + 1;
                    solvable = true;
                }
                if ((i + 1 < m_x) && (work_field.accessXY(i+1,j) == 0)){
                    work_field.accessXY(i+1,j) = current_step + 1;
                    solvable = true;
                }
                if ((j - 1 >= 0) && (work_field.accessXY(i,j-1) == 0)){
                    work_field.accessXY(i,j-1) = current_step + 1;
                    solvable = true;
                }
                if ((j + 1 < m_y) && (work_field.accessXY(i,j+1) == 0)){
                    work_field.accessXY(i,j+1) = current_step + 1;
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

void LabirynthSolver::restore_way(){
    int x = x_finish;
    int y = y_finish;
    int aim_val = current_step;
    while (aim_val > 0){
        if (x - 1 >= 0 && work_field.accessXY(x-1,y) == aim_val){
            x = x - 1;
            m_labirynth.accessXY(x-1, y) = -1;
            aim_val--;
            continue;
        }
        if (x + 1 < m_x && work_field.accessXY(x+1,y) == aim_val){
            x = x + 1;
            m_labirynth.accessXY(x+1, y) = -1;
            aim_val--;
            continue;
        }
        if (y - 1 >= 0 && work_field.accessXY(x,y-1) == aim_val){
            y = y - 1;
            m_labirynth.accessXY(x, y-1) = -1;
            aim_val--;
            continue;
        }
        if (y + 1 < m_y && work_field.accessXY(x,y+1) == aim_val){
            y = y + 1;
            m_labirynth.accessXY(x, y+1) = -1;
            aim_val--;
            continue;
        }
    }
}

LabirynthSolver::LabirynthSolver(const Labirynth& labirynth): m_labirynth(labirynth), work_field(labirynth)
{
    // m_x = m_labirynth.size();
    // m_y = m_labirynth[0].size();
    labirynth.getDimensions(m_x, m_y);
    
}

// LabirynthSolver::~LabirynthSolver()
// {
// }

int LabirynthSolver::solve(){
    init_work_field();
    
    while(update_work_field() == 0){
        current_step++;
    }
    if (solvable == false){
        return 0;
    }
    return 1;
}

Labirynth LabirynthSolver::getAnswer(){
    return m_labirynth;
}






// std::vector<std::vector<int>> Labirynth::get2DLabirynth() const{
//     std::vector<std::vector<int>> _2Dlabirynth(m_max_y, std::vector<int>(m_max_x, 0));
//     for(int i = 0; i < m_max_y; i++){
//         for(int j = 0; j < m_max_x; j++){
//             _2Dlabirynth[i][j] = m_labirynth[(i*m_max_x) + j];
//         }
//     }
//     return _2Dlabirynth;
// }


// Labirynth::Labirynth(std::vector<int> _1Dlabirynth){
//     m_labirynth = _1Dlabirynth;
//     m_max_x = m_labirynth.size();
//     m_max_y = m_labirynth.size()/m_max_x;
// }
