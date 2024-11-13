#ifndef MOUSECLIENT_H_
#define MOUSECLIENT_H_

#include <QObject>
#include <QSize>
#include <QUdpSocket>
#include <KWayland/Client/surface.h>
#include <KWayland/Client/pointer.h>
#include <KWayland/Client/pointerconstraints.h>

#pragma pack(push, 1)
struct MouseData {
  uint16_t seqnum;
  uint8_t button;
  int8_t x;
  int8_t y;
  int8_t z;
};
#pragma pack(pop)

class WheelDirectionClass {
  Q_GADGET
public:
  explicit WheelDirectionClass();
  enum Value { WHEEL_NOMOVE, WHEEL_UP, WHEEL_DOWN };
  Q_ENUM(Value)
};

typedef WheelDirectionClass::Value WheelDirection;

class MouseClient : public QObject {
  Q_OBJECT

public:
  explicit MouseClient(QObject *parent = 0);
  void sendRelativeMovement(const QSize &delta);
  void setConstraints(KWayland::Client::Surface *surface, KWayland::Client::Pointer* p, KWayland::Client::PointerConstraints* pc);
  void setServer(QHostAddress server, quint16 port);

public slots:
  void sendMovement(int x, int y, bool leftClick = false,
                    bool rightClick = false, bool middleClick = false,
                    int wheelDirection = int(WheelDirection::WHEEL_NOMOVE));
  void lockArea();

private:
  uint16_t seqnum_;
  QUdpSocket *socket_;
  QSize delta_;
  bool locked_;
  QHostAddress server_;
  quint16 port_;
  KWayland::Client::Surface *surface_;
  KWayland::Client::Pointer *p_;
  KWayland::Client::PointerConstraints *pc_;
};

#endif // MOUSECLIENT_H_
