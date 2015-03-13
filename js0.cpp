#include "js0.h"


JS0::JS0(QObject *parent) : QObject(parent)
{


    joy_fd0=0;

    num_of_axis=0;
    num_of_buttons=0;
    x=0;
    name_of_joystick[80]=NULL;
    //struct js_event js;



}

JS0::~JS0()
{
  close( joy_fd0 );
    //close( joy_fd0 );        /* too bad we never get here */

}


//void JS0::readStick0()
//{
//    printf("TEST");

//    int joy_fd0, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
//    char *button=NULL, name_of_joystick[80];
//    struct js_event js;




//}

void JS0::doWork0()
{

    //struct timespec ts = {0,8.*1000000.};

    //for(;;){readStick0(); nanosleep(&ts,NULL);}
    //readStick0();
    int *axis=NULL;
    char *button=NULL;

    if( ( joy_fd0 = open( JOY_DEV0 , O_RDONLY)) == -1 )
    {
            printf( "Couldn't open joystick\n" );
            //return -1;
    }

    ioctl( joy_fd0, JSIOCGAXES, &num_of_axis );
    ioctl( joy_fd0, JSIOCGBUTTONS, &num_of_buttons );
    ioctl( joy_fd0, JSIOCGNAME(80), &name_of_joystick );

    axis = (int *) calloc( num_of_axis, sizeof( int ) );
    button = (char *) calloc( num_of_buttons, sizeof( char ) );

    printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
            , name_of_joystick
            , num_of_axis
            , num_of_buttons );

    //    fcntl( joy_fd0, F_SETFL, O_NONBLOCK );   /* use non-blocking mode */
        fcntl( joy_fd0, F_SETFL );   /* use non-blocking mode */

    while( 1 )      /* infinite loop */
    {

            /* read the joystick state */
        read(joy_fd0, &js, sizeof(struct js_event));//stop and wait for data (if blocking)

            /* see what to do with the event */
        switch (js.type & ~JS_EVENT_INIT)
        {
            case JS_EVENT_AXIS:
                    axis   [ js.number ] = js.value;
                    printf(" THR JS_TRIP ");
                    break;
            case JS_EVENT_BUTTON:
                    button [ js.number ] = js.value;
                    printf(" THR BT_TRIP ");
                    break;
        }

            /* print the results */
        //printf( "A0: %6d A1: %6d ", axis[0], axis[1] );
        printf("%6d %6d ", axis[0], axis[1] );

        if( num_of_axis > 2 )
            //printf("A2: %6d  ", axis[2] );
            printf("%6d ", axis[2] );

        if( num_of_axis > 3 )
            //printf("A3: %6d ", axis[3] );
            printf("%6d ", axis[3] );

        if( num_of_axis > 4 )
            //printf("A4: %6d ", axis[4] );
            printf("%6d ", axis[4] );

        if( num_of_axis > 5 )
            //printf("A5: %6d ", axis[5] );
            printf("%6d ", axis[5] );

        if( num_of_axis > 6 )
            //printf("A6: %6d ", axis[6] );
            printf("%6d ", axis[6] );

        for( x=0 ; x<num_of_buttons ; ++x )
            //printf("B%d: %d ", x, button[x] );
            printf("%d  ", button[x] );

        printf("  \r \n");
        //nanosleep(&ts,NULL);
        fflush(stdout);



    }



}
