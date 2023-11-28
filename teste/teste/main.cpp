#include <QApplication>
#include <QHBoxLayout>

#include "dragwidget.h"
#include "sombra.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(pieces);

    QApplication app(argc, argv);

    QWidget mainWidget;
    mainWidget.setFixedSize(1000,320);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->addWidget(new DragWidget);
    horizontalLayout->addWidget(new Sombra);

    mainWidget.setWindowTitle(QObject::tr("Jogo - Tangram"));
    mainWidget.show();

    return app.exec();
}
