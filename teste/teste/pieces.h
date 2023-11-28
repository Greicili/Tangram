#ifndef PIECES_H
#define PIECES_H
#include <QLabel>
#include <QPoint>
#include <QPixmap>
#include <QVector>
#include <QWidget>

class Pieces : public QLabel
{
public:
    Pieces(QWidget *parent = nullptr);

//private:
    struct Piece {
        QPixmap _pixmap;
        QPoint _location;
        QPoint _shadow_location;
        QString _name_piece;
    };
    void addPiece(QString name_image, int scale,  QPoint location, QPoint shadow_location, QString name_piece);
    QVector<Piece> _pieces;
};

#endif // PIECES_H
