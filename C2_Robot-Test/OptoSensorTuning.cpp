#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHMotor.h>

int main(void)
{
    AnalogInputPin left(FEHIO::P1_1);
    AnalogInputPin middle(FEHIO::P1_2);
    AnalogInputPin right(FEHIO::P1_3);

    ButtonBoard button(FEHIO::Bank3);

    while (true)
    {
        if(button.MiddlePressed())
        {
            LCD.Write("Left value: ");
            LCD.WriteLine(left.Value());
            LCD.Write("Middle value: ");
            LCD.WriteLine(middle.Value());
            LCD.Write("Right value: ");
            LCD.WriteLine(right.Value());

        }
    }


    return(0);
}

