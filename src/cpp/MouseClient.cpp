#include "MouseClient.hpp"
#include <QHostAddress>

MouseClient::MouseClient(QObject *parent)
    : QObject(parent), seqnum_(1), socket_(new QUdpSocket()) {}

void MouseClient::sendMovement(int x, int y, bool leftClick, bool rightClick,
                               bool middleClick, int wheelDirection) {
  qDebug() << "Sending x: " << x << "\ty: " << y << "\tleft: " << leftClick
           << "\tright: " << rightClick << "\twheel: " << int(wheelDirection);
  MouseData data{seqnum_, 0, static_cast<int8_t>(x), static_cast<int8_t>(y), 0};
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
    data.z = 0xff;
  }
  qDebug() << "Wheel direction " << wheelDirection;

  socket_->writeDatagram((char *)&data, sizeof(data),
                         QHostAddress("192.168.1.101"), 5001);
  seqnum_++;
}
