#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "MouseClient.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("wilypomegranate");
  QCoreApplication::setApplicationName("civet");

  MouseClient *mouseClient = new MouseClient();

  QGuiApplication app(argc, argv);

  QCoreApplication::addLibraryPath("./");

  QQmlApplicationEngine engine;

  QQmlContext *context = engine.rootContext();

  context->setContextProperty("_mouseClient", mouseClient);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
