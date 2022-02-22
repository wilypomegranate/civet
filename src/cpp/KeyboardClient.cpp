#include "KeyboardClient.hpp"

KeyboardClient::KeyboardClient(QObject *parent)
    : QObject(parent), socket_(new QTcpSocket) {
  socket_->connectToHost("127.0.0.1", 5002);
  if (!socket_->waitForConnected(1000)) {
    qDebug() << "Error: " << socket_->errorString();
  }
}

void KeyboardClient::pressKey(int key, int modifiers) {
  KeyboardData data = {0, 0, 0, 0, 0, 0, 0, 0};
  QKeyEvent event(QEvent::Type::KeyPress, key, Qt::KeyboardModifiers(modifiers),
                  QKeySequence(key).toString());
  switch (event.key()) {
  case Qt::Key_Backspace:
    data.key1 = 0x2a;
    break;
  case Qt::Key_Tab:
    data.key1 = 0x2b;
    break;
  case Qt::Key_Return:
    data.key1 = 0x28;
    break;
  case Qt::Key_Escape:
    data.key1 = 0x29;
    break;
  case Qt::Key_Space:
    data.key1 = 0x2c;
    break;
  case Qt::Key_PageUp:
    data.key1 = 0x4b;
    break;
  case Qt::Key_PageDown:
    data.key1 = 0x4e;
    break;
  case Qt::Key_0:
    data.key1 = 0x27;
    break;
  case Qt::Key_1:
    data.key1 = 0x1e;
    break;
  case Qt::Key_2:
    data.key1 = 0x1f;
    break;
  case Qt::Key_3:
    data.key1 = 0x20;
    break;
  case Qt::Key_4:
    data.key1 = 0x21;
    break;
  case Qt::Key_5:
    data.key1 = 0x22;
    break;
  case Qt::Key_6:
    data.key1 = 0x23;
    break;
  case Qt::Key_7:
    data.key1 = 0x24;
    break;
  case Qt::Key_8:
    data.key1 = 0x25;
    break;
  case Qt::Key_9:
    data.key1 = 0x26;
    break;
  case Qt::Key_Semicolon:
    data.key1 = 0x33;
    break;
  case Qt::Key_Less:
    data.key1 = 0xc5;
    break;
  case Qt::Key_Equal:
    data.key1 = 0x23;
    break;
  case Qt::Key_Comma:
    data.key1 = 0x36;
    break;
  case Qt::Key_Minus:
    data.key1 = 0x2d;
    break;
  case Qt::Key_Period:
    data.key1 = 0x37;
    break;
  case Qt::Key_Slash:
    data.key1 = 0x38;
    break;
  case Qt::Key_BracketLeft:
    data.key1 = 0x2f;
    break;
  case Qt::Key_BracketRight:
    data.key1 = 0x30;
    break;
  case Qt::Key_QuoteLeft:
    data.key1 = 0x34;
    break;
  case Qt::Key_Backslash:
    data.key1 = 0x31;
    break;
  case Qt::Key_A:
    data.key1 = 0x04;
    break;
  case Qt::Key_B:
    data.key1 = 0x05;
    break;
  case Qt::Key_C:
    data.key1 = 0x06;
    break;
  case Qt::Key_D:
    data.key1 = 0x07;
    break;
  case Qt::Key_E:
    data.key1 = 0x08;
    break;
  case Qt::Key_F:
    data.key1 = 0x09;
    break;
  case Qt::Key_G:
    data.key1 = 0x0a;
    break;
  case Qt::Key_H:
    data.key1 = 0x0b;
    break;
  case Qt::Key_I:
    data.key1 = 0x0c;
    break;
  case Qt::Key_J:
    data.key1 = 0x0d;
    break;
  case Qt::Key_K:
    data.key1 = 0x0e;
    break;
  case Qt::Key_L:
    data.key1 = 0x0f;
    break;
  case Qt::Key_M:
    data.key1 = 0x10;
    break;
  case Qt::Key_N:
    data.key1 = 0x11;
    break;
  case Qt::Key_O:
    data.key1 = 0x12;
    break;
  case Qt::Key_P:
    data.key1 = 0x13;
    break;
  case Qt::Key_Q:
    data.key1 = 0x14;
    break;
  case Qt::Key_R:
    data.key1 = 0x15;
    break;
  case Qt::Key_S:
    data.key1 = 0x16;
    break;
  case Qt::Key_T:
    data.key1 = 0x17;
    break;
  case Qt::Key_U:
    data.key1 = 0x18;
    break;
  case Qt::Key_V:
    data.key1 = 0x19;
    break;
  case Qt::Key_W:
    data.key1 = 0x1a;
    break;
  case Qt::Key_X:
    data.key1 = 0x1b;
    break;
  case Qt::Key_Y:
    data.key1 = 0x1c;
    break;
  case Qt::Key_Z:
    data.key1 = 0x1d;
    break;
  default:
    // If no key defined just return and do nothing for now.
    break;
  }

  // Handle modifiers.
  // Only send left events since Qt is differentiating.
  if (modifiers & Qt::ControlModifier) {
    data.modifier |= 1 << 0;
  }
  if (modifiers & Qt::ShiftModifier) {
    data.modifier |= 1 << 1;
  }
  if (modifiers & Qt::AltModifier) {
    data.modifier |= 1 << 2;
  }

  qDebug() << "Sending " << data.key1;
  int res = socket_->write((char *)(&data), sizeof(data));
  socket_->flush();
  qDebug() << "Socket send returned " << res;
}

void KeyboardClient::releaseKey(int key, int modifiers) {
  KeyboardData data = {0, 0, 0, 0, 0, 0, 0, 0};

  // Handle modifiers.
  // Only send left events since Qt is differentiating.
  if (modifiers & Qt::ControlModifier) {
    data.modifier |= 1 << 0;
  }
  if (modifiers & Qt::ShiftModifier) {
    data.modifier |= 1 << 1;
  }
  if (modifiers & Qt::AltModifier) {
    data.modifier |= 1 << 2;
  }

  qDebug() << "Releasing " << data.key1;
  int res = socket_->write((char *)(&data), sizeof(data));
  socket_->flush();
  qDebug() << "Socket send returned " << res;
}
