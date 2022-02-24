#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CursorMove.hpp"
#include "KeyboardClient.hpp"
#include "MouseClient.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("wilypomegranate");
  QCoreApplication::setApplicationName("civet");

  MouseClient *mouseClient = new MouseClient();
  KeyboardClient *keyboardClient = new KeyboardClient();
  CursorMove *cursorMove = new CursorMove();

  QGuiApplication app(argc, argv);

  QCoreApplication::addLibraryPath("./");

  QQmlApplicationEngine engine;

  QQmlContext *context = engine.rootContext();

  context->setContextProperty("_mouseClient", mouseClient);
  context->setContextProperty("_keyboardClient", keyboardClient);
  context->setContextProperty("_cursorMove", cursorMove);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
