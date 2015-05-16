/******************************************************************************
 * UDP Packet Sender
 *
 * This broadcasts joycast telemetry and heartbeat to the Firewalker UDP Receiver.
 *
 * Modified May 2015 by Ted Donovan
 * Created 16 Feb 2015 by John Donovan for Ted Donovan (SDSM)
 *****************************************************************************/
#include "udppacketsender.h"

udpPacketSender::udpPacketSender(QObject *parent) : QObject(parent)
{
//! [0]
    udpSocket = new QUdpSocket(this);
//! [0]
    messageNo = 1;
}

udpPacketSender::~udpPacketSender()
{

}

void udpPacketSender::sendDatagram(QByteArray datagram)
{
    QHostAddress outBound;
    outBound.setAddress("151.159.37.191");
    //outBound.setAddress("151.159.37.156");
    fprintf(stdout,"Trying to send data: ");
    fprintf(stdout,"%s\n",datagram.data());
    fflush(stdout);
//! [1]
//    QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             //QHostAddress::Broadcast, SENDER_PORT);
                               outBound, SENDER_PORT);
                               //QHostAddress::LocalHost, SENDER_PORT);
//! [1]
    ++messageNo;
}

