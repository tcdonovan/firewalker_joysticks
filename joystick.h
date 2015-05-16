#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <time.h>

#define JOY_DEV0 "/dev/input/js0"
#define JOY_DEV1 "/dev/input/js1"

#include <QObject>

class Joystick : public QObject
{
    Q_OBJECT
public:
    explicit Joystick(int whichJoystick, QObject *parent = 0);
    ~Joystick();

private:
    int *_axis;
    char *_button;

    int which_joystick_index;
    QString strJoystickName;
    int joy_fd, num_of_axis, num_of_buttons, x;
    char name_of_joystick[80];
    struct js_event js;

signals:
    void reportTelemetryUpdate(QByteArray);

public slots:
    void doWork();
    void doMainLoop();

};

#endif // JOYSTICK_H
