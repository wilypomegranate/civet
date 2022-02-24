#include "CursorMove.hpp"

CursorMove::CursorMove(QObject *parent) : QObject(parent) {}

void CursorMove::moveCursor(QPointF p) { QCursor::setPos(p.x(), p.y()); }
