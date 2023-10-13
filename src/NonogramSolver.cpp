#include <iostream>
#include "Puzzle.hpp"
#include "PuzzleSolver.hpp"

int main()
{
    Puzzle myPuzzle;
    myPuzzle.rowsNumbers = Puzzle::RowsNumbers{
        std::vector<unsigned int>{8,7,5,7},
        std::vector<unsigned int>{5,4,3,3},
        std::vector<unsigned int>{3,3,2,3},
        std::vector<unsigned int>{4,3,2,2},
        std::vector<unsigned int>{3,3,2,2},

        std::vector<unsigned int>{3,4,2,2},
        std::vector<unsigned int>{4,5,2},
        std::vector<unsigned int>{3,5,1},
        std::vector<unsigned int>{4,3,2},
        std::vector<unsigned int>{3,4,2},

        std::vector<unsigned int>{4,4,2},
        std::vector<unsigned int>{3,6,2},
        std::vector<unsigned int>{3,2,3,1},
        std::vector<unsigned int>{4,3,4,2},
        std::vector<unsigned int>{3,2,3,2},

        std::vector<unsigned int>{6,5},
        std::vector<unsigned int>{4,5},
        std::vector<unsigned int>{3,3},
        std::vector<unsigned int>{3,3},
        std::vector<unsigned int>{1,1}
    };
    myPuzzle.columnsNumbers = Puzzle::ColumnsNumbers{
    std::vector<unsigned int>{1},
    std::vector<unsigned int>{1},
    std::vector<unsigned int>{2},
    std::vector<unsigned int>{4},
    std::vector<unsigned int>{7},

    std::vector<unsigned int>{9},
    std::vector<unsigned int>{2,8},
    std::vector<unsigned int>{1,8},
    std::vector<unsigned int>{8},
    std::vector<unsigned int>{1,9},
    
    std::vector<unsigned int>{2,7},
    std::vector<unsigned int>{3,4},
    std::vector<unsigned int>{6,4},
    std::vector<unsigned int>{8,5},
    std::vector<unsigned int>{1,11},
    
    std::vector<unsigned int>{1,7},
    std::vector<unsigned int>{8},
    std::vector<unsigned int>{1,4,8},
    std::vector<unsigned int>{6,8},
    std::vector<unsigned int>{4,7},
    
    std::vector<unsigned int>{2,4},
    std::vector<unsigned int>{1,4},
    std::vector<unsigned int>{5},
    std::vector<unsigned int>{1,4},
    std::vector<unsigned int>{1,5},
    
    std::vector<unsigned int>{7},
    std::vector<unsigned int>{5},
    std::vector<unsigned int>{3},
    std::vector<unsigned int>{1},
    std::vector<unsigned int>{1}
    };

    PuzzleSolver solver(&myPuzzle);
    solver.Solve();
    myPuzzle.print();

    std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
