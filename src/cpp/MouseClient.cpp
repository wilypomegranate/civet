#include "MouseClient.hpp"
#include <QHostAddress>
#include <QObject>
#include <QUdpSocket>

MouseClient::MouseClient(QObject *parent)
    : QObject(parent), seqnum_(1), socket_(new QUdpSocket()) {}

void MouseClient::sendMovement(int x, int y, bool leftClick) {
  qDebug() << "Sending x: " << x << "\ty: " << y;
  MouseData data{seqnum_, 0, static_cast<int8_t>(x), static_cast<int8_t>(y)};
  if (leftClick) {
    data.button = 1;
  }
  socket_->writeDatagram((char *)&data, sizeof(data),
                         QHostAddress("192.168.1.101"), 5001);
  seqnum_++;
}
