#include "Pawn.h"
#include <QDebug>
#include "Game.h"

extern Game* game;
Pawn::Pawn(bool team, int category,QGraphicsItem *parent)
{
    side = team;
    this->category=category;
    setImage();
}

void Pawn::setImage()
{
    if(side){
        setPixmap(QPixmap(":/image/WhitePawn.png"));
    }
    else{
        setPixmap(QPixmap(":/image/BlackPawn.png"));
    }
}

void Pawn::moves(){
    location.clear();
     x=this->getCurrentBox()->x();
     y=this->getCurrentBox()->y();
     position =63-( x/62 + (y/62)*8 );
     p=0;
     temp;


    if(firstMove){
        if(this->getSide()){
            temp_move=game->whitePawn_firstMove[position];
            temp_eat=game->whitePawn_eat[position];

            if(temp_move&game->chess_position.pieces){
                if((game->chess_position.pieces>>(position+8))&1){
                    temp_move=0;
                }
                else{
                    temp_move^=game->mask[position+16];
                }
            }

        }
        else{
            temp_move=game->blackPawn_firstMove[position];
            temp_eat=game->blackPawn_eat[position];

            if(temp_move&game->chess_position.pieces){
                if((game->chess_position.pieces>>(position-8))&1){
                    temp_move=0;
                }
                else{
                    temp_move^=game->mask[position-16];
                }
            }
        }

    }
    else{
        if(this->getSide()){
            temp_move=game->whitePawn_move[position];
            temp_eat=game->whitePawn_eat[position];


        }
        else{
            temp_move=game->blackPawn_move[position];
            temp_eat=game->blackPawn_eat[position];
        }
        if(temp_move&game->chess_position.pieces){
           temp_move=0;
         }
    }
    temp=temp_eat|temp_move;
    while(temp){
        if((temp_move&1)){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        if((temp_eat&1)&((game->getSideBitBoard(!(this->getSide()))>>p)&1)){
            game->collection[7-(p>>3)][7-(p%8)]->setColor(Qt::red);
            location.append(game->collection[7-(p/8)][7-(p%8)]);
        }
        p++;
        temp_move>>=1;
        temp_eat>>=1;
        temp=temp_move|temp_eat;
    }

}

void Pawn::setLegalMove()
{
//    if(this->side){
//        game->chess_position.whitePawnsLegalMove=legalMove;
//    }
//    else{
//        game->chess_position.blackPawnsLegalMove=legalMove;
//    }
}

void Pawn::bitBoardMoves()
{
    x=this->getCurrentBox()->x();
    y=this->getCurrentBox()->y();
    position =63-( x/62 + (y/62)*8 );
    p=0;
    temp;

   legalMove=0;

   if(firstMove){
       if(this->getSide()){
           temp_move=game->whitePawn_firstMove[position];
           temp_eat=game->whitePawn_eat[position];

           if(temp_move&game->chess_position.pieces){
               if((game->chess_position.pieces>>(position+8))&1){
                   temp_move=0;
               }
               else{
                   temp_move^=game->mask[position+16];
               }
           }

       }
       else{
           temp_move=game->blackPawn_firstMove[position];
           temp_eat=game->blackPawn_eat[position];

           if(temp_move&game->chess_position.pieces){
               if((game->chess_position.pieces>>(position-8))&1){
                   temp_move=0;
               }
               else{
                   temp_move^=game->mask[position-16];
               }
           }
       }

   }
   else{
       if(this->getSide()){
           temp_move=game->whitePawn_move[position];
           temp_eat=game->whitePawn_eat[position];


       }
       else{
           temp_move=game->blackPawn_move[position];
           temp_eat=game->blackPawn_eat[position];
       }
       if(temp_move&game->chess_position.pieces){
          temp_move=0;
        }
   }
   temp=temp_eat|temp_move;
   while(temp){
       if((temp_move&1)){
           legalMove|=game->mask[p];
       }
       if((temp_eat&1)&((game->getSideBitBoard(!(this->getSide()))>>p)&1)){
           legalMove|=game->mask[p];
       }
       p++;
       temp_move>>=1;
       temp_eat>>=1;
       temp=temp_move|temp_eat;
   }
}
BitBoard Pawn::getBitBoard()
{
    if(this->side){
        return game->chess_position.whitePawns;
    }
    else{
        return game->chess_position.blackPawns;
    }
}

BitBoard Pawn::getLegalMove()
{
    return legalMove;

}


