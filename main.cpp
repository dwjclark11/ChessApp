#include <iostream>
#include <windows.h>
#include "Board.h"
#include <stdio.h>
#include <assert.h>

// Constants
const int screenWidth = 120;
const int screenHeight = 30;
const DWORD consoleWrite = screenWidth * screenHeight;
// Create Screen Buffer
wchar_t* screen = new wchar_t[screenWidth * screenHeight];

// Create a new chessBoard
Board chessBoard(8);

const wchar_t* GetPieceLetter(Board::ChessPieces piece)
{
    switch (piece)
    {
    case Board::ChessPieces::KING:
        return L"K";
        break;

    case Board::ChessPieces::QUEEN:
        return L"Q";
        break;

    case Board::ChessPieces::ROOKE:
        return L"R";
        break;

    case Board::ChessPieces::BISHOP:
        return L"B";
        break;

    case Board::ChessPieces::KNIGHT:
        return L"N";
        break;
    default:
        break;
    }
    return L"X";
}

void PrintBoard(Board board, Board::ChessPieces piece)
{
    swprintf(&screen[5 * screenWidth + 50], L" =============");
    swprintf(&screen[6 * screenWidth + 50], L" |Game Board |");
    swprintf(&screen[7 * screenWidth + 50], L" =============");

    // Print col numbers
    swprintf(&screen[8 * screenWidth + 40], L"   0   1   2   3   4   5   6   7");

    for (int i = 0; i < board.GetBoardSize(); i++)
    {
        swprintf(&screen[(9 + i * 2) * screenWidth + 40], L" +---+---+---+---+---+---+---+---+");
        swprintf(&screen[(10 + i * 2) * screenWidth + 39], L"%d", i);

        for (int j = 0; j < board.GetBoardSize(); j++)
        {
            if (board.boardGrid[i][j].IsCellOccupied())
            {
                swprintf(&screen[(10 + i * 2) * screenWidth + 43 + (j * 4)], GetPieceLetter(piece));
            }
            else if (board.boardGrid[i][j].LegalMove())
            {
                swprintf(&screen[(10 + i * 2) * screenWidth + 43 + (j * 4)], L"+");
            }
            else
            {
                swprintf(&screen[(10 + i * 2) * screenWidth + 43 + (j * 4)], L".");
            }
            swprintf(&screen[(10 + i * 2) * screenWidth + 41 + (j * 4)], L"|");

            // Close the box
            if (j == board.GetBoardSize() - 1)
                swprintf(&screen[(10 + i * 2) * screenWidth + 41 + (board.GetBoardSize() * 4)], L"|");

        }
    }
    swprintf(&screen[25 * screenWidth + 40], L" +---+---+---+---+---+---+---+---+");
}

Board::ChessPieces GetSelectedChessPiece(int& pieceNum, const wchar_t* pieceName)
{
    switch (pieceNum)
    {
    case 0:
        return Board::ChessPieces::KING;
        break;

    case 1:
        return Board::ChessPieces::QUEEN;
        break;

    case 2:
        return Board::ChessPieces::ROOKE;
        break;
    case 3:
        return Board::ChessPieces::BISHOP;
        break;
    case 4:
        return Board::ChessPieces::KNIGHT;
        break;
    default:
        break;
    }
    return Board::ChessPieces::KNIGHT;
}

int main()
{
    // Set the Screen Buffer Values
    for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';
    HANDLE consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(consoleHandle);
    DWORD bytesWritten = 0;

    // Variables
    int player = 1;
    int row = -1;
    int col = -1;
    int pieceNum = 0;
    Board::ChessPieces pieceType = Board::ChessPieces::KING;

    const wchar_t* pieceName = L"";
    bool rowSet = false, colSet = false, pieceSet = false;
    bool keyRight = false, keyLeft = false, keyRightPrev = false, keyLeftPrev = false, enterKey = false, enterKeyPrev = false;
    bool choosePiece = true, checkWin = false, cellOccupied = false, fullBoard = false;
    bool gameRunning = true;
    bool finished = false;
    // Run the Game loop
    while (gameRunning)
    {
        row = 0;
        col = 0;

        while (!finished)
        {
            // Set input/key values
            keyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000);
            keyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000);
            enterKey = (GetAsyncKeyState(VK_RETURN) & 0x8000);

            // Clear the screen
            for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';

            // Print the Title Bar
            swprintf(&screen[1 * screenWidth + 15], L"=========================================================================================");
            swprintf(&screen[2 * screenWidth + 15], L"|                 Welcome to this Simple Chess Legal Move Checker Game!                 |");
            swprintf(&screen[3 * screenWidth + 15], L"=========================================================================================");

            // Print the Chess Board
            PrintBoard(chessBoard, pieceType);
            //swprintf(&screen[4 * screenWidth + 50], L"Player# %d's Turn!", player);
            swprintf(&screen[4 * screenWidth + 43], L"Please enter the row number: %d", row);

            // If left key pressed
            if (keyLeft && !keyLeftPrev)
            {
                if (!rowSet)
                    row--;
                else if (!colSet)
                    col--;
                else if (choosePiece)
                    pieceNum--;
            }
            // If right key pressed
            else if (keyRight && !keyRightPrev)
            {
                if (!rowSet)
                    row++;
                else if (!colSet)
                    col++;
                else if (choosePiece)
                    pieceNum++;
            }
            // only allow one increment per key press
            keyRightPrev = keyRight;
            keyLeftPrev = keyLeft;

            // clamp row to 0-2
            if (row <= 0) row = 0;
            else if (row >= 7) row = 7;

            // clamp col to 0-2
            if (col <= 0) col = 0;
            else if (col >= 7) col = 7;

            // clamp col to 0-2
            if (pieceNum <= 0) pieceNum = 0;
            else if (pieceNum >= 4) pieceNum = 4;

            // Enter key pressed
            if (enterKey && !enterKeyPrev)
            {
                if (!rowSet)
                    rowSet = true;
                else if (!colSet)
                    colSet = true;
                else if (choosePiece)
                    pieceSet = true;
            }
            enterKeyPrev = enterKey;

            if (rowSet)
                swprintf(&screen[4 * screenWidth + 43], L"Please enter the col number: %d", col);

            // if row and col are chosen, try to place the player character
            if (rowSet && colSet && !pieceSet)
            {
                swprintf(&screen[26 * screenWidth + 32], L"What chess piece do you want to see the legal moves for?");

                if (GetSelectedChessPiece(pieceNum, pieceName) == Board::ChessPieces::KING)
                {
                    pieceType = Board::ChessPieces::KING;
                    pieceName = L"KING";
                }
                else if (GetSelectedChessPiece(pieceNum, pieceName) == Board::ChessPieces::QUEEN)
                {
                    pieceType = Board::ChessPieces::QUEEN;
                    pieceName = L"QUEEN";
                }
                else if (GetSelectedChessPiece(pieceNum, pieceName) == Board::ChessPieces::BISHOP)
                {
                    pieceType = Board::ChessPieces::BISHOP;
                    pieceName = L"BISHOP";
                }
                else if (GetSelectedChessPiece(pieceNum, pieceName) == Board::ChessPieces::ROOKE)
                {
                    pieceType = Board::ChessPieces::ROOKE;
                    pieceName = L"ROOKE";
                }
                else if (GetSelectedChessPiece(pieceNum, pieceName) == Board::ChessPieces::KNIGHT)
                {
                    pieceType = Board::ChessPieces::KNIGHT;
                    pieceName = L"KNIGHT";
                }
                swprintf(&screen[27 * screenWidth + 32], L"PIECE: %lS", pieceName);
                choosePiece = true;
            }

            if (pieceSet)
            {
                chessBoard.MarkNexLegalMoves(chessBoard.boardGrid[row][col], pieceType);
                swprintf(&screen[26 * screenWidth + 32], L"HIT 'SPACE' TO SELECT ANOTHER PIECE");
                swprintf(&screen[27 * screenWidth + 42], L"HIT 'ESC' TO EXIT");
                finished = true;
                PrintBoard(chessBoard, pieceType);
            }

            // Draw Closing Bar
            swprintf(&screen[29 * screenWidth + 15], L"=========================================================================================");

            // Draw Left Bar
            for (int i = 0; i < screenHeight - 5; i++)
                swprintf(&screen[(4 + i) * screenWidth + 15], L"|");

            // Draw Right Bar
            for (int i = 0; i < screenHeight - 5; i++)
                swprintf(&screen[(4 + i) * screenWidth + 103], L"|");

            // Render Frame
            WriteConsoleOutputCharacter(consoleHandle, screen, consoleWrite, { 0, 0 }, &bytesWritten);

        }
        // Wait here for space bar to continue or esc to quit game
        while ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0)
        {
            // If escape is pressed leave game
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gameRunning = false;
                break;
            }
        }
        // Reset winner status
        finished = false;
        rowSet = false;
        colSet = false;
        pieceSet = false;

        // Clear the board
        for (int i = 0; i < chessBoard.GetBoardSize(); i++)
        {
            for (int j = 0; j < chessBoard.GetBoardSize(); j++)
            {
                chessBoard.boardGrid[i][j].IsCellOccupied() = false;
                chessBoard.boardGrid[i][j].LegalMove() = false;
            }
        }
    }

    return 0;
}
