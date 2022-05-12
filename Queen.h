#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
class Queen:public ChessPiece
{
public:
    Queen(bool team,int category,QGraphicsItem *parent = 0);

    void moves();
    void setLegalMove();
    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();
private:
    void setImage();
};
#endif // QUEEN_H
