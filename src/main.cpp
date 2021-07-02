#include <QApplication>
#include <QQmlApplicationEngine>
#include "backend.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<BackEnd>("src.backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc://⁄src/main.qml")));
    return app.exec();
}
