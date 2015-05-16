/******************************************************************************
 * UDP Packet Sender
 *
 * This broadcasts joycast telemetry and heartbeat to the Firewalker UDP Receiver.
 *
 * Modified May 2015 by Ted Donovan
 * Created 16 Feb 2015 by John Donovan for Ted Donovan (SDSM)
 *****************************************************************************/
#ifndef UDPPACKETSENDER_H
#define UDPPACKETSENDER_H

#include <QObject>
#include <QUdpSocket>

#define SENDER_PORT 6000

class udpPacketSender : public QObject
{
    Q_OBJECT
public:
    explicit udpPacketSender(QObject *parent = 0);
    ~udpPacketSender();

private:
    QUdpSocket* udpSocket;
    int messageNo;

signals:

public slots:
    void sendDatagram(QByteArray datagram);

};

#endif // UDPPACKETSENDER_H
