#include "Puzzle.hpp"
#include <iostream>


unsigned int Puzzle::computeWhiteSpacesInRow(size_t rowIndex) const {
    const Numbers& rowNumbers = rowsNumbers[rowIndex];

    unsigned int blackSpaces{ 0 };
    for (unsigned int run : rowNumbers) {
        blackSpaces += run;
    }

    const unsigned int rowLength{ COLUMNS };
    return rowLength - blackSpaces;
}


void Puzzle::print() const {
    for (size_t row{0}; row < ROWS; row++) {
        for (size_t col{0}; col < COLUMNS; col++) {
            char printChar = cells.cells[row][col] ? '\u2588' : ' ';
            std::cout << printChar;
        }

        std::cout << "\n";
    }
}