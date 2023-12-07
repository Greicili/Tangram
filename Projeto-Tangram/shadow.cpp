#include "shadow.h"

Shadow::Shadow(QString path_image, int scaleShadow, QVector<QPoint> shadow_location, QVector<int> trueIndexRotation, QWidget *parent)
    : QWidget(parent)
{
    _shadowImage.load(path_image);
    _shadowImage = _shadowImage.scaledToHeight(scaleShadow);
    _shadowLocationPieces = shadow_location;
    _trueIndexRotation = trueIndexRotation;
}
