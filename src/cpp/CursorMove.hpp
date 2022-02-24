#ifndef CURSORMOVE_H_
#define CURSORMOVE_H_

#include <QObject>
#include <QCursor>

class CursorMove : public QObject {
  Q_OBJECT

  public:
    explicit CursorMove(QObject *parent = 0);

  public slots:
        void moveCursor(QPointF p);
};

#endif // CURSORMOVE_H_
