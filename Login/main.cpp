#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlContext>


#include "loginbox.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    LoginBox access;

    engine.rootContext()->setContextProperty("access", &access);
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    component.create();

    return app.exec();
}
