#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRPS.h>
#include <cmath>

#include "DriveSystem.h"
#include "Robot.h"
#include "ButtonSwitch.h"
#include "SupplyArm.h"

#define SUP_X_TARGET            28.0
#define X_TARGET                30.0
#define Y_TARGET                64.1

#define YELLOW_BLUE_THRESHOLD   1.25

int main(void)
{
    using namespace std;

    RPS.InitializeTouchMenu();

//    buttonSwitch->ArmIn();

    supplyArm->ToDropOff();

    float start = TimeNow();
    while(TimeNow() - start < 1.0);

//    buttonSwitch->ToRedButton();

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

    drive->WaitForSetpointInch(SUP_X_TARGET - RPS.X());

    drive->Stop();

    while(RPS.X() < SUP_X_TARGET - .2 || RPS.X() > SUP_X_TARGET)
    {
        if(RPS.X() < SUP_X_TARGET - .2)
        {
            drive->MoveBackwards(25);
            Sleep(0.05);
            drive->Stop();
        }

        if(RPS.X() > SUP_X_TARGET)
        {
            drive->MoveForward(25);
            Sleep(0.05);
            drive->Stop();
        }
    }

    Sleep(0.25);

    drive->ZeroTurnCounter(80);

    drive->Stop();

    Sleep(0.25);

    start = TimeNow();

    while((RPS.Heading() < 90 - 1 || RPS.Heading() > 90 + 1) && TimeNow() - start < 0.25)
    {
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
    }

    drive->MoveForward(50);

    drive->WaitForSetpointInch(RPS.Y() - 11.5 - 6);

    drive->Stop();

    Sleep(0.25);

    float angle;

    if(RPS.X() > SUP_X_TARGET)
    {
        angle = atan2(RPS.Y() - 11.5, RPS.X() - SUP_X_TARGET);
        angle = 90 - angle;
    }
    else
    {
        angle = atan2(RPS.Y() - 11.5, SUP_X_TARGET - RPS.X());
        angle = 90 + angle;
    }

    start = TimeNow();

    while((RPS.Heading() < angle - 1 || RPS.Heading() > angle + 1) && TimeNow() - start < 0.25)
    {
        if(RPS.Heading() < angle)
        {
            drive->ZeroTurnCounter(90 - RPS.Heading());
            Sleep(0.25);
        }
        else if(RPS.Heading() > angle)
        {
            drive->ZeroTurnClockwise(RPS.Heading() - 90);
            Sleep(0.25);
        }
    }

    drive->MoveForward(50);

    drive->WaitForSetpointInch(RPS.Y() - 11.5);

    drive->Stop();

    Sleep(0.25);
    //Correction and mechanism here
    //Correct to (28.7, 11.5)
    supplyArm->ToPickUp();
    //Correction and mechanism end here

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

    if(RPS.X() < X_TARGET - 0.1)
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

        drive->MoveBackwards(50);

        drive->WaitForSetpointInch(X_TARGET - RPS.X());

        drive->Stop();

        Sleep(0.25);

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

        drive->MoveForward(50);

        drive->WaitForSetpointInch(RPS.X() - X_TARGET);

        drive->Stop();

        Sleep(0.25);

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

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(Y_TARGET - RPS.Y());

    drive->Stop();

    //RPS Checks and math. Fun.....

//    if(RPS.X() < X_TARGET)
//    {
//        //Do the maths
//        float x = X_TARGET - RPS.X();
//        float y = Y_TARGET - RPS.Y();

//        float angle = 90 - atan2(y, x); //Not right. Fix later.

//        float target = sqrt(pow(x, 2) + pow(y, 2));

//        drive->ZeroTurnClockwise(angle);

//        drive->Stop();

//        Sleep(0.25);

//        drive->MoveBackwards(30);

//        drive->WaitForSetpointInch(target);

//        drive->Stop();

//        Sleep(0.25);

//        drive->MoveForward(20);

//        drive->WaitForSetpointInch(0.5);

//        drive->Stop();

//        Sleep(0.25);

//        drive->ZeroTurnCounter(90);

//        drive->Stop();

//        Sleep(0.25);

//        start = TimeNow();

//        while((RPS.Heading() < 90 - 1 || RPS.Heading() > 90 + 1) && TimeNow() - start < 0.25)
//        {
//            if(RPS.Heading() < 90)
//            {
//                drive->ZeroTurnCounter(90 - RPS.Heading());

//                drive->Stop();

//                Sleep(0.25);
//            }
//            else
//            {
//                drive->ZeroTurnClockwise(RPS.Heading() - 90);

//                drive->Stop();

//                Sleep(0.25);
//            }
//        }
//    }
//    else if(RPS.X() > X_TARGET)
//    {
//        //Do the other maths
//        float x = RPS.X() - X_TARGET;
//        float y = Y_TARGET - RPS.Y();

//        float angle = 90 - atan2(y, x); //Not right. Fix later.

//        float target = sqrt(pow(x, 2) + pow(y, 2));

//        drive->ZeroTurnCounter(angle);

//        drive->Stop();

//        Sleep(0.25);

//        drive->MoveBackwards(30);

//        drive->WaitForSetpointInch(target);

//        drive->Stop();

//        Sleep(0.25);

//        drive->ZeroTurnClockwise(90 - RPS.Heading());

//        drive->Stop();

//        Sleep(0.25);
//    }

//    drive->MoveBackwards(30);

//    drive->WaitForSetpointInch(Y_TARGET - RPS.Y());

//    drive->Stop();

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

    Sleep(0.25);

    drive->LineFollowingFunc();

    Sleep(0.25);

    supplyArm->ToDropOff();

    Sleep(1.0);

    supplyArm->ToPickUp();

    Sleep(0.25);

    drive->BackwardsTurn(50, 40);

    Sleep(2.0);

    drive->Stop();  //RPS Checks for posiiton to line up on the middle switch

    Sleep(0.25);

    drive->ZeroTurnCounter(90);

    drive->Stop();

    Sleep(0.25);

    while(RPS.Heading() < 0)
    {
        drive->MoveBackwards(50);

        Sleep(0.1);

        drive->Stop();
    }

    if(RPS.Heading() < 359.9 && RPS.Heading() > 180)
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

    drive->WaitForSetpointInch(X_TARGET - RPS.X());

    drive->Stop();

    Sleep(0.25);

    drive->ZeroTurnCounter(90);

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

    drive->WaitForSetpointInch(25);

    drive->Stop();
    return 0;
}
