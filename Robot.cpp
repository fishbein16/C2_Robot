
#include "Robot.h"

Robot* robot = new Robot();

Robot::Robot()
{
  fuelSensor = new AnalogInputPin(FEHIO::P2_2);
  startSensor = new AnalogInputPin(FEHIO::P2_0);
}

bool Robot::Start()
{
    return StartValue() < RED_BLUE_THRESHOLD;
}

float Robot::FuelValue()
{
    return fuelSensor->Value();
}

float Robot::StartValue()
{
    return startSensor->Value();
}

void Robot::FlipSwitches(int left, int middle, int right)
{
    //1 is towards bottom level
    //Otherwise, towards upper level
    bool againstWall = true;
    if(left == 1)
    {
        buttonSwitch->ToLeftSwitch();
        buttonSwitch->ArmOut();
        Sleep(0.25);
    }
    else
    {
        buttonSwitch->ToLeftMidGap();
        buttonSwitch->ArmOut();
        Sleep(0.1);
        buttonSwitch->ToLeftSwitch();

        drive->MoveForward(20);
        drive->WaitForSetpointInch(0.2);
        drive->Stop();
        Sleep(0.25);

        againstWall = false;

        buttonSwitch->ToLeftMidGap();
    }

    if(middle == 1)
    {
        if(againstWall)
        {
            drive->MoveForward(20);
            drive->WaitForSetpointInch(0.2);
            drive->Stop();
            againstWall = false;
            Sleep(0.25);
        }
        buttonSwitch->ToMiddleSwitch();

        drive->MoveBackwards(20);
        drive->WaitForSetpointInch(0.3);
        drive->Stop();
        Sleep(0.25);
    }
    else
    {
        if(!againstWall)
        {
            drive->MoveBackwards(20);
            drive->WaitForSetpointInch(0.3);
            drive->Stop();
            againstWall = true;
            Sleep(0.25);
        }
        buttonSwitch->ArmIn();
        Sleep(0.1);
        buttonSwitch->ToMiddleSwitch();
        buttonSwitch->ArmOutMid();

        drive->MoveForward(20);
        drive->WaitForSetpointInch(0.2);
        drive->Stop();
        againstWall = false;
        Sleep(0.25);
    }

    if(right == 1)
    {
        if(againstWall)
        {
            drive->MoveForward(20);
            drive->WaitForSetpointInch(0.2);
            drive->Stop();
            Sleep(0.25);
            againstWall = false;
        }
        buttonSwitch->ToRightSwitch();

        drive->MoveBackwards(20);
        drive->WaitForSetpointInch(0.3);
        drive->Stop();
        Sleep(0.25);
        againstWall = true;
    }
    else
    {
        buttonSwitch->ToRightMidGap();

        if(!againstWall)
        {
            drive->MoveBackwards(20);
            drive->WaitForSetpointInch(0.3);
            drive->Stop();
            Sleep(0.25);
            againstWall = true;
        }
        buttonSwitch->ToRightSwitch();

        drive->MoveForward(20);
        drive->WaitForSetpointInch(0.2);
        drive->Stop();
        Sleep(0.25);
        againstWall = false;
    }

    if(!againstWall)
    {
        drive->MoveBackwards(20);
        drive->WaitForSetpointInch(0.3);
        drive->Stop();
        Sleep(0.25);
    }

    buttonSwitch->ToRightMidGap();
    buttonSwitch->ArmIn();
    buttonSwitch->ToMiddleSwitch();
}

bool Robot::IsRed()
{
    return FuelValue() < RED_BLUE_THRESHOLD;
}

bool Robot::IsBlue()
{
    return FuelValue() < BLUE_NO_LIGHT_THRESHOLD && FuelValue() > RED_BLUE_THRESHOLD;
}

void Robot::PressButton()
{
    if(IsRed())
    {
        buttonSwitch->ToRedButton();
        Sleep(0.2);
    }
    else
    {
        drive->MoveForward(30);
        drive->WaitForSetpointInch(0.2);
        drive->Stop();
        Sleep(0.25);
        buttonSwitch->ToBlueButton();
        Sleep(0.5);
    }

    drive->MoveBackwards(20);

    Sleep(0.75);

    drive->Stop();

    Sleep(5.00);

    drive->MoveForward(30);

    drive->WaitForSetpointInch(1);

    drive->Stop();

    buttonSwitch->ToRedButton();
}
