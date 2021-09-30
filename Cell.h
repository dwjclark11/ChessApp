#pragma once

class Cell
{
private:
    int rowNumber;
    int colNumber;
    bool currentlyOccupied;
    bool legalNextMove;

public:
    Cell()
    {
        rowNumber = 0;
        colNumber = 0;
        currentlyOccupied = false;
        legalNextMove = false;
    }
    Cell(int row, int col)
    {
        rowNumber = row;
        colNumber = col;
        currentlyOccupied = false;
        legalNextMove = false;
    }

    inline int GetRowNumber() { return rowNumber; }
    inline int GetColNumber() { return colNumber; }
    inline void SetRowNumber(int row) { rowNumber = row; }
    inline void SetColNumber(int col) { colNumber = col; }
    inline bool& IsCellOccupied() { return currentlyOccupied; }
    inline bool& LegalMove() { return legalNextMove; }
};
