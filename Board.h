#pragma once

#include "Cell.h"

class Board
{
private:
    int boardSize;

public:
    enum class ChessPieces
    {
        KNIGHT = 0,
        KING,
        ROOKE,
        BISHOP,
        PAWN,
        QUEEN
    };

    Cell boardGrid[8][8];

    Board(int board_size)
    {
        //
        boardSize = board_size;

        // Set the numbers to the cells
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                boardGrid[i][j].SetRowNumber(i);
                boardGrid[i][j].SetColNumber(j);
            }
        }
    }
    ~Board() {}

    int GetBoardSize() { return boardSize; }
    void MarkNexLegalMoves(Cell currentCell, ChessPieces chessPiece)
    {
        // Step 1 - clear all the previous legal moves
        for (int i = 0; i < this->boardSize; i++)
        {
            for (int j = 0; j < this->boardSize; j++)
            {
                boardGrid[i][j].IsCellOccupied() = false;
                boardGrid[i][j].LegalMove() = false;
            }
        }

        // Step 2 - Find all the legal moves and mark the cells as "Legal"
        switch (chessPiece)
        {
        case ChessPieces::KNIGHT:
            if (currentCell.GetRowNumber() + 2 <= boardSize - 1 && currentCell.GetColNumber() + 1 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() + 2][currentCell.GetColNumber() + 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 2 <= boardSize - 1 && currentCell.GetColNumber() - 1 >= 0)
                boardGrid[currentCell.GetRowNumber() + 2][currentCell.GetColNumber() - 1].LegalMove() = true;
            if (currentCell.GetRowNumber() - 1 >= 0 && currentCell.GetColNumber() + 2 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() - 1][currentCell.GetColNumber() + 2].LegalMove() = true;
            if (currentCell.GetRowNumber() - 1 >= 0 && currentCell.GetColNumber() - 2 >= 0)
                boardGrid[currentCell.GetRowNumber() - 1][currentCell.GetColNumber() - 2].LegalMove() = true;
            if (currentCell.GetRowNumber() - 2 >= 0 && currentCell.GetColNumber() + 1 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() - 2][currentCell.GetColNumber() + 1].LegalMove() = true;
            if (currentCell.GetRowNumber() - 2 >= 0 && currentCell.GetColNumber() - 1 >= 0)
                boardGrid[currentCell.GetRowNumber() - 2][currentCell.GetColNumber() - 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 1 <= boardSize - 1 && currentCell.GetColNumber() + 2 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() + 1][currentCell.GetColNumber() + 2].LegalMove() = true;
            if (currentCell.GetRowNumber() + 1 <= boardSize - 1 && currentCell.GetColNumber() - 2 >= 0)
                boardGrid[currentCell.GetRowNumber() + 1][currentCell.GetColNumber() - 2].LegalMove() = true;
            break;

        case ChessPieces::KING:
            if (currentCell.GetRowNumber() - 1 >= 0 && currentCell.GetColNumber() - 1 >= 0)
                boardGrid[currentCell.GetRowNumber() - 1][currentCell.GetColNumber() - 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 0 >= 0 && currentCell.GetColNumber() - 1 >= 0)
                boardGrid[currentCell.GetRowNumber() + 0][currentCell.GetColNumber() - 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 1 <= boardSize - 1 && currentCell.GetColNumber() - 1 >= 0)
                boardGrid[currentCell.GetRowNumber() + 1][currentCell.GetColNumber() - 1].LegalMove() = true;
            if (currentCell.GetRowNumber() - 1 >= 0 && currentCell.GetColNumber() + 1 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() - 1][currentCell.GetColNumber() + 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 1 <= boardSize - 1 && currentCell.GetColNumber() + 0 >= 0)
                boardGrid[currentCell.GetRowNumber() + 1][currentCell.GetColNumber() + 0].LegalMove() = true;
            if (currentCell.GetRowNumber() + 1 <= boardSize - 1 && currentCell.GetColNumber() + 1 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() + 1][currentCell.GetColNumber() + 1].LegalMove() = true;
            if (currentCell.GetRowNumber() + 0 >= 0 && currentCell.GetColNumber() + 1 <= boardSize - 1)
                boardGrid[currentCell.GetRowNumber() + 0][currentCell.GetColNumber() + 1].LegalMove() = true;
            if (currentCell.GetRowNumber() - 1 >= 0 && currentCell.GetColNumber() + 0 >= 0)
                boardGrid[currentCell.GetRowNumber() - 1][currentCell.GetColNumber() + 0].LegalMove() = true;
            break;
        case ChessPieces::ROOKE:
            // Left
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetColNumber() - i >= 0)
                    boardGrid[currentCell.GetRowNumber()][currentCell.GetColNumber() - i].LegalMove() = true;
            }
            // Right
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetColNumber() + i <= boardSize - 1)
                    boardGrid[currentCell.GetRowNumber()][currentCell.GetColNumber() + i].LegalMove() = true;
            }
            // Down
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetRowNumber() + i <= boardSize - 1)
                    boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber()].LegalMove() = true;
            }
            // Up
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetRowNumber() - i >= 0)
                    boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber()].LegalMove() = true;
            }

            break;
        case ChessPieces::BISHOP:

            for (int i = 0; i < boardSize; i++)
            {
                for (int j = 0; j < boardSize; j++)
                {
                    // Down Right
                    if (currentCell.GetRowNumber() + i <= boardSize - 1 && currentCell.GetColNumber() + j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber() + j].LegalMove() = true;
                    }
                    // Down Left
                    if (currentCell.GetRowNumber() + i <= boardSize - 1 && currentCell.GetColNumber() - j >= 0 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber() - j].LegalMove() = true;
                    }
                    // Up Left
                    if (currentCell.GetRowNumber() - i >= 0 && currentCell.GetColNumber() - j >= 0 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber() - j].LegalMove() = true;
                    }
                    // Up Right
                    if (currentCell.GetRowNumber() - i >= 0 && currentCell.GetColNumber() + j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber() + j].LegalMove() = true;
                    }
                }
            }

            break;
        case ChessPieces::PAWN:
            break;
        case ChessPieces::QUEEN:
            // The Queen is just the Rooke and bishop Combined!!
            // Left
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetColNumber() - i >= 0)
                    boardGrid[currentCell.GetRowNumber()][currentCell.GetColNumber() - i].LegalMove() = true;
            }
            // Right
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetColNumber() + i <= boardSize - 1)
                    boardGrid[currentCell.GetRowNumber()][currentCell.GetColNumber() + i].LegalMove() = true;
            }
            // Down
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetRowNumber() + i <= boardSize - 1)
                    boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber()].LegalMove() = true;
            }
            // Up
            for (int i = 0; i < boardSize; i++)
            {
                if (currentCell.GetRowNumber() - i >= 0)
                    boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber()].LegalMove() = true;
            }

            // Diagonals
            for (int i = 0; i < boardSize; i++)
            {
                for (int j = 0; j < boardSize; j++)
                {
                    // Down Right
                    if (currentCell.GetRowNumber() + i <= boardSize - 1 && currentCell.GetColNumber() + j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber() + j].LegalMove() = true;
                    }
                    // Down Left
                    if (currentCell.GetRowNumber() + i <= boardSize - 1 && currentCell.GetColNumber() - j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() + i][currentCell.GetColNumber() - j].LegalMove() = true;
                    }
                    // Up Left
                    if (currentCell.GetRowNumber() - i >= 0 && currentCell.GetColNumber() - j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber() - j].LegalMove() = true;
                    }
                    // Up Right
                    if (currentCell.GetRowNumber() - i >= 0 && currentCell.GetColNumber() + j <= boardSize - 1 && i == j)
                    {
                        boardGrid[currentCell.GetRowNumber() - i][currentCell.GetColNumber() + j].LegalMove() = true;
                    }
                }
            }
            break;
        default:
            break;
        }
        boardGrid[currentCell.GetRowNumber()][currentCell.GetColNumber()].IsCellOccupied() = true;
    }
};
