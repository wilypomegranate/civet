#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <qnamespace.h>

#include "CursorMove.hpp"
#include "KeyboardClient.hpp"
#include "MouseClient.hpp"
#include <KWayland/Client/connection_thread.h>
#include <KWayland/Client/pointer.h>
#include <KWayland/Client/pointerconstraints.h>
#include <KWayland/Client/registry.h>
#include <KWayland/Client/relativepointer.h>
#include <KWayland/Client/seat.h>
#include <KWayland/Client/surface.h>

using namespace KWayland::Client;

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("wayland"));
  QCoreApplication::setOrganizationName("wilypomegranate");
  QCoreApplication::setApplicationName("civet");

  KeyboardClient *keyboardClient = new KeyboardClient();
  CursorMove *cursorMove = new CursorMove();

  QGuiApplication app(argc, argv);

  // WayPointer wp;

  KWayland::Client::ConnectionThread *connection =
      KWayland::Client::ConnectionThread::fromApplication();

  KWayland::Client::Registry registry;
  registry.create(connection);

  KWayland::Client::Seat *seat = nullptr;
  KWayland::Client::RelativePointerManager *rpm = nullptr;
  KWayland::Client::Pointer *p = nullptr;
  KWayland::Client::PointerConstraints *pc = nullptr;
  KWayland::Client::RelativePointer *rp = nullptr;
  KWayland::Client::Surface *surface = nullptr;

  MouseClient *mouseClient = new MouseClient();

  QObject::connect(
      &registry, &KWayland::Client::Registry::interfacesAnnounced, &app,
      [&registry, &rpm, &pc, &p, &surface, &mouseClient] {
        const bool hasRelative =
            registry.hasInterface(KWayland::Client::Registry::Interface::
                                      RelativePointerManagerUnstableV1);
        if (!hasRelative) {
          qDebug() << "Relative pointer wayland interface missing"
                   << hasRelative;
          exit(1);
        }

        const bool hasPointerConstraints = registry.hasInterface(KWayland::Client::Registry::Interface::PointerConstraintsUnstableV1);
        if (!hasPointerConstraints) {
          qDebug() << "Pointer constraints wayland interface missing"
                   << hasPointerConstraints;
          exit(1);
        }

        const auto pcData = registry.interface(KWayland::Client::Registry::Interface::
                                PointerConstraintsUnstableV1);
        pc = registry.createPointerConstraints(pcData.name, pcData.version);
        mouseClient->setConstraints(surface, p, pc);

        // const auto seatData =
        // registry.interface(KWayland::Client::Registry::Interface::Seat);
        // KWayland::Client::Seat *seat =
        //     registry.createSeat(seatData.name, seatData.version);

      },
      Qt::QueuedConnection);

  QObject::connect(
      &registry, &Registry::seatAnnounced, &app,
      [&seat, &registry, &app, &rpm, &p, &rp, &mouseClient](quint32 name,
                                                            quint32 version) {
        seat = registry.createSeat(name, version);

        QObject::connect(
            seat, &Seat::hasPointerChanged, &app,
            [&registry, &seat, &app, &rpm, &p, &rp, &mouseClient](bool has) {
              if (!has) {
                return;
              }

              p = seat->createPointer(&app);
        const auto rpmData =
            registry.interface(KWayland::Client::Registry::Interface::
                                   RelativePointerManagerUnstableV1);
        rpm = registry.createRelativePointerManager(rpmData.name,
                                                    rpmData.version);
        if (rpm) {
          // rpm->createRelativePointer()
        } else {
          qDebug() << "Could not get relative pointer manager";
          exit(1);
        }
              rp = rpm->createRelativePointer(p);
              QObject::connect(
                  rp, &RelativePointer::relativeMotion, &app,
                  [&app, &rp, &mouseClient](const QSizeF &delta,
                                            const QSizeF &deltaNonAccelerated,
                                            quint64 timestamp) {
                    // qDebug() << "relative baby " << delta << " "
                    //          << deltaNonAccelerated;
                    int width = delta.width();
                    int height = delta.height();
                    mouseClient->sendRelativeMovement(QSize(width, height));
                  });
              // while (true) {
              //   rp->relativeMotion(QSizeF(1, 2), QSizeF(3, 4),
              //                      quint64(-1));
              //   qDebug() << "relative baby";
              // }
            });
      });

  registry.setup();

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

  QObject* rootObject = engine.rootObjects().first();
  if(rootObject) {
    QWindow *window = qobject_cast<QWindow *>(rootObject);
    if(window) {
      surface = KWayland::Client::Surface::fromWindow(window);
      // mouseClient->setConstraints(surface, p, pc);
      // qDebug() << mouseClient;
    }
  }

  return app.exec();
}
