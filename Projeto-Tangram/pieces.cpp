#include <QtWidgets>
#include <QPixmap>
#include "pieces.h"

Pieces::Pieces(QWidget *parent)
    : QLabel (parent)
{

    addPiece(QString(":/images/Imagem1.png"), 120, QPoint(10,5), QPoint(1,0));
    addPiece(QString(":/images/Imagem2.png"), 120, QPoint(300,20), QPoint(119,179));
    addPiece(QString(":/images/Imagem3.png"), 120, QPoint(300,150), QPoint(60,180));
    addPiece(QString(":/images/Imagem4.png"), 180, QPoint(200,5), QPoint(60,61));
    addPiece(QString(":/images/Imagem5.png"), 170, QPoint(10,130), QPoint(119,130));
    addPiece(QString(":/images/Imagem6.png"), 120, QPoint(150,150), QPoint(119,10));
    addPiece(QString(":/images/Imagem7.png"), 120, QPoint(400,150), QPoint(1,60));

}


