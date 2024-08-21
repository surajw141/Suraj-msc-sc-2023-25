#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = '-';
        }
    }
}

void Board::placeQueen(int row, int col)
{
    board[row][col] = 'Q';
}

void Board::removeQueen(int row, int col)
{
    board[row][col] = '-';
}

bool Board::isSafe(int row, int col)
{
    for (int i = 0; i < 8; i++)
    {
        if (board[row][i] == 'Q' || board[i][col] == 'Q')
            return false;
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == 'Q')
            return false;
        if (row + i < 8 && col + i < 8 && board[row + i][col + i] == 'Q')
            return false;
        if (row - i >= 0 && col + i < 8 && board[row - i][col + i] == 'Q')
            return false;
        if (row + i < 8 && col - i >= 0 && board[row + i][col - i] == 'Q')
            return false;
    }
    return true;
}

void Board::printBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
