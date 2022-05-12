#ifndef KNIGHT_H
#define KNIGHT_H
#include "ChessPiece.h"

class Knight:public ChessPiece
{
public:
    Knight(bool team,int category,QGraphicsItem *parent = 0);

    void moves();
    void setLegalMove();
    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();
private:
    void setImage();

};
#endif // KNIGHT_H
