#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRPS.h>
#include <cmath>
#include <FEHSD.h>

#include "DriveSystem.h"
#include "Robot.h"
#include "ButtonSwitch.h"
#include "SupplyArm.h"

#define PI  3.14159265358979323846
int main(void)
{
    using namespace std;

    RPS.InitializeTouchMenu();

    float supXTarget, supYTarget, xTargetFuel, yTargetFuel, finalXTarget, postRampYDown, switchX, switchY;

    robot->SelectRPSRegionVariables(&supXTarget, &xTargetFuel, &yTargetFuel, &finalXTarget, &postRampYDown, &switchX, &switchY);

    buttonSwitch->ArmIn();

    supplyArm->ToDropOff();

    float start = TimeNow();
    while(TimeNow() - start < 1.0);

    buttonSwitch->NeutralButton();

    while(!robot->Start());

    ///////////////////////////////
    ///////Start to Supplies///////
    ///////////////////////////////
    drive->MoveBackwards(70);

    drive->WaitForSetpointInch(12.5); //12.5

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

    drive->WaitForSetpointInch(supXTarget - RPS.X());

    drive->Stop();

    if(RPS.X() < supXTarget - .1)
    {
        while(RPS.X() < supXTarget - .1)
        {
            drive->MoveBackwards(25);
            Sleep(0.05);
            drive->Stop();
            Sleep(0.1);
        }
    }
    else if(RPS.X() > supXTarget)
    {
        while(RPS.X() > supXTarget)
        {
            drive->MoveForward(25);
            Sleep(0.05);
            drive->Stop();
            Sleep(0.1);
        }
    }

    Sleep(0.25);

    drive->ZeroTurnCounter(90);

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

    if(RPS.X() > supXTarget)
    {
        angle = atan2(RPS.Y() - supYTarget, RPS.X() - supXTarget);
        angle = 90 - angle;
    }
    else
    {
        angle = atan2(RPS.Y() - 11.5, supXTarget - RPS.X());
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

    drive->ZeroTurnClockwise(10);

    drive->ZeroTurnCounter(10);

    drive->MoveForward(30);

    drive->WaitForSetpointInch(RPS.Y() - 11.5);

    Sleep(0.25);

    supplyArm->ToPickUp();

    Sleep(0.5);
    //Correction and mechanism end here

    ///////////////////////////////
    ///////Supplies to Upper///////
    ///////////////////////////////

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

    if(RPS.X() < xTargetFuel - 1.6)
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

        drive->MoveBackwards(30);

        drive->WaitForSetpointInch(xTargetFuel - RPS.X());

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
    }
    else if(RPS.X() > xTargetFuel)
    {
        drive->ZeroTurnClockwise(RPS.Heading());

        drive->Stop();

        Sleep(0.25);

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

        drive->MoveForward(30);

        drive->WaitForSetpointInch(RPS.X() - xTargetFuel);

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
    }

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(25);

    drive->Stop();

    Sleep(0.25);

    start = TimeNow();

    while((RPS.Heading() < 90 - 1 || RPS.Heading() > 90 + 1) && TimeNow() - start < 2.0)
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

    buttonSwitch->ArmInMid();

    Sleep(0.1);

    //////////////////////////////
    ///////Upper to Buttons///////
    //////////////////////////////

    while(RPS.Y() < yTargetFuel - 8)
    {
        drive->MoveBackwards(50);
        drive->WaitForSetpointInch(yTargetFuel - 8 - RPS.Y());
    }

    //RPS Checks and math. Fun....
    if(RPS.X() < xTargetFuel - 5/8.0 || RPS.X() > xTargetFuel)
    {
        drive->ZeroTurnClockwise(90);

        Sleep(0.25);

        if(RPS.X() < 0)
        {
            drive->MoveBackwards(30);
            while(RPS.X() < 0)
            drive->Stop();
        }
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

        if(RPS.X() < 0)
        {
            while(RPS.X() < 0)
            {
                drive->MoveBackwards(30);
            }
            drive->Stop();
        }
        if(RPS.X() < xTargetFuel)
        {
            drive->MoveBackwards(30);

            drive->WaitForSetpointInch(xTargetFuel - RPS.X());

            drive->Stop();

            Sleep(0.25);
        }

        if(RPS.X() < xTargetFuel  - 0.1)
        {
            while(RPS.X() < xTargetFuel - 0.1) //0.0
            {
                drive->MoveBackwards(25);
                Sleep(0.05);
                drive->Stop();
                Sleep(0.1);
            }
        }
        else if(RPS.X() > xTargetFuel + 0.1)
        {
            while(RPS.X() > xTargetFuel + 0.1)
            {
                drive->MoveForward(25);
                Sleep(0.05);
                drive->Stop();
                Sleep(0.1);
            }
        }

        drive->ZeroTurnCounter(90);

        Sleep(0.25);
    }

    start = TimeNow();

    while((RPS.Heading() < 90 - 1 || RPS.Heading() > 90 + 1) && TimeNow() - start < 1.0)
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

    drive->MoveBackwards(30);

    drive->WaitForSetpointInch(yTargetFuel - 0.5 - RPS.Y());

    drive->Stop();

    while(RPS.Y() < yTargetFuel - 0.05 || RPS.Y() > yTargetFuel + 0.05)
    {
        if(RPS.Y() < yTargetFuel)
        {
            drive->MoveBackwards(30);
            Sleep(0.05);
            drive->Stop();
            Sleep(0.1);
        }
        else if(RPS.Y() > yTargetFuel)
        {
            drive->MoveForward(30);
            Sleep(0.05);
            drive->Stop();
            Sleep(0.1);
        }
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

    buttonSwitch->NeutralButton();

    Sleep(1.0);

    start = TimeNow();

    while(!robot->IsRed() && TimeNow() - start < 0.15)
    {
        drive->MoveBackwards(20);

        Sleep(0.05);

        drive->Stop();

        Sleep(0.05);

        if(robot->IsRed())
        {
            LCD.WriteLine("Red Button");
        }
        else if(robot->IsBlue())
        {
            LCD.WriteLine("Blue Button");
        }
        else
        {
            LCD.WriteLine("Unknown");
        }
    }

    LCD.WriteLine(robot->FuelValue());

    robot->PressButton();

    Sleep(0.25);

    /////////////////////////////////
    ///////Buttons to Drop Off///////
    /////////////////////////////////

    SD.OpenLog();

    drive->LineFollowingFunc();

    SD.CloseLog();

    Sleep(0.25);

    supplyArm->ToDropOff();

    Sleep(1.0);

    supplyArm->ToPickUp();

    Sleep(1.0);

    //////////////////////////////////
    ///////Drop Off to Switches///////
    //////////////////////////////////

    drive->BackwardsTurn(50, 35);

    drive->WaitForSetpointInch(12.5);

    drive->Stop();

    Sleep(0.25);

    while(RPS.Heading() < 0)
    {
        drive->MoveBackwards(50);
    }
    drive->Stop();

    drive->ZeroTurnCounter(90);

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

    if(RPS.X() < switchX)
    {
        drive->MoveBackwards(50);
        drive->WaitForSetpointInch(switchX - RPS.X());
        drive->Stop();
        Sleep(0.25);
    }
    else if(RPS.X() > switchX)
    {
        drive->MoveForward(50);
        drive->WaitForSetpointInch(RPS.X() - switchX);
        drive->Stop();
        Sleep(0.25);
    }

    drive->ZeroTurnClockwise(90);

    while(RPS.Y() < 0)
    {
        drive->BackwardsTurn(60, 35);
        Sleep(0.25);
        drive->Stop();
        Sleep(0.25);
    }

    //////////////////////////////////////
    ///////Line up and Hit Switches///////
    //////////////////////////////////////
    //RPS Checks for posiiton to line up on the middle switch

    if(RPS.Heading() < 270)
    {
        drive->ZeroTurnCounter(270 - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 270)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - 270);
        Sleep(0.25);
    }

    while(RPS.Y() >= switchY + 1.0)
    {
        drive->MoveBackwards(50);
        drive->WaitForSetpointInch(1);
        drive->Stop();
        Sleep(0.25);
    }
    robot->FlipSwitches(RPS.RedSwitchDirection(), RPS.WhiteSwitchDirection(), RPS.BlueSwitchDirection());


    /////////////////////////////
    ///////To Final Button///////
    /////////////////////////////

    drive->MoveForward(50);
    drive->WaitForSetpointInch(1);
    drive->Stop();

    buttonSwitch->NeutralButton();

    Sleep(0.25);

    drive->ZeroTurnCounter(90);

    drive->Stop();

    Sleep(0.25);

    drive->MoveBackwards(50);

    drive->WaitForSetpointInch(1.0);

    drive->Stop();

    while(RPS.Heading() < 0)
    {
        drive->MoveBackwards(50);

        Sleep(0.1);

        drive->Stop();
    }

    start = TimeNow();

    while(((RPS.Heading() < 359.9 - 1 && RPS.Heading() > 180) || (RPS.Heading() > 0 + 1 && RPS.Heading() < 180)) && TimeNow() - start < 2.0)
    {
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
    }

    drive->MoveBackwards(70);

    drive->WaitForSetpointInch(xTargetFuel - RPS.X() - 4);

    drive->Stop();

    Sleep(0.25);

    while(RPS.X() < xTargetFuel)
    {
        drive->MoveBackwards(50);
        Sleep(0.05);
        drive->Stop();
        Sleep(0.05);
    }

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

    Sleep(0.25);

    if(RPS.Y() > postRampYDown)
    {
        drive->MoveForward(30);

        drive->WaitForSetpointInch(RPS.Y() - postRampYDown);

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

    float x = RPS.X();
    float y = RPS.Y();

    angle = atan2(x, y) * 180 / PI + 10;

    drive->ZeroTurnCounter(180 - angle);

    if(RPS.Heading() < 270 - angle)
    {
        drive->ZeroTurnCounter(270 - angle - RPS.Heading());
        Sleep(0.25);
    }
    else if(RPS.Heading() > 270 - angle)
    {
        drive->ZeroTurnClockwise(RPS.Heading() - (270 - angle));
        Sleep(0.25);
    }

    x = RPS.X();
    y = RPS.Y();
    float hyp = sqrt(pow(x, 2) + pow(y, 2));

    drive->BackwardsTurn(80, 70);

    drive->WaitForSetpointInch(hyp / 2);

    Sleep(0.25);

    drive->BackwardsTurn(70,50);

    drive->WaitForSetpointInch(hyp);

    return 0;
}
