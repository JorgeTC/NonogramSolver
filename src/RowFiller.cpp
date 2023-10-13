#include "RowFiller.hpp"
#include "Puzzle.hpp"

static unsigned int computeWhiteSpaces(const Puzzle::Numbers& rowHints, unsigned int rowLength) {
    unsigned int blackSpaces{ 0 };
    for (unsigned int run : rowHints) {
        blackSpaces += run;
    }

    return rowLength - blackSpaces;
}

RowFiller::RowFiller(const Puzzle::Numbers& rowHints, unsigned int rowLength) :
    rowHints(rowHints),
    rowLength(rowLength),
    whiteSpaces(computeWhiteSpaces(rowHints, rowLength))
{
    combination.resize(rowHints.size());
}

void RowFiller::FillRow(Puzzle::Table::TableRow tableRow)
{
    size_t rowIndex{ 0 };
    for (size_t i = 0; i < combination.size(); i++) {
        for (unsigned int whiteIndex = 0; whiteIndex < combination[i]; whiteIndex++) {
            tableRow[rowIndex++] = false;
        }
        for (unsigned int blackIndex = 0; blackIndex < rowHints[i]; blackIndex++) {
            tableRow[rowIndex++] = true;
        }
    }
}
;
