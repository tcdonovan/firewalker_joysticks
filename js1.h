#ifndef JS1_H
#define JS1_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <QObject>
#include <time.h>

#define JOY_DEV1 "/dev/input/js1"


class JS1 : public QObject
{
    Q_OBJECT
public:
    explicit JS1(QObject *parent = 0);
    ~JS1();

private:
    int *_axis;
    char *_button;

    int joy_fd0, num_of_axis, num_of_buttons, x;
    char name_of_joystick[80];
    struct js_event js;
    //void readStick1();

signals:

public slots:
    void doWork1();
    void doMainLoop();
};

#endif // JS1_H
