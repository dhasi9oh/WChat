#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QDirIterator>
#include <QDebug>

#include "Def.h"
#include "tcpmgr.h"
#include "usrmgr.h"
#include "httpmgr.h"
#include "msgrectangle.h"

QObject* TcpMgrSingleton(QQmlEngine*, QJSEngine*) {
    return TcpMgr::Instance();
}

QObject* HttpMgrSingleton(QQmlEngine*, QJSEngine*) {
    return HttpMgr::Instance();
}

QObject* UsrMgrSingleton(QQmlEngine*, QJSEngine*) {
    return UsrMgr::Instance();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MsgRectangle>("MsgControls", 1, 0, "MsgRectangle");
    qmlRegisterSingletonType<TcpMgr>("UsrMgr", 1, 0, "UsrMgr", UsrMgrSingleton);
    qmlRegisterSingletonType<TcpMgr>("TcpMgr", 1, 0, "TcpMgr", TcpMgrSingleton);
    qmlRegisterSingletonType<HttpMgr>("HttpMgr", 1, 0, "HttpMgr", HttpMgrSingleton);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/InitWindow.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
