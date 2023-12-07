#ifndef PIECE_H
#define PIECE_H

#include <QtWidgets>

class Piece: public QLabel
{
public:
    Piece(QVector<QString> path_images, int numRotation, int scale,  QPoint location, QWidget *parent = nullptr);
    void setLocation(QPoint loc){_location = loc;}
    QPoint getLocation(){return _location;}

    void indexPieceRotation(int value){_indexPieceRotation = value;}
    int indexPieceRotation(){return _indexPieceRotation;}

    void correctPosition(bool value){_correctPosition = value;}
    bool correctPosition(){return _correctPosition;}

    QPixmap pieceImage(int index){return _piece[index];}
    int numRotation(){return _numRotation;}

private:
    QVector<QPixmap> _piece;
    QPoint _location;
    bool _correctPosition;
    int _indexPieceRotation;
    int _numRotation;
};

#endif // PIECE_H
