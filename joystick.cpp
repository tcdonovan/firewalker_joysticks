#include "joystick.h"

Joystick::Joystick(int whichJoystick, QObject *parent) : QObject(parent)
{

    joy_fd=0;

    num_of_axis=0;
    num_of_buttons=0;
    x=0;

//    assert( (whichJoystick == 0) || (whichJoystick == 1) );
    which_joystick_index = 0;
    strJoystickName = JOY_DEV0;
    if( whichJoystick == 1 )
    {
        which_joystick_index = 1;
        strJoystickName = JOY_DEV1;
    }
}

Joystick::~Joystick()
{
    close( joy_fd );
}

void Joystick::doWork()
{
    if( ( joy_fd = open( strJoystickName.toLocal8Bit().data(), O_RDONLY)) == -1 )
    {
            printf( "Couldn't open joystick %s\n", strJoystickName.toLocal8Bit().data() );
            return; // Return without continuing loop
    }

    ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
    ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
    ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

    _axis = (int *) calloc( num_of_axis, sizeof( int ) );
    _button = (char *) calloc( num_of_buttons, sizeof( char ) );

    printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
            , name_of_joystick
            , num_of_axis
            , num_of_buttons );

    //    fcntl( joy_fd, F_SETFL, O_NONBLOCK );   /* use non-blocking mode */
        fcntl( joy_fd, F_SETFL );   /* use non-blocking mode */

        QMetaObject::invokeMethod( this, "doMainLoop", Qt::QueuedConnection );

}

void Joystick::doMainLoop() /* infinite loop */
{
    QByteArray myData("");
    /* read the joystick state */
    read(joy_fd, &js, sizeof(struct js_event));//stop and wait for data (if blocking)

        /* see what to do with the event */
    switch (js.type & ~JS_EVENT_INIT)
    {
        case JS_EVENT_AXIS:
                _axis   [ js.number ] = js.value;
                    if (num_of_buttons==32)
                    {
                        printf(" THRJST");
                        myData.append(" THRJST");
                    }else{
                        printf(" JOYJST");
                        myData.append(" JOYJST");
                    }
                break;
        case JS_EVENT_BUTTON:
                _button [ js.number ] = js.value;
                    if (num_of_buttons==32)
                    {
                        printf(" THRBTN");
                        myData.append(" THRBTN");
                    }else{
                        printf(" JOYBTN");
                        myData.append(" JOYBTN");
                    }
                break;
    }

    /* print the results */
    //printf( "A0: %6d A1: %6d ", axis[0], axis[1] );
    printf("%6d %6d ", _axis[0], _axis[1] );
        myData.append(QByteArray::number(_axis[0]).rightJustified(6));
        myData.append(QByteArray::number(_axis[1]).rightJustified(6));

    if( num_of_axis > 2 )
        {
        //printf("A2: %6d  ", axis[2] );
        printf("%6d ", _axis[2] );
            myData.append(QByteArray::number(_axis[2]).rightJustified(6));
        }

    if( num_of_axis > 3 )
        {
        //printf("A3: %6d ", axis[3] );
        printf("%6d ", _axis[3] );
            myData.append(QByteArray::number(_axis[3]).rightJustified(6));
        }

    if( num_of_axis > 4 )
        {
        //printf("A4: %6d ", axis[4] );
        printf("%6d ", _axis[4] );
            myData.append(QByteArray::number(_axis[4]).rightJustified(6));
        }

    if( num_of_axis > 5 )
        {
        //printf("A5: %6d ", axis[5] );
        printf("%6d ", _axis[5] );
            myData.append(QByteArray::number(_axis[5]).rightJustified(6));
        }

    if( num_of_axis > 6 )
        {
        //printf("A6: %6d ", axis[6] );
        printf("%6d ", _axis[6] );
            myData.append(QByteArray::number(_axis[6]).rightJustified(6));
        }

        printf("%s"," " );
        myData.append(" ");
    for( x=0 ; x<num_of_buttons ; ++x )
        {
        //printf("B%d: %d ", x, button[x] );
        printf("%d  ", _button[x] );
            myData.append(QByteArray::number(_button[x]).rightJustified(1));
        }
    printf("  \r \n");
        myData.append("\r \n");
        fflush(stdout);
        //nanosleep(&ts,NULL);

    QMetaObject::invokeMethod( this, "doMainLoop", Qt::QueuedConnection );
    emit reportTelemetryUpdate(myData);

}


