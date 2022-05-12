#ifndef BISHOP_H
#define BISHOP_H
#include "ChessPiece.h"

class Bishop:public ChessPiece
{
public:
    Bishop(bool team ,int category,QGraphicsItem *parent = 0);

    void moves();

    void setLegalMove();

    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();

private:
    void setImage();
};


#endif // BISHOP_H
