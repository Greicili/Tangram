#include "piece.h"

Piece::Piece(QVector<QString> path_images, int numRotation, int scale,  QPoint location, QWidget *parent)
: QLabel (parent)
{
    QPixmap pieceImage;
    for(int i = 0; i < numRotation; i++){
        pieceImage.load(path_images[i]);
        pieceImage = pieceImage.scaledToHeight(scale);
        _piece.push_back(pieceImage);
    }
    _numRotation = numRotation;
    _location = location;
    _correctPosition = false;
    _indexPieceRotation = 0;
}
