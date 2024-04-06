#include "Labirynth.hpp"

LabirynthSolver::LabirynthSolver(Labirynth labirynth): m_labirynth(labirynth)
{
    x = m_labirynth.size();
    y = m_labirynth[0].size();
}

LabirynthSolver::~LabirynthSolver()
{
}
