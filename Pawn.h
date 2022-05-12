#ifndef PAWN_H
#define PAWN_H
#include "ChessPiece.h"
class Pawn:public ChessPiece
{
public:
    Pawn(bool team,int category,QGraphicsItem *parent = 0);
    void moves();
    void setLegalMove();
    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();
private:
    void setImage();

};
#endif // PAWN_H
