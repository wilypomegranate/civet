#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <KWayland/Client/connection_thread.h>
#include <KWayland/Client/registry.h>

#include "CursorMove.hpp"
#include "KeyboardClient.hpp"
#include "MouseClient.hpp"

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("wayland"));
  QCoreApplication::setOrganizationName("wilypomegranate");
  QCoreApplication::setApplicationName("civet");

  MouseClient *mouseClient = new MouseClient();
  KeyboardClient *keyboardClient = new KeyboardClient();
  CursorMove *cursorMove = new CursorMove();

  QGuiApplication app(argc, argv);

  KWayland::Client::ConnectionThread *connection =
      KWayland::Client::ConnectionThread::fromApplication();

  KWayland::Client::Registry registry;
  registry.create(connection);

  QObject::connect(
      &registry, &KWayland::Client::Registry::interfacesAnnounced, &app,
      [&registry] {
        const bool hasRelative =
            registry.hasInterface(KWayland::Client::Registry::Interface::
                                      RelativePointerManagerUnstableV1);
        qDebug() << "has relative " << hasRelative;
        exit(1);
      },
      Qt::QueuedConnection);

  QCoreApplication::addLibraryPath("./");

  QQmlApplicationEngine engine;

  QQmlContext *context = engine.rootContext();

  context->setContextProperty("_mouseClient", mouseClient);
  context->setContextProperty("_keyboardClient", keyboardClient);
  context->setContextProperty("_cursorMove", cursorMove);

  qmlRegisterUncreatableType<WheelDirectionClass>(
      "civet.wheeldirection", 1, 0, "WheelDirection",
      "Not creatable as it is an enum type.");

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
