#ifndef JS0_H
#define JS0_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <QObject>
#include <time.h>

#define JOY_DEV0 "/dev/input/js0"

class JS0 : public QObject
{
    Q_OBJECT
public:
    explicit JS0(QObject *parent = 0);
    ~JS0();


private:
    int *_axis;
    char *_button;

    int joy_fd0, num_of_axis, num_of_buttons, x;
    char name_of_joystick[80];
    struct js_event js;
    //void readStick0();

signals:

public slots:
    void doWork0();
    void doMainLoop();
};

#endif // JS0_H
