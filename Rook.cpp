#include "Rook.h"
#include <QDebug>

#include "Game.h"

extern Game *game;
Rook::Rook(bool team,int category, QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();
}

void Rook::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhiteRook.png"));
    }
    else{
        setPixmap(QPixmap(":/image/BlackRook.png"));
    }
}

void Rook::moves(){
    location.clear();
     x=this->getCurrentBox()->x();
     y=this->getCurrentBox()->y();
     position =63-( x/62 + (y/62)*8 );
     p=0;
     temp=(game->rank_attacks[position][(game->chess_position.pieces>>(8*(position/8)))&0xff])|(game->file_attacks[position][(game->chess_position.rotated_90>>(8*(game->r90R_map[position]/8)))&0xff]);

    while(temp){
        if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        p++;
        temp>>=1;
    }

}

void Rook::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whiteRooksLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackRooksLegalMove=legalMove;
//    }
}


void Rook::bitBoardMoves()
{

    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    temp=(game->rank_attacks[position][(game->chess_position.pieces>>(8*(position/8)))&0xff])|(game->file_attacks[position][(game->chess_position.rotated_90>>(8*(game->r90R_map[position]/8)))&0xff]);
   legalMove=0;

   while(temp){
       if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
           legalMove|=game->mask[p];
       }
       p++;
       temp>>=1;
   }
}

BitBoard Rook::getBitBoard()
{
    if(this->side){
        return game->chess_position.whiteRooks;
    }
    else{
        return game->chess_position.blackRooks;
    }
}

BitBoard Rook::getLegalMove()
{
    return legalMove;

}

