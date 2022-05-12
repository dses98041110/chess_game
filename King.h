#ifndef KING_H
#define KING_H
#include "ChessPiece.h"

class King:public ChessPiece
{
public:
    King(bool team,int category,QGraphicsItem *parent = 0);
    void moves();
    void setLegalMove();
    BitBoard getBitBoard();
    BitBoard getLegalMove();
    void bitBoardMoves();
    void setCheck(bool check);
    bool getCheck();
private:
    void setImage();
    bool check;
};
#endif // KING_H
