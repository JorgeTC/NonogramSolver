#include <utility>
#include "PuzzleSolver.hpp"
#include "SumCombinations.hpp"


static SumCombinations getCombinationsForRow(const Puzzle& puzzle, unsigned int iRow) {
    const Puzzle::Numbers& rowsNumbers = puzzle.rowsNumbers[iRow];

    // Substract the middle spaces, because they cannot be 0
    const unsigned int whiteSpaces{ puzzle.computeWhiteSpacesInRow(iRow) - (rowsNumbers.size() - 1)};

    return SumCombinations(whiteSpaces, rowsNumbers.size() + 1);
}


static void fillLine(Puzzle& puzzle, const SumCombinations::Combination& rowCombination, unsigned int iRow) {
    const Puzzle::Numbers& rowsNumbers = puzzle.rowsNumbers[iRow];
    Puzzle::Table::TableRow& fillingRow{ puzzle.cells.cells[iRow] };

    auto isMiddleSpace = [rowCombination](size_t i) {
        return (i > 0) && (i < rowCombination.size() - 1);
    };

    size_t rowIndex{ 0 };
    for (size_t i = 0; i < rowCombination.size(); i++) {
        const unsigned int whiteRunLength = rowCombination[i] + (isMiddleSpace(i) ? 1 : 0);
        for (unsigned int whiteIndex = 0; whiteIndex < whiteRunLength; whiteIndex++) {
            fillingRow[rowIndex++] = false;
        }
        if (i >= rowsNumbers.size())
            break;
        for (unsigned int blackIndex = 0; blackIndex < rowsNumbers[i]; blackIndex++) {
            fillingRow[rowIndex++] = true;
        }
    }
}

static std::vector<unsigned int> getColumnAsBlocks(const Puzzle& puzzle, unsigned int iMaxRow, unsigned int iCol) {

    std::vector<unsigned int> blocks;
    bool inBlock{ false };
    for (size_t iRow{ 0 }; iRow <= iMaxRow; iRow++) {
        const bool isBlackCell{puzzle.cells.cells[iRow][iCol] == true};
        if (isBlackCell) {
            if (inBlock) {
                blocks.back() += 1;
            }
            else {
                inBlock = true;
                blocks.push_back(1);
            }

        }
        else {
            if (inBlock) {
                inBlock = false;
            }
        }
    }

    return blocks;
}

static bool isColumnWrong(const Puzzle& puzzle, unsigned int iRow, unsigned int iCol) {
    const std::vector<unsigned int> blocks{getColumnAsBlocks(puzzle, iRow, iCol)};
    const Puzzle::Numbers& columnNumbers{ puzzle.columnsNumbers[iCol] };

    // If there are too many blocks, there is something wrong
    if (blocks.size() > columnNumbers.size())
        return true;

    // Check all the full existing blocks have the expected size
    bool isLastCellWhite{ puzzle.cells.cells[iRow][iCol] == false };
    for (size_t iBlock{ 0 }; iBlock < blocks.size(); iBlock++) {

        if (iBlock + 1 < blocks.size() ||
            isLastCellWhite) {
            if (blocks[iBlock] != columnNumbers[iBlock])
                return true;
        }
        else {
            // And the last block, not finished yet, is not too big
            if (blocks[iBlock] > columnNumbers[iBlock])
                return true;
        }
    }

    // Check the remaining blocks fit in the remaining rows
    const unsigned int remainingCells{ Puzzle::ROWS - (iRow + 1) };
    unsigned int neededCells{ 0 };
    if (!isLastCellWhite) {
        const unsigned int currentNumberIndex{ blocks.size() - 1 };

        // Add the cells needed to finish the current block
        neededCells += columnNumbers[currentNumberIndex] - blocks.back();

        // Add the needed white space to begin a new block
        if (currentNumberIndex + 1 < columnNumbers.size())
            neededCells += 1;
    }
    if (neededCells > remainingCells) {
        return true;
    }

    for (size_t iRemainingBlock{ blocks.size() }; iRemainingBlock < columnNumbers.size(); iRemainingBlock++) {
        neededCells += columnNumbers[iRemainingBlock];
        if (neededCells > remainingCells) {
            return true;
        }

        // Add the white space needed for the next block
        neededCells += 1;
    }

    // The column seems to be ok
    return false;
}

static bool isPuzzleWrong(const Puzzle& puzzle, unsigned int iRow) {
    for (size_t iCol{ 0 }; iCol < puzzle.COLUMNS; iCol++) {
        if (isColumnWrong(puzzle, iRow, iCol))
            return true;
    }
    return false;
}

static void clearRow(Puzzle& puzzle, unsigned int iRow) {
    Puzzle::Table::TableRow& targetRow{ puzzle.cells.cells[iRow] };

    for (bool& cell : targetRow)
        cell = false;
}

bool PuzzleSolver::solve(unsigned int iRow) {

    // Iterate the different ways of filling the current line
    const SumCombinations& rowCombinations{ rowsCombinations[iRow]};
    for (const SumCombinations::Combination& rowCombination : rowCombinations.combinations) {
        // Actually fill the line
        fillLine(*puzzle, rowCombination, iRow);

        // If the current state makes the current table incoherent, stop filling the table
        if (isPuzzleWrong(*puzzle, iRow))
            continue;

        // The current state is valid
        // If the current row is the last one, I have solved the puzzle
        if (iRow + 1 == Puzzle::ROWS)
            return true;

        // Fill the next row, if I get a valid filling for the following rows, I have solved the puzzle
        if (solve(iRow + 1))
            return true;
    }

    clearRow(*puzzle, iRow);

    // I iterated all the combinations for the current row, there is something wrong
    return false;
}

void PuzzleSolver::Solve() {
    solve(0);
}

template <std::size_t ... Is>
static std::array<SumCombinations, sizeof...(Is)> make_array_impl(const Puzzle& puzzle, std::index_sequence<Is...>)
{
    return { {getCombinationsForRow(puzzle, Is)...} };
}

static std::array<SumCombinations, Puzzle::ROWS> loadRowsCombinations(const Puzzle& puzzle) {
    return make_array_impl(puzzle, std::make_index_sequence<Puzzle::ROWS>());
}

PuzzleSolver::PuzzleSolver(Puzzle* puzzle) :
    puzzle(puzzle),
    rowsCombinations(loadRowsCombinations(*puzzle))
{}
