#include <vector>

//typedef std::vector<std::vector<int>> Labirynth;

class Labirynth
{
    int m_max_x, m_max_y;
    std::vector<int> m_labirynth;
public:
    Labirynth() = default;
    Labirynth(const Labirynth& other);
    Labirynth(int x, int y, const std::vector<int>& labirynth);
    std::vector<int> get1DLabirynth() const;
    //void setXY(int x, int y, int val);
    //int getXY(int x, int y);
    int& accessXY(int x, int y);
    void getDimensions(int& x, int& y) const;
    ~Labirynth() = default;
};

class LabirynthSolver
{
private:
    Labirynth m_labirynth;
    Labirynth work_field;
    int m_x, m_y = 0;
    int x_start, y_start = 0;
    int x_finish, y_finish = 0;
    int current_step = 0;
    bool solvable = true;

    void init_work_field();
    int check_if_near_exit(int x, int y);
    int check_neighbour(int x, int y, int neigh_val);
    int update_work_field();
    void restore_way();
public:
    LabirynthSolver(const Labirynth& labirynth);
    int solve();
    Labirynth getAnswer();
    ~LabirynthSolver();
};
