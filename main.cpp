/*********************************************
 *  This is a comment or something
 ********************************************/
#include <QCoreApplication>
#include <QThread>


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#include "js0.h"
#include "js1.h"

#define JOY_DEV0 "/dev/input/js0"
#define JOY_DEV1 "/dev/input/js1"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    QThread js0Thread;
    QThread js1Thread;

    JS0* myJS0 = new JS0();
    JS1* myJS1 = new JS1();

    myJS0->moveToThread(&js0Thread);
    myJS1->moveToThread(&js1Thread);

    QObject::connect(&js0Thread,SIGNAL(started()),myJS0,SLOT(doWork0()));
    QObject::connect(&js1Thread,SIGNAL(started()),myJS1,SLOT(doWork1()));


    js0Thread.start();
    js1Thread.start();



    return a.exec();
}

