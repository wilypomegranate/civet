#include "WayPointer.hpp"

#include <QDebug>

WayPointer::WayPointer(QObject *parent) : QObject(parent) {

  KWayland::Client::ConnectionThread *connection =
      KWayland::Client::ConnectionThread::fromApplication();

  KWayland::Client::Registry registry;
  registry.create(connection);
  qDebug() << "here2";

  QObject::connect(
      &registry, &Registry::interfacesAnnounced, parent,
      [&registry, parent] {
        const bool hasRelative =
            registry.hasInterface(KWayland::Client::Registry::Interface::
                                      RelativePointerManagerUnstableV1);
        if (!hasRelative) {
          qDebug() << "Relative pointer wayland interface missing"
                   << hasRelative;
          exit(1);
        }
        qDebug() << "here";
      },
      Qt::QueuedConnection);

  // QObject::connect(
  //     &registry, &KWayland::Client::Registry::interfacesAnnounced, &app,
  //     [&registry] {
  //       const bool hasRelative =
  //           registry.hasInterface(KWayland::Client::Registry::Interface::
  //                                     RelativePointerManagerUnstableV1);
  //       if (!hasRelative) {
  //         qDebug() << "Relative pointer wayland interface missing"
  //                  << hasRelative;
  //         exit(1);
  //       }
  registry.setup();
}

void WayPointer::init() {}

WayPointer::~WayPointer() {}
