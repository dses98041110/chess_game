#include "ChessBox.h"
#include "Game.h"
#include <QDebug>
#include<bits/stdc++.h>

extern Game *game;
ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //making the Square CHess Box
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
//    setChessPieceColor("NONE");
    currentPiece = NULL;
}
//-----------------------------------------------
ChessBox::~ChessBox()
{
    delete this;
}
//-----------------------------------------------
void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event){ 
    if(currentPiece == game->pieceToMove && currentPiece){
        currentPiece->mousePressEvent(event);
        return;
    }

    //if selected
    if(game->pieceToMove){

        //TO make sure the selected box is in move zone
        QList <ChessBox *> movLoc = game->pieceToMove->moveLocation();
        int legalMove = 0;
        for(size_t i = 0, n = movLoc.size(); i < n;i++) {
            if(movLoc[i] == this) {
                legalMove++;
                break;
            }
        }
        // if not prsent return
        if(legalMove == 0){
            game->pieceToMove->getCurrentBox()->resetOriginalColor();
            game->pieceToMove->decolor();
            game->pieceToMove = NULL;
            return;
        }

        //change the color back to normal
         game->pieceToMove->decolor();

         //make the first move false applicable for pawn only
         game->pieceToMove->firstMove = false;

        //this is to eat or consume the enemy present inn the movable region
       if(this->getHasChessPiece()){
           this->currentPiece->setIsPlaced(false);
           this->currentPiece->setCurrentBox(NULL);
           game->removeFromScene(this->currentPiece);

       }
       int x,y;
       x=game->pieceToMove->getCurrentBox()->x();
       y=game->pieceToMove->getCurrentBox()->y();
       int current_position =63-( x/62 + (y/62)*8 );
       x=this->x();
       y=this->y();
       int target_position =63-( x/62 + (y/62)*8 );



        //changing the new stat and resetting the previous left region
        game->pieceToMove->getCurrentBox()->setHasChessPiece(false);
        game->pieceToMove->getCurrentBox()->currentPiece = NULL;
        game->pieceToMove->getCurrentBox()->resetOriginalColor();

        //placePiece
        placePiece(game->pieceToMove);
        //placePiece_end

        //bitBoardUpdate
       game->bitBoardUpdate(&(game->chess_position),current_position,target_position);
        //bitBoardUpdate_end
        for(int i=0;i<64;i++){
            if(game->chess_position.pieceInSquare[i]==-6){
                game->check(game->chess_position.pieceInSquare,i);
                break;
            }

        }


       //check_end
        game->pieceToMove = NULL;

        //minimx
        game->hashTableList.clear();
        int bestMove=87;
        int bestPiece=87;
        int maxValue=INT_MAX;
        for(int i=0;i<64;i++){
            if(game->chess_position.pieceInSquare[i]&0x8){
                int score=game->minimax(game->chess_position.pieceInSquare,i,INT_MIN,INT_MAX,2);
                if((score<=maxValue)&&(rand()%2+0)){
                    maxValue=score;
                    bestMove=game->bestBlackMoveTarget;
                    bestPiece=i;

                }
            }
        }
        //minimx_end

//        game->negaMax(0,4,INT_MIN,INT_MAX);
        game->blackMove(bestPiece,bestMove);
        game->bitBoardUpdate(&(game->chess_position),bestPiece,bestMove);
        for(int i=0;i<64;i++){
            if(game->chess_position.pieceInSquare[i]==-6){
                game->check(game->chess_position.pieceInSquare,i);
                break;
            }

        }

    }
    //Selecting couterpart of the chessPiece
    else if(this->getHasChessPiece())
    {
        this->currentPiece->mousePressEvent(event);
    }

}
//-----------------------------------------------
void ChessBox::placePiece(ChessPiece *piece)
{

    piece->setPos(x()+31- piece->pixmap().width()/2  ,y()+31-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;


}
//-----------------------------------------------
void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}
//-----------------------------------------------
void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}
//-----------------------------------------------
void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}
//-----------------------------------------------
void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
}
//-----------------------------------------------
bool ChessBox::getHasChessPiece()
{
    return hasChessPiece;
}
