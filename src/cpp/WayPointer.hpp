#ifndef WAYPOINTER_H_
#define WAYPOINTER_H_

#include <KWayland/Client/connection_thread.h>
#include <KWayland/Client/registry.h>

using namespace KWayland::Client;

class WayPointer : public QObject {
  Q_OBJECT
public:
  explicit WayPointer(QObject *parent = nullptr);
  ~WayPointer() override;

  void init();

private:
  Seat *seat_;
};

#endif // WAYPOINTER_H_
