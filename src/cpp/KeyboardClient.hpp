#ifndef KEYBOARDCLIENT_H_
#define KEYBOARDCLIENT_H_

#include <QKeyEvent>
#include <QObject>
#include <QTcpSocket>

#pragma pack(push, 1)
struct KeyboardData {
  uint8_t modifier;
  uint8_t reserved;
  uint8_t key1;
  uint8_t key2;
  uint8_t key3;
  uint8_t key4;
  uint8_t key5;
  uint8_t key6;
};
#pragma pack(pop)

class KeyboardClient : public QObject {
  Q_OBJECT

public:
  explicit KeyboardClient(QObject *parent = 0);
  Q_INVOKABLE void pressKey(int key, int modifiers);
  Q_INVOKABLE void releaseKey(int key, int modifiers);

private:
  QTcpSocket *socket_;
};

#endif // KEYBOARDCLIENT_H_
