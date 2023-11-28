#include <QtWidgets>
#include <QPixmap>
#include "pieces.h"

Pieces::Pieces(QWidget *parent)
    : QLabel (parent)
{

    addPiece(QString(":/images/Imagem1.png"), 120, QPoint(10,5), QPoint(1,0), QString("Quadrado"));
    addPiece(QString(":/images/Imagem2.png"), 120, QPoint(300,20), QPoint(119,179), QString("Triângulo roxo"));
    addPiece(QString(":/images/Imagem3.png"), 120, QPoint(300,150), QPoint(60,180), QString("Triângulo azul escuro"));
    addPiece(QString(":/images/Imagem4.png"), 180, QPoint(200,5), QPoint(60,61), QString("Paralelepípedo"));
    addPiece(QString(":/images/Imagem5.png"), 170, QPoint(10,130), QPoint(119,130), QString("Triêngulo verde"));
    addPiece(QString(":/images/Imagem6.png"), 120, QPoint(150,150), QPoint(119,10), QString("Triângulo azul claro"));
    addPiece(QString(":/images/Imagem7.png"), 120, QPoint(400,150), QPoint(1,60), QString("Triângulo vermelho"));

    /*

    QLabel *imagem1 = new QLabel(this);
    imagem1->setPixmap(QPixmap(":/images/Imagem1.png").scaledToHeight(120));
    imagem1->move(10, 5);
    imagem1->show();
    imagem1->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem2 = new QLabel(this);
    imagem2->setPixmap(QPixmap(":/images/Imagem2.png").scaledToHeight(120));
    imagem2->move(300, 20);
    imagem2->show();
    imagem2->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem3 = new QLabel(this);
    imagem3->setPixmap(QPixmap(":/images/Imagem3.png").scaledToHeight(120));
    imagem3->move(300, 150);
    imagem3->show();
    imagem3->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem4 = new QLabel(this);
    imagem4->setPixmap(QPixmap(":/images/Imagem4.png").scaledToHeight(180));
    imagem4->move(200, 5);
    imagem4->show();
    imagem4->setAttribute(Qt::WA_DeleteOnClose);


    QLabel *imagem5 = new QLabel(this);
    imagem5->setPixmap(QPixmap(":/images/Imagem5.png").scaledToHeight(170));
    imagem5->move(10, 130);
    imagem5->show();
    imagem5->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem6 = new QLabel(this);
    imagem6->setPixmap(QPixmap(":/images/Imagem6.png").scaledToHeight(120));
    imagem6->move(150, 150);
    imagem6->show();
    imagem6->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem7 = new QLabel(this);
    imagem7->setPixmap(QPixmap(":/images/Imagem7.png").scaledToHeight(120));
    imagem7->move(400, 150);
    imagem7->show();
    imagem7->setAttribute(Qt::WA_DeleteOnClose);
*/
}

void Pieces::addPiece(QString name_image, int scale,  QPoint location, QPoint shadow_location, QString name_piece)
{
    Piece new_piece;
    QPixmap pixmap;
    //pixmap.load(":/images/Imagem1.png");
    pixmap.load(name_image);
    pixmap = pixmap.scaledToHeight(scale);
    //QPoint location(10,5);
    //QPoint shadow_location(1,0);
    //QString name_piece("Quadrado");

    new_piece._pixmap = pixmap;
    new_piece._location = location;
    new_piece._shadow_location = shadow_location;
    new_piece._name_piece = name_piece;

    _pieces.push_back(new_piece);
}
