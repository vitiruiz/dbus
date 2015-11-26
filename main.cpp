#include <QApplication>
#include <QQmlApplicationEngine>

#include <QtDBus>

#include <QDebug>

#include "a2dpsource.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    A2DPSourceThread source;
    source.start();





    return app.exec();
}
