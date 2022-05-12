#include "ChessBoard.h"
#include "ChessBox.h"
#include "Game.h"

extern Game *game;
ChessBoard::ChessBoard()
{
    setUpWhite();
    setUpBlack();

}
//-----------------------------------------------
void ChessBoard::drawBoxes(int x,int y)
{
    int SHIFT = 62;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::white);
            else
                box->setOriginalColor(Qt::darkGreen);
            game->addToScene(box);
        }
    }

}
//-----------------------------------------------
void ChessBoard::addChessPiece() {

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box =game->collection[i][j];
            if(i < 2) {
                static int k;
                box->placePiece(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 5) {
                static int h;
                box->placePiece(white[h]);
                game->addToScene(white[h++]);
            }
        }
    }
}
//-----------------------------------------------
void ChessBoard::setUpWhite()
{
    ChessPiece *piece;

    for(int i = 15; i >=0 ; i--) {

        switch (game->chess_position.pieceInSquare[i]) {
        case 1:
            piece = new Pawn(1,1);
            white.append(piece);
            break;
        case 2:
            piece = new Knight(1,2);
            white.append(piece);
            break;
        case 3:
            piece = new Bishop(1,3);
            white.append(piece);
            break;
        case 4:
            piece = new Rook(1,4);
            white.append(piece);
            break;
        case 5:
            piece = new Queen(1,5);
            white.append(piece);
            break;
        case 6:
            piece = new King(1,6);
            white.append(piece);
            break;
        default:
            break;
        }
    }

}
//-----------------------------------------------
void ChessBoard::setUpBlack()
{

    ChessPiece *piece;

    for(int i = 63; i >=48 ; i--) {

        switch (game->chess_position.pieceInSquare[i]) {
        case -1:
            piece = new Pawn(0,-1);
            black.append(piece);
            break;
        case -2:
            piece = new Knight(0,-2);
            black.append(piece);
            break;
        case -3:
            piece = new Bishop(0,-3);
            black.append(piece);
            break;
        case -4:
            piece = new Rook(0,-4);
            black.append(piece);
            break;
        case -5:
            piece = new Queen(0,-5);
            black.append(piece);
            break;
        case -6:
            piece = new King(0,-6);
            black.append(piece);
            break;
        default:
            break;
        }
    }
}




