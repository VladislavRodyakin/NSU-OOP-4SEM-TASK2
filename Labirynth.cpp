#include "Labirynth.hpp"

void LabirynthSolver::init_work_field(){
    //Labirynth work_field;
    //int x_start, y_start, x_finish, y_finish;
    for(int i = 0; i < m_x; i++){
        for(int j = 0; j < m_y; j++){
            if(m_labirynth[i][j] == 1){
                work_field[i][j] = -1;
            }
            if(m_labirynth[i][j] == 2){
                work_field[i][j] = 0;
                x_start = i;
                y_start = j;
            }
            if(m_labirynth[i][j] == 3){
                work_field[i][j] = 0;
                x_finish = i;
                y_finish = j;
            }
        }
    }
}

int LabirynthSolver::check_if_near_exit(int x, int y){
    if (x - 1 >= 0 && x - 1 == x_finish && y == y_finish){
        work_field[x - 1][y] = current_step + 1;
        return 1;
    }
    if (x + 1 < m_x && x + 1 == x_finish && y == y_finish){
        work_field[x + 1][y] = current_step + 1;
        return 1;
    }
    if (y - 1 >= 0 && y - 1 == y_finish && x == x_finish){
        work_field[x][y - 1] = current_step + 1;
        return 1;
    }
    if (y + 1 < m_y && y + 1 == y_finish && x == x_finish){
        work_field[x][y + 1] = current_step + 1;
        return 1;
    }
    return 0;
}

int LabirynthSolver::check_neighbour(int x, int y, int neigh_val){
    if ((x - 1 >= 0) && (work_field[x - 1][y] == neigh_val)){
        work_field[x - 1][y] = current_step + 1;
        solvable = true;
    }
    if ((x + 1 < m_x) && (work_field[x + 1][y] == neigh_val)){
        work_field[x + 1][y] = current_step + 1;
        solvable = true;
    }
    if ((y - 1 >= 0) && (work_field[x][y - 1] == neigh_val)){
        work_field[x][y - 1] = current_step + 1;
        solvable = true;
    }
    if ((y + 1 < m_y) && (work_field[x][y + 1] == neigh_val)){
        work_field[x][y + 1] = current_step + 1;
        solvable = true;
    }
    if (solvable == false){
        return -1;
    }
}

int LabirynthSolver::update_work_field(){
    solvable = false;
    for (int i = 0; i < m_x; i++){
        for (int j = 0; j < m_y; j++){
            if (work_field[i][j] == current_step){
                if (check_if_near_exit(i, j) == 1){
                    solvable = true;
                    return 1;
                }
                if ((i - 1 >= 0) && (work_field[i - 1][j] == 0)){
                    work_field[i - 1][j] = current_step + 1;
                    solvable = true;
                }
                if ((i + 1 < m_x) && (work_field[i + 1][j] == 0)){
                    work_field[i + 1][j] = current_step + 1;
                    solvable = true;
                }
                if ((j - 1 >= 0) && (work_field[i][j - 1] == 0)){
                    work_field[i][j - 1] = current_step + 1;
                    solvable = true;
                }
                if ((j + 1 < m_y) && (work_field[i][j + 1] == 0)){
                    work_field[i][j + 1] = current_step + 1;
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
    
}

LabirynthSolver::LabirynthSolver(const Labirynth& labirynth): m_labirynth(labirynth)
{
    m_x = m_labirynth.size();
    m_y = m_labirynth[0].size();
}

LabirynthSolver::~LabirynthSolver()
{
}

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

