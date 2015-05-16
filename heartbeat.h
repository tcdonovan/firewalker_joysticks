#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QObject>
#include <time.h>

class heartbeat : public QObject
{
    Q_OBJECT

public:
    explicit heartbeat(QObject *parent = 0);
    ~heartbeat();

private:
    struct timespec ts_delay;

signals:
    void reportTelemetryUpdate(QByteArray);

public slots:
    void doWork();
};

#endif // HEARTBEAT_H
