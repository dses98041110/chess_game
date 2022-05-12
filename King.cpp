#include "King.h"
#include <QDebug>
#include "Game.h"


extern Game *game;
King::King(bool team, int category,QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();
}

void King::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhiteKing.png"));
    }
    else{
        setPixmap(QPixmap(":/image/BlackKing.png"));
    }
}

void King::moves(){
    location.clear();
     x=this->getCurrentBox()->x();
     y=this->getCurrentBox()->y();
     position =63-( x/62 + (y/62)*8 );
     p=0;
     temp=game->king[position];
    while(temp){
        if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        p++;
        temp>>=1;
    }

}

void King::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whiteKingsLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackKingsLegalMove=legalMove;
//    }
}
void King::bitBoardMoves()
{
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    temp=game->king[position];
   legalMove=0;

   while(temp){
       if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
           legalMove|=game->mask[p];
       }
       p++;
       temp>>=1;
   }
}

void King::setCheck(bool check)
{
    this->check=check;
}

bool King::getCheck()
{
    return check;
}

BitBoard King::getBitBoard()
{
    if(this->side){
        return game->chess_position.whiteKings;
    }
    else{
        return game->chess_position.blackKings;
    }
}

BitBoard King::getLegalMove()
{
    return legalMove;

}


