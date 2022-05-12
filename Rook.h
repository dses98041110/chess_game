#ifndef ROOK_H
#define ROOK_H
#include "ChessPiece.h"

class Rook:public ChessPiece
{
public:
    Rook(bool team,int category,QGraphicsItem *parent = 0);

    void moves();
    void setLegalMove();

    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();
private:
    void setImage();
};
#endif // ROOK_H
