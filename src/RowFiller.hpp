#pragma once
#include <vector>
#include "Puzzle.hpp"

class RowFiller {
public:
    const Puzzle::Numbers& rowHints;
    const unsigned int rowLength;

    std::vector<unsigned int> combination{};

private:
    const unsigned int whiteSpaces;

    RowFiller(const Puzzle::Numbers& rowHints, unsigned int rowLength);

    void FillRow(Puzzle::Table::TableRow);
};
