#include "Queen.h"
#include <QDebug>
#include "Game.h"

extern Game *game;
Queen::Queen(bool team, int category,QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();
}

void Queen::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhiteQueen.png"));
    }
    else{
        setPixmap(QPixmap(":/image/BlackQueen.png"));
    }
}

void Queen::moves(){
    location.clear();
     x=this->getCurrentBox()->x();
     y=this->getCurrentBox()->y();
     position =63-( x/62 + (y/62)*8 );
     p=0;
     b=1;
     rook_temp=(game->rank_attacks[position][(game->chess_position.pieces>>(8*(position/8)))&0xff])|(game->file_attacks[position][(game->chess_position.rotated_90>>(8*(game->r90R_map[position]/8)))&0xff]);
     bishop_temp=(game->diag_H8A1_attacks[position][(((game->chess_position.rotated45)>>(game->shift_H8A1_diag[position]))&((b<<(game->length_H8A1_diag[position]))-1))])|(game->diag_A8H1_attacks[position][(((game->chess_position.rotated_45)>>(game->shift_A8H1_diag[position]))&((b<<(game->length_A8H1_diag[position]))-1))]);
     temp=rook_temp|bishop_temp;

    while(temp){
        if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        p++;
        temp>>=1;
    }
}

void Queen::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whiteQueensLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackQueensLegalMove=legalMove;
//    }
}


void Queen::bitBoardMoves()
{

    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    b=1;
    rook_temp=(game->rank_attacks[position][(game->chess_position.pieces>>(8*(position/8)))&0xff])|(game->file_attacks[position][(game->chess_position.rotated_90>>(8*(game->r90R_map[position]/8)))&0xff]);
    bishop_temp=(game->diag_H8A1_attacks[position][(((game->chess_position.rotated45)>>(game->shift_H8A1_diag[position]))&((b<<(game->length_H8A1_diag[position]))-1))])|(game->diag_A8H1_attacks[position][(((game->chess_position.rotated_45)>>(game->shift_A8H1_diag[position]))&((b<<(game->length_A8H1_diag[position]))-1))]);
    temp=rook_temp|bishop_temp;
   legalMove=0;

   while(temp){
       if((temp&1)&(!((game->getSideBitBoard(this->getSide())>>p)&1))){
           legalMove|=game->mask[p];
       }
       p++;
       temp>>=1;
   }
}
BitBoard Queen::getBitBoard()
{
    if(this->side){
        return game->chess_position.whiteQueens;
    }
    else{
        return game->chess_position.blackQueens;
    }
}

BitBoard Queen::getLegalMove()
{
    return legalMove;

}


