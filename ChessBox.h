#ifndef CHESSBOX_H
#define CHESSBOX_H
#include <QGraphicsRectItem>
#include <QBrush>
#include "ChessPiece.h"
#include <QGraphicsSceneMouseEvent>
#include <QTime>


class ChessPiece;
class ChessBox:public QGraphicsRectItem
{
public:

    //Constructor
    ChessBox(QGraphicsItem *parent=0);
    ~ChessBox();


    //public member function
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(ChessPiece *piece);


    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = 0);

    void checkForCheck();

    QString getChessPieceColor() ;
    void setChessPieceColor(QString value);

    int rowLoc;
    int colLoc;

    ChessPiece * currentPiece;

    bool hasChessPiece;
    QTime time;
private:
    QBrush brush;
    QColor originalColor;

    QString chessPieceColor;


};
#endif // CHESSBOX_H
