#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include "Example.h"

int main(void)
{
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    while( true )
    {
        if( LCD.Touch(&x,&y) )
        {
            LCD.WriteLine( "Hello World!" );
            Sleep( 100 );
        }
    }
    //Using global pointer object
    object->randfunction();

    return 0;
}

