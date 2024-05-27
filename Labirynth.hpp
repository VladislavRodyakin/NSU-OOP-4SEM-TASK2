#pragma once
#include <vector>
#include <iostream>

//typedef std::vector<std::vector<int>> Labirynth;

class Labirynth final
{
    int m_max_x, m_max_y = 0;
    std::vector<int> m_labirynth = {};
public:
    Labirynth() = default;
    Labirynth(const Labirynth& other);
    Labirynth(int x, int y, const std::vector<int>& labirynth);
    std::vector<int> get1DLabirynth() const;
    void setXY(int x, int y, int val);
    int getXY(int x, int y) const;
    //int& accessXY(int x, int y);
    void getDimensions(int& x, int& y) const;
    ~Labirynth() = default;
};

class LabirynthSolver final
{
private:
    Labirynth m_labirynth;
    // int m_x, m_y = 0;
    // bool solvable = true;
    Labirynth work_field;
    int x_start, y_start = 0;
    int x_finish, y_finish = 0;
    int current_step = 1;

    void init_work_field(const Labirynth& m_labirynth);
    int check_if_near_exit(int x, int y);
    int update_work_field();
    int solve();
    // int check_neighbour(int x, int y, int neigh_val);
    // void restore_way();
public:
    LabirynthSolver(const Labirynth& labirynth);
    Labirynth getAnswer();
    ~LabirynthSolver();
};
