#include "Board.h"
#include "Queen.h"

int main()
{
    Board board;

    // Example solution
    board.placeQueen(0, 0);
    board.placeQueen(1, 2);
    board.placeQueen(2, 4);
    board.placeQueen(3, 6);
    board.placeQueen(4, 1);
    board.placeQueen(5, 3);
    board.placeQueen(6, 5);
    board.placeQueen(7, 7);

    board.printBoard();

    return 0;
}
