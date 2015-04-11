<<<<<<< HEAD
/*********************************************
 *  This is a comment or something
 ********************************************/
#include "joystick.h"

#define JOY_DEV0 "/dev/input/js0"
#define JOY_DEV1 "/dev/input/js1"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread js0Thread;
    QThread js1Thread;

    Joystick* myJS0 = new Joystick(0);
    Joystick* myJS1 = new Joystick(1);

    myJS0->moveToThread(&js0Thread);
    myJS1->moveToThread(&js1Thread);

    QObject::connect(&js0Thread,SIGNAL(started()),myJS0,SLOT(doWork()));
    QObject::connect(&js1Thread,SIGNAL(started()),myJS1,SLOT(doWork()));

    js0Thread.start();
    js1Thread.start();

    return a.exec();
}

