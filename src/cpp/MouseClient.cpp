#include "MouseClient.hpp"
#include <QHostAddress>

MouseClient::MouseClient(QObject *parent)
    : QObject(parent), seqnum_(1), socket_(new QUdpSocket()), delta_(0, 0), locked_(false), server_(), port_(0), surface_(nullptr) {
  //     ct wl_display *display = static_cast<struct wl_display *>(
  //     QGuiApplication::platformNativeInterface()->nativeResourceForIntegration(
  //         "wl_display"));
  // struct wl_registry *registry = wl_display_get_registry(display);
  // wl_registry_bind(wl_registry, uint32_t name,
  //                  const struct wl_interface *interface, uint32_t version)
}

void MouseClient::sendRelativeMovement(const QSize &delta) {

  qDebug() << "Setting x: " << delta.width() << "\ty: " << delta.height();
  delta_ = delta;

  MouseData data{seqnum_, 0, static_cast<int8_t>(delta_.width()),
                 static_cast<int8_t>(delta_.height()), 0};

  socket_->writeDatagram((char *)&data, sizeof(data),
                         server_, port_);
  seqnum_++;
}

void MouseClient::sendMovement(int x, int y, bool leftClick, bool rightClick,
                               bool middleClick, int wheelDirection) {
  // qDebug() << "Sending x: " << x << "\ty: " << y << "\tleft: " << leftClick
  //          << "\tright: " << rightClick << "\twheel: " << int(wheelDirection);
  // MouseData data{seqnum_, 0, static_cast<int8_t>(x), static_cast<int8_t>(y),
  // 0};
  MouseData data{seqnum_, 0, static_cast<int8_t>(delta_.width()),
                 static_cast<int8_t>(delta_.height()), 0};
  if (leftClick) {
    data.button |= (1 << 0);
  } else {
    data.button &= ~(1 << 0);
  }
  if (rightClick) {
    data.button |= (1 << 1);
  } else {
    data.button &= ~(1 << 1);
  }
  if (middleClick) {
    data.button |= (1 << 2);
  } else {
    data.button &= ~(1 << 2);
  }

  // Set z based on wheel movement.
  if (wheelDirection == WheelDirectionClass::WHEEL_UP) {
    data.z = 0x01;
  } else if (wheelDirection == WheelDirectionClass::WHEEL_DOWN) {
    data.z = (int8_t)0xff;
  }
  qDebug() << "Wheel direction " << wheelDirection;

  socket_->writeDatagram((char *)&data, sizeof(data),
                         server_, port_);
  seqnum_++;
}

void MouseClient::setConstraints(KWayland::Client::Surface *surface, KWayland::Client::Pointer* p, KWayland::Client::PointerConstraints* pc) {
  surface_ = surface;
  p_ = p;
  pc_ = pc;
}

void MouseClient::setServer(QHostAddress server, quint16 port) {
  server_ = server;
  port_ = port;
}

void MouseClient::lockArea() {
  if (!locked_) {
    pc_->lockPointer(surface_, p_, nullptr, KWayland::Client::PointerConstraints::LifeTime::Persistent);
  locked_ = true;
  }
}
