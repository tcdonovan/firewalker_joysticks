#include "heartbeat.h"

heartbeat::heartbeat(QObject *parent) : QObject(parent)
{
    struct timespec ts = {0,250000000.};
    ts_delay = ts;
}

heartbeat::~heartbeat()
{

}

void heartbeat::doWork()
{

    QByteArray heartstring("lubdub");
    emit reportTelemetryUpdate(heartstring);
    nanosleep(&ts_delay,NULL);

    QMetaObject::invokeMethod(this, "doWork", Qt::QueuedConnection);
}
