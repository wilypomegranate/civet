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
  case Qt::Key_Left:
    data.key1 = 0x50;
    break;
  case Qt::Key_Down:
    data.key1 = 0x51;
    break;
  case Qt::Key_Up:
    data.key1 = 0x52;
    break;
  case Qt::Key_Right:
    data.key1 = 0x4f;
    break;
  case Qt::Key_Delete:
    data.key1 = 0x4c;
    break;
  case Qt::Key_0:
    data.key1 = 0x27;
    break;
  case Qt::Key_ParenRight:
    data.key1 = 0x27;
    break;
  case Qt::Key_1:
    data.key1 = 0x1e;
    break;
  case Qt::Key_Exclam:
    data.key1 = 0x1e;
    break;
  case Qt::Key_2:
    data.key1 = 0x1f;
    break;
  case Qt::Key_At:
    data.key1 = 0x1f;
    break;
  case Qt::Key_3:
    data.key1 = 0x20;
    break;
  case Qt::Key_NumberSign:
    data.key1 = 0x20;
    break;
  case Qt::Key_4:
    data.key1 = 0x21;
    break;
  case Qt::Key_Dollar:
    data.key1 = 0x21;
    break;
  case Qt::Key_5:
    data.key1 = 0x22;
    break;
  case Qt::Key_Percent:
    data.key1 = 0x22;
    break;
  case Qt::Key_6:
    data.key1 = 0x23;
    break;
  case Qt::Key_AsciiCircum:
    data.key1 = 0x23;
    break;
  case Qt::Key_7:
    data.key1 = 0x24;
    break;
  case Qt::Key_Ampersand:
    data.key1 = 0x24;
    break;
  case Qt::Key_8:
    data.key1 = 0x25;
    break;
  case Qt::Key_Asterisk:
    data.key1 = 0x25;
    break;
  case Qt::Key_9:
    data.key1 = 0x26;
    break;
  case Qt::Key_ParenLeft:
    data.key1 = 0x26;
    break;
  case Qt::Key_Semicolon:
    data.key1 = 0x33;
    break;
  case Qt::Key_Colon:
    data.key1 = 0x33;
    break;
  case Qt::Key_Equal:
    data.key1 = 0x2e;
    break;
  case Qt::Key_Plus:
    data.key1 = 0x2e;
    break;
  case Qt::Key_Comma:
    data.key1 = 0x36;
    break;
  case Qt::Key_Less:
    data.key1 = 0x36;
    break;
  case Qt::Key_Minus:
    data.key1 = 0x2d;
    break;
  case Qt::Key_Underscore:
    data.key1 = 0x2d;
    break;
  case Qt::Key_Period:
    data.key1 = 0x37;
    break;
  case Qt::Key_Greater:
    data.key1 = 0x37;
    break;
  case Qt::Key_Slash:
    data.key1 = 0x38;
    break;
  case Qt::Key_Question:
    data.key1 = 0x38;
    break;
  case Qt::Key_BracketLeft:
    data.key1 = 0x2f;
    break;
  case Qt::Key_BraceLeft:
    data.key1 = 0x2f;
    break;
  case Qt::Key_BracketRight:
    data.key1 = 0x30;
    break;
  case Qt::Key_BraceRight:
    data.key1 = 0x30;
    break;
  case Qt::Key_Apostrophe:
    data.key1 = 0x34;
    break;
  case Qt::Key_QuoteDbl:
    data.key1 = 0x34;
    break;
  case Qt::Key_Backslash:
    data.key1 = 0x31;
    break;
  case Qt::Key_Bar:
    data.key1 = 0x31;
    break;
  case Qt::Key_QuoteLeft:
    data.key1 = 0x35;
    break;
  case Qt::Key_AsciiTilde:
    data.key1 = 0x35;
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
  case Qt::Key_F1:
    data.key1 = 0x3a;
    break;
  case Qt::Key_F2:
    data.key1 = 0x3b;
    break;
  case Qt::Key_F3:
    data.key1 = 0x3c;
    break;
  case Qt::Key_F4:
    data.key1 = 0x3d;
    break;
  case Qt::Key_F5:
    data.key1 = 0x3e;
    break;
  case Qt::Key_F6:
    data.key1 = 0x3f;
    break;
  case Qt::Key_F7:
    data.key1 = 0x40;
    break;
  case Qt::Key_F8:
    data.key1 = 0x41;
    break;
  case Qt::Key_F9:
    data.key1 = 0x42;
    break;
  case Qt::Key_F10:
    data.key1 = 0x43;
    break;
  case Qt::Key_F11:
    data.key1 = 0x44;
    break;
  case Qt::Key_F12:
    data.key1 = 0x45;
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
  if (modifiers & Qt::MetaModifier) {
    data.modifier |= 1 << 3;
  }

  qDebug() << "Sending " << data.key1;
  int res = socket_->write((char *)(&data), sizeof(data));
  socket_->flush();
  qDebug() << "Socket send returned " << res;
}

void KeyboardClient::releaseKey(int key, int modifiers) {
  (void)(key);
  (void)(modifiers);
  KeyboardData data = {0, 0, 0, 0, 0, 0, 0, 0};

  // Handle modifiers.
  // Only send left events since Qt is differentiating.
  // if (modifiers & Qt::ControlModifier) {
  //   data.modifier |= 1 << 0;
  // }
  // if (modifiers & Qt::ShiftModifier) {
  //   data.modifier |= 1 << 1;
  // }
  // if (modifiers & Qt::AltModifier) {
  //   data.modifier |= 1 << 2;
  // }
  // if (modifiers & Qt::MetaModifier) {
  //   data.modifier |= 1 << 3;
  // }

  qDebug() << "Releasing " << data.key1;
  int res = socket_->write((char *)(&data), sizeof(data));
  socket_->flush();
  qDebug() << "Socket send returned " << res;
}
