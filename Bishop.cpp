#include "Bishop.h"
#include <QDebug>
#include "Game.h"

extern Game *game;
Bishop::Bishop(bool team, int category,QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();

}

void Bishop::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhiteBishop.png"));

    }
    else{
        setPixmap(QPixmap(":/image/BlackBishop.png"));
    }
}

void Bishop::moves()
{
    location.clear();
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    b=1;
    temp=(game->diag_H8A1_attacks[position][(((game->chess_position.rotated45)>>(game->shift_H8A1_diag[position]))&((b<<(game->length_H8A1_diag[position]))-1))])|(game->diag_A8H1_attacks[position][(((game->chess_position.rotated_45)>>(game->shift_A8H1_diag[position]))&((b<<(game->length_A8H1_diag[position]))-1))]);

    while(temp){
        if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        p++;
        temp>>=1;
    }
}

void Bishop::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whiteBishopsLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackBishopsLegalMove=legalMove;
//    }
}

void Bishop::bitBoardMoves()
{
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    legalMove=0;
    b=1;
    temp=(game->diag_H8A1_attacks[position][(((game->chess_position.rotated45)>>(game->shift_H8A1_diag[position]))&((b<<(game->length_H8A1_diag[position]))-1))])|(game->diag_A8H1_attacks[position][(((game->chess_position.rotated_45)>>(game->shift_A8H1_diag[position]))&((b<<(game->length_A8H1_diag[position]))-1))]);
    while(temp){
        if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
            legalMove|=game->mask[p];
        }
        p++;
        temp>>=1;
    }
}

BitBoard Bishop::getBitBoard()
{
    if(this->side){
        return game->chess_position.whiteBishops;
    }
    else{
        return game->chess_position.blackBishops;
    }
}

BitBoard Bishop::getLegalMove()
{
    return legalMove;
}


