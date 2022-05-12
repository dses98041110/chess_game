#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QtWidgets>


class Piece: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(QString team="" ,QGraphicsItem * parent=0);
    QPixmap pix;
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;
    QString side;


    bool dragOver = false;
private:
    void execDrag();
    QPoint startPoint;
};

#endif // PIECE_H
