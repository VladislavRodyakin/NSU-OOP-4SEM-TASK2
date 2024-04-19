#include <vector>

// redo this as class Labirynth w/ get/set methods 
// to avoid complications w/ single vector format of storing the labirynth
typedef std::vector<std::vector<int>> Labirynth;
class LabirynthSolver
{
private:
    Labirynth m_labirynth;
    Labirynth work_field;
    int m_x, m_y;
    int x_start, y_start;
    int x_finish, y_finish;
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
