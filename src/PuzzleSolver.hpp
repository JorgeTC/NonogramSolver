#pragma once

#include "Puzzle.hpp"
#include "SumCombinations.hpp"
#include <array>

class PuzzleSolver {
public:
    PuzzleSolver(Puzzle* puzzle);

    void Solve();

private:
    Puzzle* const puzzle{ nullptr };
    std::array<SumCombinations, Puzzle::ROWS> rowsCombinations;

    bool solve(unsigned int iRow);
};
