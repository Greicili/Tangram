#include "tangram.h"
#include "dragwidget.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QObjectCleanupHandler>
#include <QCoreApplication>

#include <QFrame>
#include <QLabel>

#include <iostream>
using namespace std;

Tangram::Tangram(QWidget *parent)
    : QWidget (parent)
{
    setFixedSize(1000,320);
    setStyleSheet("font-size: 15px;");

    //setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Jogo - Tangram"));

    //inicial_window();
    game_window();
}

void Tangram::inicial_window(){
    QGroupBox *group_buttons = new QGroupBox();
    QGridLayout *grid_Layout = new QGridLayout(this);

    QPushButton *btn_iniciar = new QPushButton("INICIAR JOGO");
    connect(btn_iniciar, SIGNAL(clicked()), this, SLOT(game_window()));

    QPushButton *btn = new QPushButton("SAIR");
    btn->setFixedWidth(300);
    btn_iniciar->setFixedWidth(300);
    grid_Layout->addWidget(btn_iniciar,0,0);
    grid_Layout->addWidget(btn,1,0);
    group_buttons->setFixedHeight(80);
    group_buttons->setLayout(grid_Layout);

    QLabel *logo = new QLabel();
    logo->setPixmap(QPixmap(":/image/inicial_imagem.png").scaledToHeight(250));
    logo->setFixedHeight(250);

   QVBoxLayout *horizontal_Layout = new QVBoxLayout(this);

   horizontal_Layout->setSpacing(0);
   horizontal_Layout->setContentsMargins(10,10,10,10);
   horizontal_Layout->addWidget(logo,0, Qt::AlignCenter);
   horizontal_Layout->addWidget(group_buttons,0,Qt::AlignCenter);

   horizontal_Layout->addItem(new QSpacerItem(0,20));
   setLayout(horizontal_Layout);

}
void Tangram::game_window(){
   QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
   horizontalLayout->addWidget(_frame0);
   horizontalLayout->addWidget(_frame1);
   connect(_frame1, SIGNAL(puzzleCompleted()), this, SLOT(setCompleted()));
   setLayout(horizontalLayout);
}


void Tangram::setCompleted(){
   cout << "Fim de jogo\n" << endl;
}


