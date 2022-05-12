#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include <QDebug>

class ChessBoard
{
public:
    ChessBoard();

    //drawing public function
    void drawBoxes(int x, int y);

    void setUpWhite();
    void setUpBlack();
    void setUpBitBoard_Mask();
    void setUppiece_in_square();

    void addChessPiece();
    void reset();
private:
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;
};

#endif // CHESSBOARD_H
