#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <ChessBoard.h>
#include "ChessPiece.h"
typedef unsigned long long BitBoard;
typedef struct CHESS_POSITION CHESS_POSITION;
typedef struct HASHTABLE HASHTABLE;
struct CHESS_POSITION {
    CHESS_POSITION(){}
    //BitBoard transrefkey;
    int pieceInSquare[64];
    //int player;
    //int epsquare;
    //int castles;
    //int imbalance;
    //int wkingsq;
    //int bkingsq;
    int whiteScore;
    int blackScore;
    int current_position;
    int target_position;
    BitBoard zobrist;

    BitBoard whitePawns;
    BitBoard blackPawns;
    BitBoard whiteKnights;
    BitBoard blackKnights;
    BitBoard bishopsQueens;
    BitBoard rooksQueens;
    BitBoard whiteBishops;
    BitBoard blackBishops;
    BitBoard whiteRooks;
    BitBoard blackRooks;
    BitBoard whiteQueens;
    BitBoard blackQueens;
    BitBoard whiteKings;
    BitBoard blackKings;
    BitBoard pieces;
    BitBoard whitePieces;
    BitBoard blackPieces;

    BitBoard rotated90;
    BitBoard rotated_90;
    BitBoard rotated45;
    BitBoard rotated_45;
    BitBoard rotated315;


};

struct HASHTABLE
{
    HASHTABLE() {}
    BitBoard zobrist;
    int depth;
    int value;
};
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = 0);

    ChessPiece *pieceToMove;
    ChessBox *collection[8][8];
    CHESS_POSITION chess_position;
    QList <HASHTABLE> hashTableList;
    QList <HASHTABLE>::iterator TTiter;
    //public Methods
    void drawChessBoard();
    void addChessPiece();    
    void placeInDeadPlace(ChessPiece *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);
    void initializeChessPieceMoveBoards();

    //getters/setters

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();
    void blackMove(int current_position,int target_position);

    void gameOver();
    void removeAll();


    BitBoard mask[64];
    BitBoard knight[64];
    BitBoard king[64];
    BitBoard blackPawn_move[64];
    BitBoard whitePawn_move[64];
    BitBoard blackPawn_eat[64];
    BitBoard whitePawn_eat[64];
    BitBoard blackPawn_firstMove[64];
    BitBoard whitePawn_firstMove[64];
    BitBoard rank_attacks[64][256];
    BitBoard file_attacks[64][256];
    BitBoard diag_A8H1_attacks[64][256];
    BitBoard diag_H8A1_attacks[64][256];

    BitBoard rook[64][256];
    BitBoard bishop[64][256];
    int r90R_map[64];
    int _r90R_map[64];
    int r45R_map[64];
    int _r45R_map[64];
    int ur45R_map[64];
    int u_r45R_map[64];

    //length_A8H1_diag
    int length_A8H1_diag[64] = {
     8, 7, 6, 5, 4, 3, 2, 1,
     7, 8, 7, 6, 5, 4, 3, 2,
     6, 7, 8, 7, 6, 5, 4, 3,
     5, 6, 7, 8, 7, 6, 5, 4,
     4, 5, 6, 7, 8, 7, 6, 5,
     3, 4, 5, 6, 7, 8, 7, 6,
     2, 3, 4, 5, 6, 7, 8, 7,
     1, 2, 3, 4, 5, 6, 7, 8
    };
    //length_A8H1_diag_end

    //length_H8A1_diag
    int length_H8A1_diag[64] = {
     1, 2, 3, 4, 5, 6, 7, 8,
     2, 3, 4, 5, 6, 7, 8, 7,
     3, 4, 5, 6, 7, 8, 7, 6,
     4, 5, 6, 7, 8, 7, 6, 5,
     5, 6, 7, 8, 7, 6, 5, 4,
     6, 7, 8, 7, 6, 5, 4, 3,
     7, 8, 7, 6, 5, 4, 3, 2,
     8, 7, 6, 5, 4, 3, 2, 1
    };
    //length_H8A1_diag_end

    //shift_A8H1_diag
    int shift_A8H1_diag[64]={
        28, 21, 15, 10, 6, 3, 1, 0,
        36, 28, 21, 15, 10, 6, 3, 1,
        43, 36, 28, 21, 15, 10, 6, 3,
        49, 43, 36, 28, 21, 15, 10, 6,
        54, 49, 43, 36, 28, 21, 15, 10,
        58, 54, 49, 43, 36, 28, 21, 15,
        61, 58, 54, 49, 43, 36, 28, 21,
        63, 61, 58, 54, 49, 43, 36, 28
    };
    //shift_A8H1_diag_end

    //shift_H8A1_diag
    int shift_H8A1_diag[64]={
        0, 1, 3, 6, 10, 15, 21, 28,
        1, 3, 6, 10, 15, 21, 28, 36,
        3, 6, 10, 15, 21, 28, 36, 43,
        6, 10, 15, 21, 28, 36, 43, 49,
        10, 15, 21, 28, 36, 43, 49, 54,
        15, 21, 28, 36, 43, 49, 54, 58,
        21, 28, 36, 43, 49, 54, 58, 61,
        28, 36, 43,	49,	54,	58,	61,	63
    };
    //shift_H8A1_diag_end
    BitBoard pieceInSquare2BitBoard(int pieceInSquare[64]);
    BitBoard createRotated_90Board(BitBoard bitboard);
    BitBoard createRotated45Board(BitBoard bitboard);
    BitBoard createRotated_45Board(BitBoard bitboard);
    BitBoard getSideBitBoard(bool side);

    void bitBoardUpdate(CHESS_POSITION *chess_position,int current_position,int target_position);    
    void whitePieceMoveBitBoardUpdate(CHESS_POSITION *chess_position,int current_position,int target_position);
    void whitePieceEatBitBoardUpdate(CHESS_POSITION *chess_position,int target_position);

    void blackPieceMoveBitBoardUpdate(CHESS_POSITION *chess_position,int current_position,int target_position);
    void blackPieceEatBitBoardUpdate(CHESS_POSITION *chess_position,int target_position);

        BitBoard whiteBishipMove(int pieceInSquare[64],int target_position);
        BitBoard blackBishipMove(int pieceInSquare[64],int target_position);
        BitBoard whiteKingMove(int pieceInSquare[64],int target_position);
        BitBoard blackKingMove(int pieceInSquare[64],int target_position);
        BitBoard whiteKnightMove(int pieceInSquare[64],int target_position);
        BitBoard blackKnightMove(int pieceInSquare[64],int target_position);
        BitBoard whitePawnMove(int pieceInSquare[64],int target_position);
        BitBoard blackPawnMove(int pieceInSquare[64],int target_position);
        BitBoard whiteQueenMove(int pieceInSquare[64],int target_position);
        BitBoard blackQueenMove(int pieceInSquare[64],int target_position);
        BitBoard whiteRookMove(int pieceInSquare[64],int target_position);
        BitBoard blackRookMove(int pieceInSquare[64],int target_position);


    int minimax(int pieceInSquare[64],int target_position,int alpha,int beta,int depth);
    void check(int pieceInSquare[], int target_position);
    int evaluateBoard(int pieceInSquare[64]);

    BitBoard randU64(void);
    BitBoard zobristRand64(void);
    BitBoard zobrist[7][2][64];


    int bestBlackMoveCurrent;
    int bestBlackMoveTarget;

private:
    QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;    
    QString turn;
    ChessBoard *chessBoard;
    QList <QGraphicsItem *> listG;

    /////
    int p;
    BitBoard b;
    BitBoard legalMove;
    BitBoard temp;
    BitBoard rook_temp;
    BitBoard bishop_temp;
    BitBoard temp_eat;
    BitBoard temp_move;

//    CHESS_POSITION bestChessPosition;

};


#endif // GAME_H
