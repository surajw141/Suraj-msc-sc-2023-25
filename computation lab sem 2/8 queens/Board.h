#include <iostream>

class Board
{
private:
    char board[8][8];

public:
    Board();
    void placeQueen(int row, int col);
    void removeQueen(int row, int col);
    bool isSafe(int row, int col);
    void printBoard();
};
