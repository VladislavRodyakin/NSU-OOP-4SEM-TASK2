#include <vector>

typedef std::vector<std::vector<int>> Labirynth;
class LabirynthSolver
{
private:
    Labirynth m_labirynth;
    int x, y;
public:
    LabirynthSolver(Labirynth labirynth);
    int solve();
    Labirynth getAnswer();
    ~LabirynthSolver();
};
