#ifndef MOUSECLIENT_H_
#define MOUSECLIENT_H_

#include <QObject>
#include <QUdpSocket>

#pragma pack(push, 1)
struct MouseData {
    uint16_t seqnum;
    uint8_t button;
    int8_t x;
    int8_t y;
};
#pragma pack(pop)

class MouseClient : public QObject {
        Q_OBJECT

        public:
        explicit MouseClient(QObject *parent = 0);
        Q_INVOKABLE void sendMovement(int x, int y);

        private:
          uint16_t seqnum_;
          QUdpSocket* socket_;

};

#endif // MOUSECLIENT_H_
