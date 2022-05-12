#include "Game.h"
#include <QPixmap>
#include "King.h"
#include <QDebug>
#include <QMessageBox>
/*
 white =1;
 black =0;
 */
Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,500,500);

    //Making the view
    setFixedSize(500,500);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
//    qDebug()<<bin<<(bool)!(0&0x80)<<(bool)!(4&0x80)<<(bool)!(-4&0x80);
    pieceToMove = NULL;

    //test

}
//-----------------------------------------------drawChessBoard
void Game::drawChessBoard()
{
    chessBoard = new ChessBoard();
    chessBoard->drawBoxes(0,0);
}
//-------------------------------------------------------------
//-----------------------------------------------addChessPiece
void Game::addChessPiece()
{
    chessBoard->addChessPiece();
    //-----------------------------------------------
}
//-----------------------------------------------addToScene
void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}
//----------------------------------------------------
//-----------------------------------------------removeFromScene
void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}
//----------------------------------------------------
//-----------------------------------------------
//1:Pawn,2:Knight,3:Biship,4:Rook,5:Queen,6:King
void Game::initializeChessPieceMoveBoards()
{
    //home

    /*
     * 63 62 61 60 59 58 57 56
     * 55 54 53 52 51 50 49 48
     * 47 46 45 44 43 42 41 40
     * 39 38 37 36 35 34 33 32
     * 31 30 29 28 27 26 25 24
     * 23 22 21 20 19 18 17 16
     * 15 14 13 12 11 10  9  8
     *  7  6  5  4  3  2  1  0
    */

    //mask
     //Knight
     //king
     //blackpawn_move
     //whitepawn_move
     //blackpawn_eat
     //whitepawn_eat
     //blackpawn_firstMove
     //whitepawn_firstMove
     //r90R_map
     //_r90R_map
     //r45R_map
     //ur45R_map
     //_r45R_map
     //rook_rank
     //rook_file
     //bishop_diag_A8H1
     //bishop_diag_H8A1
     //create__r90_board
     //create_r45_board
     //create_r_45_board
     //test

    int c,k,p,i;
    BitBoard temp;
    BitBoard b=1;

    for(c=0;c<64;c++){
         chess_position.pieceInSquare[c]=0;
    }
    for(c=0;c<8;c++){
        chess_position.pieceInSquare[8+c]=1;
        chess_position.pieceInSquare[48+c]=-1;
    }
    chess_position.pieceInSquare[0]=4;
    chess_position.pieceInSquare[1]=2;
    chess_position.pieceInSquare[2]=3;
    chess_position.pieceInSquare[3]=6;
    chess_position.pieceInSquare[4]=5;
    chess_position.pieceInSquare[5]=3;
    chess_position.pieceInSquare[6]=2;
    chess_position.pieceInSquare[7]=4;
    chess_position.pieceInSquare[56]=-4;
    chess_position.pieceInSquare[57]=-2;
    chess_position.pieceInSquare[58]=-3;
    chess_position.pieceInSquare[59]=-6;
    chess_position.pieceInSquare[60]=-5;
    chess_position.pieceInSquare[61]=-3;
    chess_position.pieceInSquare[62]=-2;
    chess_position.pieceInSquare[63]=-4;

    //zobrist
    for(c=1;c<=6;c++){
        for(k=0;k<2;k++){
            for(p=0;p<64;p++){
                zobrist[c][k][p]=zobristRand64();

            }
        }
    }
    //zobrist_edn

    //mask
    for(c=0;c<64;c++){
        mask[c]=b<<c;

    }
    //mask_end
    //bitboard
    for(c=0;c<64;c++){
        switch (chess_position.pieceInSquare[c]) {
        case 1:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whitePawns|=mask[c];
            chess_position.zobrist^=zobrist[1][1][c];
            break;
        case 2:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whiteKnights|=mask[c];
            chess_position.zobrist^=zobrist[2][1][c];
            break;
        case 3:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whiteBishops|=mask[c];
            chess_position.zobrist^=zobrist[3][1][c];
            break;
        case 4:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whiteRooks|=mask[c];
            chess_position.zobrist^=zobrist[4][1][c];
            break;
        case 5:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whiteQueens|=mask[c];
            chess_position.zobrist^=zobrist[5][1][c];
            break;
        case 6:
            chess_position.pieces|=mask[c];
            chess_position.whitePieces|=mask[c];
            chess_position.whiteKings|=mask[c];
            chess_position.zobrist^=zobrist[6][1][c];
            break;
        case -1:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackPawns|=mask[c];
            chess_position.zobrist^=zobrist[1][0][c];
            break;
        case -2:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackKnights|=mask[c];
            chess_position.zobrist^=zobrist[2][0][c];
            break;
        case -3:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackBishops|=mask[c];
            chess_position.zobrist^=zobrist[3][0][c];
            break;
        case -4:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackRooks|=mask[c];
            chess_position.zobrist^=zobrist[4][0][c];
            break;
        case -5:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackQueens|=mask[c];
            chess_position.zobrist^=zobrist[5][0][c];
            break;
        case -6:
            chess_position.pieces|=mask[c];
            chess_position.blackPieces|=mask[c];
            chess_position.blackKings|=mask[c];
            chess_position.zobrist^=zobrist[6][0][c];
            break;
        default:
            break;
        }

    }
    //bitboard_end

    //Knight
    int knightsq[8] = {-17, -15, -6, 10, 17, 15, 6, -10};
    for(c = 0;c<64;c++) {
         temp = 0;
         for (k = 0; k < 8; k++) {
            p =c + knightsq[k];
            if ( (p>= 0) && (p < 64)&&((p/8-c/8)<3)&&(abs(p%8-c%8)<3)) {
              temp |= mask[p];
            }
         }
         knight[c] = temp;
    }
    //knight_end

    //king
    int kingsq[8] = {-7, -9, -8, 1, 7, 9, 8, -1};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<8;k++){
            p=c+kingsq[k];
            if((p>=0)&&(p<64)&&((p/8-c/8)<2)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        king[c]=temp;
    }
    //king_end

    //blackpawn_move
    int blackpawn_movesq[1]={-8};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<1;k++){
            p=c+blackpawn_movesq[k];
            if(p>=0&&p<64&&((p/8-c/8)<2)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        blackPawn_move[c]=temp;
    }
    //blackpawn_move_end

    //whitepawn_move
    int whitepawn_movesq[1]={8};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<1;k++){
            p=c+whitepawn_movesq[k];
            if(p>=0&&p<64&&((p/8-c/8)<2)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        whitePawn_move[c]=temp;
    }
    //whitepawn_move_end

    //blackpawn_eat
    int blackpawn_eatsq[2]={-7,-9};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<2;k++){
            p=c+blackpawn_eatsq[k];
            if(p>=0&&p<64&&((p/8-c/8)<2)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        blackPawn_eat[c]=temp;
    }
    //blackpawn_eat_end

    //whitepawn_eat
    int whitepawn_eatsq[2]={7,9};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<2;k++){
            p=c+whitepawn_eatsq[k];
            if(p>=0&&p<64&&((p/8-c/8)<2)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        whitePawn_eat[c]=temp;
    }
    //whitepawn_eat_end

    //blackpawn_firstMove
    int blackpawn_firstMovesq[2]={-8,-16};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<2;k++){
            p=c+blackpawn_firstMovesq[k];
            if(p>=0&&p<64&&((p/8-c/8)<3)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        blackPawn_firstMove[c]=temp;
    }
    //blackpawn_firstMove_end

    //whitepawn_firstMove
    int whitepawn_firstMovesq[2]={8,16};
    for(c=0;c<64;c++){
        temp=0;
        for(k=0;k<2;k++){
            p=c+whitepawn_firstMovesq[k];
            if(p>=0&&p<64&&((p/8-c/8)<3)&&(abs(p%8-c%8)<2)){
                temp|=mask[p];
            }
        }
        whitePawn_firstMove[c]=temp;
    }
    //whitepawn_firstMove_end

    //r90R_map
    k=56;
    i=1;
    for(c=0;c<64;c++){  

        r90R_map[c]=k-8*(i-1);
        if(i%8){
            i++;
        }
        else{
            i=1;
            k++;
        }

    }
    //r90R_map_end

    //_r90R_map
    k=8;
    for(c=0;c<64;c++){
        if(c%8==0){
            k--;
        }
        _r90R_map[c]=k+8*(c%8);

    }
    //_r90R_map_end


    //r45R_map
    //ur45R_map
    p=0;
    for(c=0;c<64;){
        i=length_H8A1_diag[p];
        for(k=0;k<i;k++){
            r45R_map[c]=p-k*7;
            ur45R_map[p-k*7]=c;
            c++;
        }

        if(p<56){
            p+=8;
        }
        else{
            p+=1;
        }

    }
    //r45R_map_end
    //ur45R_map_end


    //_r45R_map
    //u_r45R_map
    p=7;
    for(c=0;c<64;){
        i=length_A8H1_diag[p];
        for(k=0;k<i;k++){
            _r45R_map[c]=p+k*9;
            u_r45R_map[p+k*9]=c;
            c++;
        }

        if(p%8){
            p--;
        }
        else{
            if(p){
                p+=8;
            }
            else{
                p=8;
            }
        }

    }
    //_r45R_map_end
    //u_r45R_map_end

    //rook_rank
    BitBoard row;
    for(c=0;c<64;c++){
        p=c%8;
        for(k=0;k<256;k++){
            row=k;
            temp=0;
            b=1;
            for(i=1;i<=(7-p);i++){
                temp|=b<<(p+i);
                if((row>>(p+i))&1){
                    break;
                }
            }

            rank_attacks[c][k]=0;
            rank_attacks[c][k]|=temp<<((c/8)*8);

            int max=0;
            temp=0xff>>(8-p);
            for(i=0;i<p;i++){
                if((row>>i)&1){
                    max=i;
                }
            }
            temp^=(b<<max)-1;
            rank_attacks[c][k]|=temp<<((c/8)*8);


        }
    }
    //rook_rank_end

    //rook_file
    for(c=0;c<64;c++){
        for(k=0;k<256;k++){

            temp=0;
            b=1;
            for(i=0;i<64;i++){
                if((rank_attacks[r90R_map[c]][k]>>i)&b){
                    temp|=mask[_r90R_map[i]];
                }
            }

            file_attacks[c][k]=temp;


        }
    }
    //rook_file_end

    //bishop_diag_A8H1
    for(c=0;c<64;c++){
        int l=(b<<(length_A8H1_diag[_r45R_map[c]]))-1;

        for(i=1;((_r45R_map[c]-(9*i))>=0)&&(length_A8H1_diag[(_r45R_map[c]-(9*i))]==length_A8H1_diag[_r45R_map[c]]);i++){
        }
        p=i-1;

        for(k=0;k<=l;k++){
            row=k;
            b=1;
            diag_A8H1_attacks[_r45R_map[c]][k]=0;

            for(i=1;i<(length_A8H1_diag[_r45R_map[c]]-p);i++){
                diag_A8H1_attacks[_r45R_map[c]][k]|=mask[_r45R_map[c]+(9*i)];

                if((row>>(p+i))&1){
                    break;
                }
            }

            int max=0;
            temp=(b<<p)-1;

            for(i=0;i<p;i++){
                if((row>>i)&1){
                    max=i;
                }
            }

            temp^=(b<<max)-1;

            i=p;

            while(temp){


                if(temp&1){
                    diag_A8H1_attacks[_r45R_map[c]][k]|=mask[_r45R_map[c]-(9*i)];

                }
                temp>>=1;
                i--;
            }


        }
    }
    //bishop_diag_A8H1_end

    //bishop_diag_H8A1
    for(c=0;c<64;c++){
        int l=(b<<(length_H8A1_diag[r45R_map[c]]))-1;
        for(i=1;((r45R_map[c]+(7*i))<=63)&&(length_H8A1_diag[(r45R_map[c]+(7*i))]==length_H8A1_diag[r45R_map[c]]);i++){
        }
        p=i-1;

        for(k=0;k<=l;k++){

            row=k;
            b=1;

            diag_H8A1_attacks[r45R_map[c]][k]=0;

            for(i=1;i<(length_H8A1_diag[r45R_map[c]]-p);i++){
                diag_H8A1_attacks[r45R_map[c]][k]|=mask[r45R_map[c]-(7*i)];

                if((row>>(p+i))&1){
                    break;
                }
            }

            int max=0;
            temp=(b<<p)-1;

            for(i=0;i<p;i++){
                if((row>>i)&1){
                    max=i;
                }
            }

            temp^=(b<<max)-1;

            i=p;

            while(temp){


                if(temp&1){
                    diag_H8A1_attacks[r45R_map[c]][k]|=mask[r45R_map[c]+(7*i)];

                }
                temp>>=1;
                i--;
            }


        }
    }
    //bishop_diag_H8A1_end

    //create__r90_board
    chess_position.rotated_90=createRotated_90Board(chess_position.pieces);
    //create__r90_board_end

    //create_r45_board
    chess_position.rotated45=createRotated45Board(chess_position.pieces);
    //create_r45_board_end


    //create_r_45_board
    chess_position.rotated_45=createRotated_45Board(chess_position.pieces);
    //create_r_45_board_end

    //test
    //test_end

}
//-----------------------------------------------

//-----------------------------------------------
BitBoard Game::getSideBitBoard(bool side)
{
    if(side){
        return  chess_position.whitePieces;
    }
    else{
        return chess_position.blackPieces;
    }
}
//-----------------------------------------------
//-----------------------------------------------

BitBoard Game::randU64()
{

    return ((RAND_MAX*rand()+rand())<<34)+((RAND_MAX*rand()+rand())<<4)+(rand()&0xf);
}
//-----------------------------------------------
//-----------------------------------------------

BitBoard Game::zobristRand64()
{
    return rand()^(randU64()<<15)^(randU64()<<30)^(randU64()<<45)^(randU64()<<60);
}

void Game::check(int pieceInSquare[64], int target_position)
{
    int p=0;
    BitBoard b=1;
    int check=0;

    temp=(diag_H8A1_attacks[target_position][(((chess_position.rotated45)>>(shift_H8A1_diag[target_position]))&((b<<(length_H8A1_diag[target_position]))-1))])|(diag_A8H1_attacks[target_position][(((chess_position.rotated_45)>>(shift_A8H1_diag[target_position]))&((b<<(length_A8H1_diag[target_position]))-1))]);
    while(temp){

        if((temp&1)){
            if((pieceInSquare[p]==3)||(pieceInSquare[p]==5)){
                check=1;
                qDebug()<<"BorQcheck";
            }
        }
        p++;
        temp>>=1;
    }
    p=0;
    temp=(rank_attacks[target_position][(chess_position.pieces>>(8*(target_position/8)))&0xff])|(file_attacks[target_position][(chess_position.rotated_90>>(8*(r90R_map[target_position]/8)))&0xff]);
    while(temp){
       if(temp<0){
           break;
       }
       if((temp&1)){
           if((pieceInSquare[p]==4)||(pieceInSquare[p]==5)){
               check=1;
               qDebug()<<"RorQcheck";
           }
       }
       p++;
       temp>>=1;
   }
    p=0;
   temp=knight[target_position];

  while(temp){

      if((temp&1)){
          if((pieceInSquare[p]==2)){
              check=1;
              qDebug()<<"Ncheck";
          }
      }
      p++;
      temp>>=1;
  }
  p=0;
 temp=blackPawn_eat[target_position];


   while(temp){
       if(temp&1){
           if((pieceInSquare[p]==1)){
               check=1;
               qDebug()<<"Pcheck";
           }
       }
       p++;

       temp>>=1;

   }
   if(check){
       QMessageBox msgBox;
       msgBox.setText("Check");
       msgBox.exec();
   }
}

int Game::evaluateBoard(int pieceInSquare[])
{
    int score=0;
    for(int i=0;i<64;i++){
        if(pieceInSquare[i]>0){
            score+=pieceInSquare[i]*100;
        }
    }
        return score;
}
//-----------------------------------------------
//-----------------------------------------------
void Game::bitBoardUpdate(CHESS_POSITION *chess_position,int current_position,int target_position)
{
        //chess_position.piece
        chess_position->pieces^=mask[current_position];
        chess_position->pieces|=mask[target_position];
        //chess_position.piece_end

        //chess_position.rotated_90
        chess_position->rotated_90^=mask[r90R_map[current_position]];
        chess_position->rotated_90|=mask[r90R_map[target_position]];
        //chess_position.rotated_90_end


        //chess_position.rotated45
        chess_position->rotated45^=mask[ur45R_map[current_position]];
        chess_position->rotated45|=mask[ur45R_map[target_position]];
        //chess_position.rotated45_end


        //chess_position.rotated_45
        chess_position->rotated_45^=mask[u_r45R_map[current_position]];
        chess_position->rotated_45|=mask[u_r45R_map[target_position]];
        //chess_position.rotated_45_end
//        qDebug()<<(bool)(chess_position->pieceInSquare[current_position]&0x8);
        //side_bitboard
        if((chess_position->pieceInSquare[current_position]&0x8)){
            chess_position->blackPieces^=mask[current_position];
            chess_position->blackPieces|=mask[target_position];
            blackPieceMoveBitBoardUpdate(chess_position,current_position,target_position);
            if((chess_position->pieceInSquare[target_position])&0x7){
                chess_position->whitePieces^=mask[target_position];
                blackPieceEatBitBoardUpdate(chess_position,target_position);
            }
        }
        else{

            chess_position->whitePieces^=mask[current_position];
            chess_position->whitePieces|=mask[target_position];
            whitePieceMoveBitBoardUpdate(chess_position,current_position,target_position);
            if((chess_position->pieceInSquare[target_position])&0x7){
                chess_position->blackPieces^=mask[target_position];
                whitePieceEatBitBoardUpdate(chess_position,target_position);
            }
        }
        //side_bitboard_end
        chess_position->pieceInSquare[target_position]=chess_position->pieceInSquare[current_position];
        chess_position->pieceInSquare[current_position]=0;
}
//-----------------------------------------------

void Game::whitePieceMoveBitBoardUpdate(CHESS_POSITION *chess_position,int current_position,int target_position)
{
    switch (chess_position->pieceInSquare[current_position]) {
    case 1:
        chess_position->whitePawns^=mask[current_position];
        chess_position->whitePawns|=mask[target_position];
        chess_position->zobrist^=zobrist[1][1][current_position];
        chess_position->zobrist^=zobrist[1][1][target_position];
//        qDebug()<<bin<<zobrist[1][1][current_position];
//        qDebug()<<bin<<zobrist[1][1][target_position];
        break;
    case 2:
        chess_position->whiteKnights^=mask[current_position];
        chess_position->whiteKnights|=mask[target_position];
        chess_position->zobrist^=zobrist[2][1][current_position];
        chess_position->zobrist^=zobrist[2][1][target_position];
        break;
    case 3:
        chess_position->whiteBishops^=mask[current_position];
        chess_position->whiteBishops|=mask[target_position];
        chess_position->zobrist^=zobrist[3][1][current_position];
        chess_position->zobrist^=zobrist[3][1][target_position];
        break;
    case 4:
        chess_position->whiteRooks^=mask[current_position];
        chess_position->whiteRooks|=mask[target_position];
        chess_position->zobrist^=zobrist[4][1][current_position];
        chess_position->zobrist^=zobrist[4][1][target_position];
        break;
    case 5:
        chess_position->whiteQueens^=mask[current_position];
        chess_position->whiteQueens|=mask[target_position];
        chess_position->zobrist^=zobrist[5][1][current_position];
        chess_position->zobrist^=zobrist[5][1][target_position];
        break;
    case 6:
        chess_position->whiteKings^=mask[current_position];
        chess_position->whiteKings|=mask[target_position];
        chess_position->zobrist^=zobrist[6][1][current_position];
        chess_position->zobrist^=zobrist[6][1][target_position];
        break;
    default:
        break;
    }


}

void Game::whitePieceEatBitBoardUpdate(CHESS_POSITION *chess_position, int target_position)
{
    switch (chess_position->pieceInSquare[target_position]) {
    case -1:
        chess_position->blackPawns^=mask[target_position];
        chess_position->zobrist^=zobrist[1][0][target_position];
        chess_position->whiteScore+=100;
        break;
    case -2:
        chess_position->blackKnights^=mask[target_position];
        chess_position->zobrist^=zobrist[2][0][target_position];
        chess_position->whiteScore+=200;
        break;
    case -3:
        chess_position->blackBishops^=mask[target_position];
        chess_position->zobrist^=zobrist[3][0][target_position];
        chess_position->whiteScore+=300;
        break;
    case -4:
        chess_position->blackRooks^=mask[target_position];
        chess_position->zobrist^=zobrist[4][0][target_position];
        chess_position->whiteScore+=400;
        break;
    case -5:
        chess_position->blackQueens^=mask[target_position];
        chess_position->zobrist^=zobrist[5][0][target_position];
        chess_position->whiteScore+=500;
        break;
    case -6:
        chess_position->blackKings^=mask[target_position];
        chess_position->zobrist^=zobrist[6][0][target_position];
        chess_position->whiteScore+=5400;
        break;
    default:
        break;
    }
}

void Game::blackPieceMoveBitBoardUpdate(CHESS_POSITION *chess_position, int current_position, int target_position)
{
    switch (chess_position->pieceInSquare[current_position]) {
    case -1:        
        chess_position->blackPawns^=mask[current_position];
        chess_position->blackPawns|=mask[target_position];
        chess_position->zobrist^=zobrist[1][0][current_position];
        chess_position->zobrist^=zobrist[1][0][target_position];
        break;
    case -2:
        chess_position->blackKnights^=mask[current_position];
        chess_position->blackKnights|=mask[target_position];
        chess_position->zobrist^=zobrist[2][0][current_position];
        chess_position->zobrist^=zobrist[2][0][target_position];
        break;
    case -3:
        chess_position->blackBishops^=mask[current_position];
        chess_position->blackBishops|=mask[target_position];
        chess_position->zobrist^=zobrist[3][0][current_position];
        chess_position->zobrist^=zobrist[3][0][target_position];
        break;
    case -4:
        chess_position->blackRooks^=mask[current_position];
        chess_position->blackRooks|=mask[target_position];
        chess_position->zobrist^=zobrist[4][0][current_position];
        chess_position->zobrist^=zobrist[4][0][target_position];
        break;
    case -5:
        chess_position->blackQueens^=mask[current_position];
        chess_position->blackQueens|=mask[target_position];
        chess_position->zobrist^=zobrist[5][0][current_position];
        chess_position->zobrist^=zobrist[5][0][target_position];
        break;
    case -6:
        chess_position->blackKings^=mask[current_position];
        chess_position->blackKings|=mask[target_position];
        chess_position->zobrist^=zobrist[6][0][current_position];
        chess_position->zobrist^=zobrist[6][0][target_position];
        break;
    default:
        break;
    }
}

void Game::blackPieceEatBitBoardUpdate(CHESS_POSITION *chess_position, int target_position)
{
    switch (chess_position->pieceInSquare[target_position]) {
    case 1:
        chess_position->whitePawns^=mask[target_position];
        chess_position->zobrist^=zobrist[1][1][target_position];
        chess_position->blackScore-=100;
        break;
    case 2:
        chess_position->whiteKnights^=mask[target_position];
        chess_position->zobrist^=zobrist[2][1][target_position];
        chess_position->blackScore-=200;
        break;
    case 3:
        chess_position->whiteBishops^=mask[target_position];
        chess_position->zobrist^=zobrist[3][1][target_position];
        chess_position->blackScore-=300;
        break;
    case 4:
        chess_position->whiteRooks^=mask[target_position];
        chess_position->zobrist^=zobrist[4][1][target_position];
        chess_position->blackScore-=400;
        break;
    case 5:
        chess_position->whiteQueens^=mask[target_position];
        chess_position->zobrist^=zobrist[5][1][target_position];
        chess_position->blackScore-=500;
        break;
    case 6:
        chess_position->whiteKings^=mask[target_position];
        chess_position->zobrist^=zobrist[6][1][target_position];
        chess_position->blackScore-=5400;
        break;
    default:
        break;
    }
}

BitBoard Game::whiteBishipMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);
    p=0;
    legalMove=0;
    b=1;
    temp=(diag_H8A1_attacks[target_position][(((createRotated45Board(bitboard))>>(shift_H8A1_diag[target_position]))&((b<<(length_H8A1_diag[target_position]))-1))])|(diag_A8H1_attacks[target_position][(((createRotated_45Board(bitboard))>>(shift_A8H1_diag[target_position]))&((b<<(length_A8H1_diag[target_position]))-1))]);
    while(temp){
        if((temp&1)){
            if((pieceInSquare[p]&0x8)|!(pieceInSquare[p]&0x7)){
                legalMove|=mask[p];
            }
        }
        p++;
        temp>>=1;
    }
    return  legalMove;
}

BitBoard Game::blackBishipMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);
    p=0;
    legalMove=0;
    b=1;
    temp=(diag_H8A1_attacks[target_position][(((createRotated45Board(bitboard))>>(shift_H8A1_diag[target_position]))&((b<<(length_H8A1_diag[target_position]))-1))])|(diag_A8H1_attacks[target_position][(((createRotated_45Board(bitboard))>>(shift_A8H1_diag[target_position]))&((b<<(length_A8H1_diag[target_position]))-1))]);


    while(temp){
        if((temp&1)){
            if(!(pieceInSquare[p]&0x8)){
                legalMove|=mask[p];
            }


        }
        p++;
        temp>>=1;
    }
    return  legalMove;
}

BitBoard Game::whiteKingMove(int pieceInSquare[64], int target_position)
{
    p=0;
    temp=king[target_position];
   legalMove=0;

   while(temp){
       if((temp&1)){
           if((pieceInSquare[p]&0x8)|!(pieceInSquare[p]&0x7)){
               legalMove|=mask[p];
           }
       }
       p++;
       temp>>=1;
   }
   return  legalMove;
}

BitBoard Game::blackKingMove(int pieceInSquare[64], int target_position)
{
    p=0;
    temp=king[target_position];
   legalMove=0;

   while(temp){
       if((temp&1)){
           if(!(pieceInSquare[p]&0x8)){
               legalMove|=mask[p];
           }
       }
       p++;
       temp>>=1;
   }
   return  legalMove;
}

BitBoard Game::whiteKnightMove(int pieceInSquare[64],int target_position)
{

   p=0;
   temp=knight[target_position];
   legalMove=0;

   while(temp){
       if((temp&1)){
           if((pieceInSquare[p]&0x8)|!(pieceInSquare[p]&0x7)){
               legalMove|=mask[p];
           }
       }
       p++;
       temp>>=1;
   }
    return  legalMove;
}

BitBoard Game::blackKnightMove(int pieceInSquare[64],int target_position)
{
    p=0;
   temp=knight[target_position];
  legalMove=0;

  while(temp){
      if((temp&1)){

          if(!(pieceInSquare[p]&0x8)){
              legalMove|=mask[p];
          }
      }
      p++;
      temp>>=1;
  }
   return  legalMove;
}

BitBoard Game::blackPawnMove(int pieceInSquare[64], int target_position)
{
    p=0;

   legalMove=0;

   if((target_position>>3)^0x6){
           temp_move=blackPawn_move[target_position];
           temp_eat=blackPawn_eat[target_position];

   }
   else{
       //firstMove
       temp_move=blackPawn_firstMove[target_position];
       temp_eat=blackPawn_eat[target_position];

       if(pieceInSquare[target_position-16]){
           temp_move^=mask[target_position-16];
       }

   }
   if(pieceInSquare[target_position-8]){
      temp_move=0;
    }
   temp=temp_eat|temp_move;
   while(temp){
       if((temp_move&1)){
           legalMove|=mask[p];
       }
       if(temp_eat&1){
           if(!(pieceInSquare[p]&0x8)&(pieceInSquare[p]&0x7)){
            legalMove|=mask[p];
           }
       }
       p++;
       temp_move>>=1;
       temp_eat>>=1;
       temp=temp_move|temp_eat;
   }
   return  legalMove;
}

BitBoard Game::whitePawnMove(int pieceInSquare[64], int target_position)
{
    p=0;

   legalMove=0;

   if((target_position>>3)^0x1){
       temp_move=whitePawn_move[target_position];
       temp_eat=whitePawn_eat[target_position];
   }
   else{
        //firstMove
       temp_move=whitePawn_firstMove[target_position];
       temp_eat=whitePawn_eat[target_position];
       if(pieceInSquare[target_position+16]){
           temp_move^=mask[target_position+16];
       }
   }
   if(pieceInSquare[target_position+8]){
       temp_move=0;
   }
   temp=temp_eat|temp_move;
   while(temp){
       if((temp_move&1)){
           legalMove|=mask[p];
       }
       if(temp_eat&1){
           if((pieceInSquare[p]&0x8)){
               legalMove|=mask[p];

           }
       }
       p++;
       temp_move>>=1;
       temp_eat>>=1;
       temp=temp_move|temp_eat;

   }
   return  legalMove;
}

BitBoard Game::whiteQueenMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);

    p=0;
    b=1;
    rook_temp=(rank_attacks[target_position][(bitboard>>(8*(target_position/8)))&0xff])|(file_attacks[target_position][(createRotated_90Board(bitboard)>>(8*(r90R_map[target_position]/8)))&0xff]);
    bishop_temp=(diag_H8A1_attacks[target_position][(((createRotated45Board(bitboard))>>(shift_H8A1_diag[target_position]))&((b<<(length_H8A1_diag[target_position]))-1))])|(diag_A8H1_attacks[target_position][(((createRotated_45Board(bitboard))>>(shift_A8H1_diag[target_position]))&((b<<(length_A8H1_diag[target_position]))-1))]);
    temp=rook_temp|bishop_temp;
   legalMove=0;

   while(temp){
       if((temp&1)){
           if((pieceInSquare[p]&0x8)|!(pieceInSquare[p]&0x7)){
               legalMove|=mask[p];
           }
       }
       p++;
       temp>>=1;
   }
   return  legalMove;
}

BitBoard Game::blackQueenMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);

    p=0;
    b=1;
    rook_temp=(rank_attacks[target_position][(bitboard>>(8*(target_position/8)))&0xff])|(file_attacks[target_position][(createRotated_90Board(bitboard)>>(8*(r90R_map[target_position]/8)))&0xff]);
    bishop_temp=(diag_H8A1_attacks[target_position][(((createRotated45Board(bitboard))>>(shift_H8A1_diag[target_position]))&((b<<(length_H8A1_diag[target_position]))-1))])|(diag_A8H1_attacks[target_position][(((createRotated_45Board(bitboard))>>(shift_A8H1_diag[target_position]))&((b<<(length_A8H1_diag[target_position]))-1))]);
    temp=rook_temp|bishop_temp;
   legalMove=0;

   while(temp){
       if((temp&1)){
           if(!(pieceInSquare[p]&0x8)){
               legalMove|=mask[p];

           }
       }
       p++;
       temp>>=1;
   }
   return  legalMove;
}
BitBoard Game::whiteRookMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);
    p=0;
    temp=(rank_attacks[target_position][(bitboard>>(8*(target_position/8)))&0xff])|(file_attacks[target_position][(createRotated_90Board(bitboard)>>(8*(r90R_map[target_position]/8)))&0xff]);
   legalMove=0;

   while(temp){
       if((temp&1)){
           if((pieceInSquare[p]&0x8)|!(pieceInSquare[p]&0x7)){
               legalMove|=mask[p];
           }
       }

       p++;
       temp>>=1;
   }

   return  legalMove;
}
BitBoard Game::blackRookMove(int pieceInSquare[64], int target_position)
{
    BitBoard bitboard=pieceInSquare2BitBoard(pieceInSquare);
    p=0;
    temp=(rank_attacks[target_position][(bitboard>>(8*(target_position/8)))&0xff])|(file_attacks[target_position][(createRotated_90Board(bitboard)>>(8*(r90R_map[target_position]/8)))&0xff]);
   legalMove=0;

   while(temp){
       if((temp&1)){
           if(!(pieceInSquare[p]&0x8)){
               legalMove|=mask[p];

           }
       }

       p++;
       temp>>=1;
   }

   return  legalMove;
}

int Game::minimax(int pieceInSquare[64], int target_position,int alpha,int beta, int depth)
{
     HASHTABLE hashTable;
     for(int i=0;i<64;i++){
         if(pieceInSquare[i]){
             hashTable.zobrist^=zobrist[pieceInSquare[i]][pieceInSquare[i]&0x8][i];
         }

     }
     if(!(hashTableList.isEmpty())){
         for(TTiter=hashTableList.begin();TTiter!=hashTableList.end();TTiter++){
             if((TTiter->zobrist==hashTable.zobrist)&&(TTiter->depth==depth)){
                return TTiter->value;
             }

         }
//qDebug()<<(hashTableList.isEmpty());
//            qDebug()<<hashTableList.size();
     }
    //depth
    if(depth){
          BitBoard legalMove=0;
        //switch_category
            switch (chess_position.pieceInSquare[target_position]) {
            case 1:
                legalMove=whitePawnMove(pieceInSquare,target_position);
                break;
            case 2:
                legalMove=whiteKnightMove(pieceInSquare,target_position);
                break;
            case 3:
                legalMove=whiteBishipMove(pieceInSquare,target_position);
                break;
            case 4:
                legalMove=whiteRookMove(pieceInSquare,target_position);
                break;
            case 5:
                legalMove=whiteQueenMove(pieceInSquare,target_position);
                break;
            case 6:
                legalMove=whiteKingMove(pieceInSquare,target_position);
                break;
             case -1:
                legalMove=blackPawnMove(pieceInSquare,target_position);
                break;
            case -2:
                legalMove=blackKnightMove(pieceInSquare,target_position);
                break;
            case -3:
                legalMove=blackBishipMove(pieceInSquare,target_position);
                break;
            case -4:
                legalMove=blackRookMove(pieceInSquare,target_position);
                break;
            case -5:
                legalMove=blackQueenMove(pieceInSquare,target_position);
                break;
            case -6:
                legalMove=blackKingMove(pieceInSquare,target_position);
                break;
            default:
                legalMove=0;
                break;
            }
            //switch_category_end

            //legalMove
            int p=0;
            int pieceInSquareTemp[64];
            int score;
            bool couterpart=chess_position.pieceInSquare[target_position]&0x8;
            while(legalMove){
                if(legalMove&1){
                    //tempBoard
                    for(int i=0;i<64;i++){
                            pieceInSquareTemp[i]=pieceInSquare[i];
                    }
                    //tempBoard_end
                    //movePiecd
                    pieceInSquareTemp[p]=pieceInSquareTemp[target_position];
                    pieceInSquareTemp[target_position]=0;
                    //movePiecd_end
                    BitBoard couterpartBitBoard=getSideBitBoard(couterpart);

                    //couterpartBoard
                    int k=0;
                    int maxValue=INT_MIN;
                    while(couterpartBitBoard){
                        score=-minimax(pieceInSquareTemp,k,-beta,-alpha,depth-1);
                        if((score>maxValue)&&(rand()%2+0)){
                            maxValue=score;
                        }
                        k++;
                        couterpartBitBoard>>=1;
                    }
                    //couterpartBoard_end

                    if(maxValue>=alpha){
                        HASHTABLE h;
                        for(int i=0;i<64;i++){
                            if(pieceInSquare[i]){
                                h.zobrist^=zobrist[pieceInSquare[i]][pieceInSquare[i]&0x8][i];
                            }
                        }

                        h.depth=depth;
                        h.value=maxValue;
                        hashTableList.push_back(h);
                        bestBlackMoveTarget=p;
                        return maxValue;
                    }
                    if(maxValue>beta){

                        beta=maxValue;
                    }
                }
                legalMove>>=1;
                p++;
            }
            //legalMove_end
            return beta;
    }
    //depth_end
    else{
        int val=evaluateBoard(pieceInSquare);


        hashTable.depth=depth;
        hashTable.value=val;
        hashTableList.push_back(hashTable);
        return val;
    }
}

void Game::blackMove(int current_position,int target_position){
    pieceToMove=collection[7-(current_position>>3)][7-(current_position%8)]->currentPiece;
    ChessBox* targetBox=collection[7-(target_position>>3)][7-(target_position%8)];
    if(targetBox->getHasChessPiece()){
        targetBox->currentPiece->setIsPlaced(false);
        targetBox->currentPiece->setCurrentBox(NULL);
        removeFromScene(targetBox->currentPiece);
    }
   pieceToMove->getCurrentBox()->setHasChessPiece(false);
       pieceToMove->getCurrentBox()->currentPiece = NULL;
        pieceToMove->getCurrentBox()->resetOriginalColor();

           //placePiece
           targetBox->placePiece(pieceToMove);
           //placePiece_end
   pieceToMove=NULL;

}

BitBoard Game::pieceInSquare2BitBoard(int pieceInSquare[])
{
    int i;
    BitBoard temp=0;
    for(i=0;i<64;i++){
        if(pieceInSquare[i]&0xf){
            temp|=mask[i];
        }
    }
    return temp;
}



BitBoard Game::createRotated_90Board(BitBoard bitboard)
{
    BitBoard rotated_90Board=0;
    int i;
    b=1;
    temp=bitboard;
    for(i=0;i<64;i++){
        if(temp&b){
            rotated_90Board|=mask[r90R_map[i]];

        }
        temp>>=1;
    }
    return  rotated_90Board;
}

BitBoard Game::createRotated45Board(BitBoard bitboard)
{
    BitBoard rotated45Board=0;
    int i;
    b=1;
    temp=bitboard;
    for(i=0;i<64;i++){
        if((temp>>(r45R_map[i]))&b){
            rotated45Board|=mask[i];
        }
    }
    return rotated45Board;
}

BitBoard Game::createRotated_45Board(BitBoard bitboard)
{
    BitBoard rotated_45Board=0;
    int i;
    b=1;
    temp=bitboard;
    for(i=0;i<64;i++){
        if((temp>>(_r45R_map[i]))&b){
            rotated_45Board|=mask[i];
        }
    }
    return rotated_45Board;
}




