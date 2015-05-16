#include <QCoreApplication>
#include <QThread>
/*********************************************
 *  This is a comment or something
 ********************************************/
#include "joystick.h"
#include "heartbeat.h"
#include "udppacketsender.h"

//#define JOY_DEV0 "/dev/input/js2"
//#define JOY_DEV1 "/dev/input/js1"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread js0Thread;
    QThread js1Thread;
    QThread heartbeatThread;
    QThread udpSenderThread;

    Joystick* myJS0 = new Joystick(0);
    Joystick* myJS1 = new Joystick(1);
    heartbeat* myheartbeat = new heartbeat();
    udpPacketSender* mySender = new udpPacketSender();

    myJS0->moveToThread(&js0Thread);
    myJS1->moveToThread(&js1Thread);
    myheartbeat->moveToThread(&heartbeatThread);
    mySender->moveToThread(&udpSenderThread); // Needs a thread to execute

    QObject::connect(&js0Thread,SIGNAL(started()),myJS0,SLOT(doWork()));
    QObject::connect(&js1Thread,SIGNAL(started()),myJS1,SLOT(doWork()));
    QObject::connect(&heartbeatThread,SIGNAL(started()),myheartbeat,SLOT(doWork()));
    QObject::connect(myJS0,SIGNAL(reportTelemetryUpdate(QByteArray)),mySender,SLOT(sendDatagram(QByteArray)));
    QObject::connect(myJS1,SIGNAL(reportTelemetryUpdate(QByteArray)),mySender,SLOT(sendDatagram(QByteArray)));
    QObject::connect(myheartbeat,SIGNAL(reportTelemetryUpdate(QByteArray)),mySender,SLOT(sendDatagram(QByteArray)));

    js0Thread.start();
    js1Thread.start();
    heartbeatThread.start();
    udpSenderThread.start();

    return a.exec();
}

