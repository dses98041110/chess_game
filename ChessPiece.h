#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QGraphicsPixmapItem>
#include "ChessBox.h"
#include <QGraphicsSceneMouseEvent>
#include <QTime>
typedef unsigned long long BitBoard;

class ChessBox;
class ChessPiece:public QGraphicsPixmapItem
{
public:
    ChessPiece(bool team =0,int category=0,QGraphicsItem *parent =0);


    ChessBox *getCurrentBox() ;
    bool getSide() ;
    int getCategory();
    bool getIsPlaced() ;
    QList <ChessBox *> moveLocation();

    void decolor();

    bool firstMove;


    virtual void setLegalMove()=0;

    virtual BitBoard getLegalMove()=0;
    virtual BitBoard getBitBoard()=0;

    virtual void moves() = 0;
    virtual void bitBoardMoves()=0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(ChessBox *box);
    void setSide( bool value);
    void setIsPlaced(bool value);
    bool boxSetting(ChessBox *box);

protected:
    virtual void setImage() = 0;

    ChessBox *currentBox;
    bool side;
    int category;
    bool isPlaced;
    QList <ChessBox *> location;
    BitBoard legalMove;
    ///////////////////////
    int x;
    int y;
    int position;
    int p;
    BitBoard b;
    BitBoard temp;
    BitBoard rook_temp;
    BitBoard bishop_temp;
    BitBoard temp_eat;
    BitBoard temp_move;

};
#endif // CHESSPIECE_H
