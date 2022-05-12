#include "ChessPiece.h"
#include "Game.h"

#include <QDebug>

extern Game *game;
ChessPiece::ChessPiece(bool team,int category, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->pieceToMove==this){
        return;
    }
    if(game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
    }
    game->pieceToMove=this;
    game->pieceToMove->getCurrentBox()->setColor(Qt::darkGray);
    game->pieceToMove->moves();


}
//-----------------------------------------------
void ChessPiece::setCurrentBox(ChessBox *box)
{
    currentBox = box;
}
//-----------------------------------------------
ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}
//-----------------------------------------------
bool ChessPiece::getSide()
{
    return side;
}
//-----------------------------------------------

int ChessPiece::getCategory()
{
    return category;
}
//-----------------------------------------------
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
//-----------------------------------------------
void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;

}
//-----------------------------------------------
bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}
//-----------------------------------------------
void ChessPiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

