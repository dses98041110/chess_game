#include "Knight.h"
#include <QDebug>
#include "Game.h"

extern Game *game;
Knight::Knight(bool team, int category,QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();
}

void Knight::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhiteKnight.png"));
    }
    else{
        setPixmap(QPixmap(":/image/BlackKnight.png"));
    }
}

void Knight::moves(){
   location.clear();
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
     p=0;
    temp=game->knight[position];

   while(temp){
       if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
           game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
           location.append(game->collection[7-(p/8)][7-(p%8)]);
       }
       p++;
       temp>>=1;
   }


}

void Knight::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whiteKnightsLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackKnightsLegalMove=legalMove;
//    }
}
void Knight::bitBoardMoves()
{
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
     p=0;
    temp=game->knight[position];
   legalMove=0;

   while(temp){
       if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
           legalMove|=game->mask[p];
       }
       p++;
       temp>>=1;
   }

}

BitBoard Knight::getBitBoard()
{
    if(this->side){
        return game->chess_position.whiteKnights;
    }
    else{
        return game->chess_position.blackKnights;
    }
}

BitBoard Knight::getLegalMove()
{
    return legalMove;

}


