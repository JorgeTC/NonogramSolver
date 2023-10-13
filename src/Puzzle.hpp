#pragma once

#include <vector>
#include <array>

class Puzzle {
public:
    constexpr static unsigned int ROWS = 20;
    constexpr static unsigned int COLUMNS = 30;

    using Numbers = std::vector<unsigned int>;
    using RowsNumbers = std::array<Numbers, ROWS>;
    RowsNumbers rowsNumbers{};
    using ColumnsNumbers = std::array<Numbers, COLUMNS>;
    ColumnsNumbers columnsNumbers{};

    class Table {
    public:
        using TableRow = std::array<bool, Puzzle::COLUMNS>;
        using TableCells = std::array<TableRow, Puzzle::ROWS>;

        TableCells cells{};
    };

private:
    static Table emptyTable()
    {
        Table ansTable{};

        for (auto&& tableRow : ansTable.cells) {
            for (auto&& cell : tableRow) {
                cell = false;
            }
        }

        return ansTable;
    }

public:
    Table cells{emptyTable()};

    constexpr Puzzle() = default;
    void print() const;
    unsigned int computeWhiteSpacesInRow(size_t rowIndex) const;
};
