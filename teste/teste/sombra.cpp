/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "sombra.h"
#include "pieces.h"
#include <iostream>

using namespace std;

//! [0]
Sombra::Sombra(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true); // controla poder movimentar as peças
    setFixedSize(360,300);

    QPixmap bkgnd(":/images/sombra.png");  //Load pic
    bkgnd = bkgnd.scaledToHeight(300);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);//set the pic to the background
    setPalette(palette);
    setAutoFillBackground(true);

    //connect(this, SIGNAL(puzzleCompleted()), this,  SLOT(setComplete()));
}
//! [0]

void Sombra::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Sombra::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Sombra::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        cout << "x =" << newIcon->x();
        cout << " y =" << newIcon->y() << "\n" << endl;

        for(int i = 0; i <7; i++){
            if(newIcon->pixmap()->toImage() == _p._pieces[i]._pixmap.toImage()){
                _p._pieces[i]._location = newIcon->pos();
                break;
            }
        }

        checkPosition();

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }

}


void Sombra::checkPosition(){
    if ((_p._pieces[0]._location.y() > _p._pieces[0]._shadow_location.y() - 5) && (_p._pieces[0]._location.y() < _p._pieces[0]._shadow_location.y() + 5) && (_p._pieces[0]._location.x() > _p._pieces[0]._shadow_location.x() - 5) && (_p._pieces[0]._location.x() < _p._pieces[0]._shadow_location.x() + 5)){
       if ((_p._pieces[1]._location.y() > _p._pieces[1]._shadow_location.y() - 5) && (_p._pieces[1]._location.y() < _p._pieces[1]._shadow_location.y() + 5) && (_p._pieces[1]._location.x() > _p._pieces[1]._shadow_location.x() - 5) && (_p._pieces[1]._location.x() < _p._pieces[1]._shadow_location.x() + 5)){
            if ((_p._pieces[2]._location.y() > _p._pieces[2]._shadow_location.y() - 5) && (_p._pieces[2]._location.y() < _p._pieces[2]._shadow_location.y() + 5) && (_p._pieces[2]._location.x() > _p._pieces[2]._shadow_location.x() - 5) && (_p._pieces[2]._location.x() < _p._pieces[2]._shadow_location.x() + 5)){
                if ((_p._pieces[3]._location.y() > _p._pieces[3]._shadow_location.y() - 5) && (_p._pieces[3]._location.y() < _p._pieces[3]._shadow_location.y() + 5) && (_p._pieces[3]._location.x() > _p._pieces[3]._shadow_location.x() - 5) && (_p._pieces[3]._location.x() < _p._pieces[3]._shadow_location.x() + 5)){
                    if ((_p._pieces[4]._location.y() > _p._pieces[4]._shadow_location.y() - 5) && (_p._pieces[4]._location.y() < _p._pieces[4]._shadow_location.y() + 5) && (_p._pieces[4]._location.x() > _p._pieces[4]._shadow_location.x() - 5) && (_p._pieces[4]._location.x() < _p._pieces[4]._shadow_location.x() + 5)){
                        if ((_p._pieces[5]._location.y() > _p._pieces[5]._shadow_location.y() - 5) && (_p._pieces[5]._location.y() < _p._pieces[5]._shadow_location.y() + 5) && (_p._pieces[5]._location.x() > _p._pieces[5]._shadow_location.x() - 5) && (_p._pieces[5]._location.x() < _p._pieces[5]._shadow_location.x() + 5)){
                            if ((_p._pieces[6]._location.y() > _p._pieces[6]._shadow_location.y() - 5) && (_p._pieces[6]._location.y() < _p._pieces[6]._shadow_location.y() + 5) && (_p._pieces[6]._location.x() > _p._pieces[6]._shadow_location.x() - 5) && (_p._pieces[6]._location.x() < _p._pieces[6]._shadow_location.x() + 5)){
                                //emit puzzleCompleted();
                                 cout << "Jogo finalizado" << endl;

                            }
                        }
                    }
                }
            }
        }
    }
}

void Sombra::setCompleted(){
    cout << "Jogo finalizado" << endl;
}

//! [1]
void Sombra::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
    //! [1]

    //! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    //! [2]

    //! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
    //! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
