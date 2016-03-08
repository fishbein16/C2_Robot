#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRPS.h>
#include <cmath>

#include "DriveSystem.h"
#include "Robot.h"
#include "ButtonSwitch.h"

#define SUP_X_TARGET            28.5
#define X_TARGET                30.0
#define Y_TARGET                64.1

#define YELLOW_BLUE_THRESHOLD   1.25

int main(void)
{
    using namespace std;

    RPS.InitializeTouchMenu();

//    buttonSwitch->ArmIn();

    float start = TimeNow();
    while(TimeNow() - start < 1.0);

    buttonSwitch->ToRedButton();

    while(!robot->Start());

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(16.5);

    drive->Stop();

    Sleep(0.25);

    drive->ZeroTurnClockwise(40);

    drive->Stop();

    Sleep(0.25);

    if(RPS.Heading() < 359.9 && RPS.Heading() > 330)
    {
        drive->ZeroTurnCounter(359.9 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 0)
    {
        drive->ZeroTurnClockwise(RPS.Heading());
        Sleep(0.25);
    }

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(9);

    drive->Stop();

    while(RPS.X() < SUP_X_TARGET - .2)
    {
        drive->MoveBackwards(25);
        Sleep(0.05);
        drive->Stop();
    }

    while(RPS.X() > SUP_X_TARGET)
    {
        drive->MoveForward(25);
        Sleep(5);
        drive->Stop();
    }

    Sleep(0.25);

    drive->ZeroTurnCounter(80);

    drive->Stop();

    Sleep(0.25);

    if(RPS.Heading() < 90)
    {
        drive->ZeroTurnCounter(90 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 90)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - 90);
        Sleep(0.25);
    }

    drive->MoveForward(50);

    drive->WaitForSetpointInch(12);

    drive->Stop();

    Sleep(0.25);

    if(RPS.Heading() < 90)
    {
        drive->ZeroTurnCounter(90 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 90)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - 90);
        Sleep(0.25);
    }

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(13);

    drive->Stop();

    Sleep(0.25);

    if(RPS.X() < X_TARGET - 0.25)
    {
        drive->ZeroTurnClockwise(RPS.Heading());

        drive->Stop();

        Sleep(0.25);

        if(RPS.Heading() < 359.9 && RPS.Heading() > 330)
        {
            drive->ZeroTurnCounter(359.9 - RPS.Heading());
            Sleep(0.25);
        }
        else if(RPS.Heading() > 0)
        {
            drive->ZeroTurnClockwise(RPS.Heading());
            Sleep(0.25);
        }

        drive->MoveBackwards(X_TARGET - RPS.X());

        drive->ZeroTurnCounter(90);

        drive->Stop();

        Sleep(0.25);
    }
    else if(RPS.X() > X_TARGET + 0.1)
    {
        drive->ZeroTurnClockwise(RPS.Heading());

        drive->Stop();

        Sleep(0.25);

        if(RPS.Heading() < 359.9 && RPS.Heading() > 330)
        {
            drive->ZeroTurnCounter(359.9 - RPS.Heading());
            Sleep(0.25);
        }
        else if(RPS.Heading() > 0)
        {
            drive->ZeroTurnClockwise(RPS.Heading());
            Sleep(0.25);
        }

        drive->MoveForward(RPS.X() - X_TARGET);

        drive->ZeroTurnCounter(90);

        drive->Stop();

        Sleep(0.25);
    }
    if(RPS.Heading() < 90)
    {
        drive->ZeroTurnCounter(90 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 90)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - 90);
        Sleep(0.25);
    }

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(30);

    drive->Stop();

    Sleep(0.25);

    if(RPS.Heading() < 90)
    {
        drive->ZeroTurnCounter(90 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 90)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - 90);
        Sleep(0.25);
    }

    drive->LineFollowingBack();

    //RPS Checks and math. Fun.....

    if(RPS.X() < X_TARGET)
    {
        //Do the maths
        float x = X_TARGET - RPS.X();
        float y = Y_TARGET - RPS.Y();

        float angle = 90 - atan2(y, x); //Not right. Fix later.

        float target = sqrt(pow(x, 2) + pow(y, 2));

        drive->ZeroTurnClockwise(angle);

        drive->Stop();

        Sleep(0.25);

        drive->MoveBackwards(30);

        drive->WaitForSetpointInch(target);

        drive->Stop();

        Sleep(0.25);

        drive->MoveForward(20);

        drive->WaitForSetpointInch(0.5);

        drive->Stop();

        Sleep(0.25);

        drive->ZeroTurnCounter(90);

        drive->Stop();

        Sleep(0.25);

        while(RPS.Heading() < 90 - 1 || RPS.Heading() > 90 + 1)
        {
            if(RPS.Heading() < 90)
            {
                drive->ZeroTurnCounter(90 - RPS.Heading());

                drive->Stop();

                Sleep(0.25);
            }
            else
            {
                drive->ZeroTurnClockwise(RPS.Heading() - 90);

                drive->Stop();

                Sleep(0.25);
            }
        }
    }
    else if(RPS.X() > X_TARGET)
    {
        //Do the other maths
        float x = RPS.X() - X_TARGET;
        float y = Y_TARGET - RPS.Y();

        float angle = 90 - atan2(y, x); //Not right. Fix later.

        float target = sqrt(pow(x, 2) + pow(y, 2));

        drive->ZeroTurnCounter(angle);

        drive->Stop();

        Sleep(0.25);

        drive->MoveBackwards(30);

        drive->WaitForSetpointInch(target);

        drive->Stop();

        Sleep(0.25);

        drive->ZeroTurnClockwise(90 - RPS.Heading());

        drive->Stop();

        Sleep(0.25);
    }

    drive->MoveBackwards(30);

    drive->WaitForSetpointInch(Y_TARGET - RPS.Y());

    drive->Stop();

    if(robot->FuelValue() < RED_BLUE_THRESHOLD)
    {
        LCD.WriteLine("Red Button");
    }
    else if(robot->FuelValue() > RED_BLUE_THRESHOLD && robot->FuelValue() < BLUE_NO_LIGHT_THRESHOLD)
    {
        LCD.WriteLine("Blue Button");
    }
    else
    {
        LCD.WriteLine("Unknown");
    }

    LCD.WriteLine(robot->FuelValue());

//    Sleep(0.25);

//    drive->LineFollowingFunc();

//    Sleep(0.25);

//    drive->ForwardTurn(45, -10.0);

//    Sleep(3.0);

//    drive->Stop();

//    Sleep(0.25);

//    drive->ForwardTurn(0, 20);

//    Sleep(1.0);

//    drive->Stop();

//    Sleep(0.25);

//    drive->BackwardsTurn(50, 40);

//    Sleep(2.0);

//    drive->Stop();  //RPS Checks for posiiton to line up on the middle switch
    return 0;
}
