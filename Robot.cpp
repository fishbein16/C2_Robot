
#include "Robot.h"

Robot* robot = new Robot();

Robot::Robot()
{
  fuelSensor = new AnalogInputPin(FEHIO::P2_2);
  startSensor = new AnalogInputPin(FEHIO::P2_0);

  isRed = false;
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
        buttonSwitch->ArmFullIn();
        buttonSwitch->ToLeftSwitch();
        Sleep(0.5);
        buttonSwitch->ArmOut();
        Sleep(0.5);
        buttonSwitch->ToLeftMidGap();
        Sleep(0.5);
        buttonSwitch->ArmFullIn();
    }
    else if(left == 2)
    {
        buttonSwitch->ToLeftMidGap();
        Sleep(0.5);
        buttonSwitch->ArmOut();
        Sleep(0.5);
        buttonSwitch->ToLeftSwitch();

        buttonSwitch->ArmPull();

        drive->MoveForward(30);
        drive->WaitForSetpointInch(2.5);
        drive->Stop();
        Sleep(0.5);

        againstWall = false;

        drive->MoveBackwards(50);

        drive->WaitForSetpointInch(2.5);

        drive->Stop();

        buttonSwitch->ArmOut();
        buttonSwitch->ToLeftMidGap();
        Sleep(0.5);
    }

    if(middle == 1)
    {
        drive->MoveForward(30);
        if(againstWall)
        {
            drive->WaitForSetpointInch(4.5);
        }
        else
        {
            drive->WaitForSetpointInch(4.5);
        }
        drive->Stop();
        againstWall = false;
        Sleep(0.5);

        buttonSwitch->ToMiddleSwitchPush();
        Sleep(0.5);
        buttonSwitch->ArmOutMid();
        Sleep(0.5);

        drive->MoveBackwards(30);
        drive->WaitForSetpointInch(2.0);
        drive->Stop();
        Sleep(0.5);
        buttonSwitch->ArmIn();
        againstWall = false;
        buttonSwitch->ToRightMidGap();
        Sleep(0.5);

        drive->MoveBackwards(30);
        drive->WaitForSetpointInch(1.0);
        drive->Stop();
    }
    else if(middle == 2)
    {
        if(!againstWall)
        {
            drive->MoveBackwards(30);
            drive->WaitForSetpointInch(2.6);
            drive->Stop();
            againstWall = true;
            Sleep(0.5);
        }
        buttonSwitch->ArmFullIn();
        Sleep(0.5);
        buttonSwitch->ToMiddleSwitchPull();
        Sleep(0.5);
        buttonSwitch->ArmOutMid();
        Sleep(0.5);

        drive->MoveForward(30);
        drive->WaitForSetpointInch(2.0);
        drive->Stop();
        againstWall = false;
        buttonSwitch->ArmIn();
        Sleep(0.5);
        buttonSwitch->ToRightMidGap();
        Sleep(0.5);

        drive->MoveForward(30);
        drive->WaitForSetpointInch(0.3);
        drive->Stop();
    }

//    if(againstWall)
//    {
//        drive->MoveForward(30);
//        drive->WaitForSetpointInch(1.0);
//        drive->Stop();
//        againstWall = false;
//    }
//    else if(!againstWall)
//    {
//        drive->MoveForward(30);
//        drive->WaitForSetpointInch(0.3);
//        drive->Stop();
//    }

    buttonSwitch->ArmOut();

    Sleep(0.5);

//    while(RPS.Heading() < 0)
//    {
//        drive->MoveBackwards(30);
//        Sleep(0.05);
//        drive->Stop();
//        Sleep(0.05);
//    }
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

    if(right == 1)
    {
        buttonSwitch->ToRightSwitch();
        Sleep(0.5);

        drive->MoveBackwards(30);
        drive->WaitForSetpointInch(1.1);
        drive->Stop();
        buttonSwitch->ArmOutMid();
        Sleep(0.5);
        againstWall = true;
    }
    else if(right == 2)
    {
        buttonSwitch->ToRightMidGap();
        Sleep(0.5);

        drive->MoveBackwards(30);
        drive->WaitForSetpointInch(3.0);
        drive->Stop();

        buttonSwitch->ToRightSwitch();
        Sleep(0.5);
//        buttonSwitch->ArmPull();

        drive->MoveForward(30);
        drive->WaitForSetpointInch(1.0);
        drive->Stop();
        Sleep(0.5);
        againstWall = false;
    }

    if(!againstWall)
    {
        drive->MoveBackwards(30);
        drive->WaitForSetpointInch(1.0);
        drive->Stop();
        Sleep(0.5);
    }

    buttonSwitch->ToRightMidGap();
    Sleep(0.5);
    buttonSwitch->ArmIn();
    Sleep(0.5);
    buttonSwitch->NeutralButton();
}

bool Robot::IsRed()
{
    if(FuelValue() < RED_BLUE_THRESHOLD)
    {
        isRed = true;
    }
    return isRed;
}

bool Robot::IsBlue()
{
    if(FuelValue() < BLUE_NO_LIGHT_THRESHOLD && FuelValue() > RED_BLUE_THRESHOLD)
    {
        isRed = false;
    }
    return !isRed;
}

void Robot::PressButton()
{
    if(isRed)
    {
        drive->MoveForward(30);
        drive->WaitForSetpointInch(0.5);
        drive->Stop();
        buttonSwitch->ToRedButton();
        Sleep(1.0);
    }
    else
    {
        drive->MoveForward(30);
        drive->WaitForSetpointInch(0.5);
        drive->Stop();
        Sleep(0.25);
        buttonSwitch->ToBlueButton();
        Sleep(1.0);
    }

    drive->MoveBackwards(20);

    Sleep(1.0);

    drive->Stop();

    Sleep(5.00);

    drive->MoveForward(30);

    drive->WaitForSetpointInch(1);

    drive->Stop();

    buttonSwitch->ToRedButton();
}

void Robot::SelectRPSRegionVariables(float *supXTarget, float *xTarget, float *yTarget, float *finalXTarget, float *postRampYDown, float *switchX, float *switchY)
{
    using namespace std;
    int cancel = 1;
    int c=0, d=0, n;
    float x, y;
    char region;

    FEHIcon::Icon regions_title[1];
    char regions_title_label[1][20] = {"Select RPS Region"};

    FEHIcon::Icon regions[8];
    char regions_labels[8][20] = {"A", "B", "C", "D", "E", "F", "G", "H"};

    FEHIcon::Icon confirm_title[1];
    char confirm_title_label[1][20] = {""};

    FEHIcon::Icon confirm[2];
    char confirm_labels[2][20] = {"Ok", "Cancel"};

    while(cancel)
    {
        c=0;
        d=0;
        LCD.Clear(BLACK);

        FEHIcon::DrawIconArray(regions_title, 1, 1, 1, 201, 1, 1, regions_title_label, BLACK, WHITE);
        FEHIcon::DrawIconArray(regions, 2, 4, 40, 1, 1, 1, regions_labels, WHITE, WHITE);

        while (!c)
        {
            if (LCD.Touch(&x, &y))
            {
                for (n=0; n<=7; n++)
                {
                    if (regions[n].Pressed(x, y, 0))
                    {
                        regions[n].WhilePressed(x, y);
                        c = n+1;
                    }
                }
            }
        }
        switch (c)
        {
        case 1:
            region = 'A';
            strcpy(confirm_title_label[0], "Choice: A");
            break;
        case 2:
            region = 'B';
            strcpy(confirm_title_label[0], "Choice: B");
            break;
        case 3:
            region = 'C';
            strcpy(confirm_title_label[0], "Choice: C");
            break;
        case 4:
            region = 'D';
            strcpy(confirm_title_label[0], "Choice: D");
            break;
        case 5:
            region = 'E';
            strcpy(confirm_title_label[0], "Choice: E");
            break;
        case 6:
            region = 'F';
            strcpy(confirm_title_label[0], "Choice: F");
            break;
        case 7:
            region = 'G';
            strcpy(confirm_title_label[0], "Choice: G");
            break;
        case 8:
            region = 'H';
            strcpy(confirm_title_label[0], "Choice: H");
            break;
        }

        LCD.Clear(BLACK);
        FEHIcon::DrawIconArray(confirm_title, 1, 1, 60, 201, 1, 1, confirm_title_label, BLACK, WHITE);
        FEHIcon::DrawIconArray(confirm, 1, 2, 60, 60, 1, 1, confirm_labels, WHITE, WHITE);

        while (!d)
        {
            if (LCD.Touch(&x, &y))
            {
                for (n=0; n<=1; n++)
                {
                    if (confirm[n].Pressed(x, y, 0))
                    {
                        confirm[n].WhilePressed(x, y);
                        d = n+1;
                    }
                }
            }
        }
        switch (d)
        {
        case 1:
            cancel = 0;
            break;
        case 2:
            cancel = 1;
            break;
        }
    }

    switch(region)
    {
    case 'A':
        *supXTarget = SUP_X_TARGET_A;
        *xTarget = X_TARGET_A;
        *yTarget = Y_TARGET_A;
        *finalXTarget = FINAL_X_TARGET_A;
        *postRampYDown = POST_RAMP_Y_DOWN_A;
        *switchX = SWITCH_X_A;
        *switchY = SWITCH_Y_A;
        break;
    case 'B':
        *supXTarget = SUP_X_TARGET_B;
        *xTarget = X_TARGET_B;
        *yTarget = Y_TARGET_B;
        *finalXTarget = FINAL_X_TARGET_B;
        *postRampYDown = POST_RAMP_Y_DOWN_B;
        *switchX = SWITCH_X_B;
        *switchY = SWITCH_Y_B;
        break;
    case 'C':
        *supXTarget = SUP_X_TARGET_C;
        *xTarget = X_TARGET_C;
        *yTarget = Y_TARGET_C;
        *finalXTarget = FINAL_X_TARGET_C;
        *postRampYDown = POST_RAMP_Y_DOWN_C;
        *switchX = SWITCH_X_C;
        *switchY = SWITCH_Y_C;
        break;
    case 'D':
        *supXTarget = SUP_X_TARGET_D;
        *xTarget = X_TARGET_D;
        *yTarget = Y_TARGET_D;
        *finalXTarget = FINAL_X_TARGET_D;
        *postRampYDown = POST_RAMP_Y_DOWN_D;
        *switchX = SWITCH_X_D;
        *switchY = SWITCH_Y_D;
        break;
    case 'E':
        *supXTarget = SUP_X_TARGET_E;
        *xTarget = X_TARGET_E;
        *yTarget = Y_TARGET_E;
        *finalXTarget = FINAL_X_TARGET_E;
        *postRampYDown = POST_RAMP_Y_DOWN_E;
        *switchX = SWITCH_X_E;
        *switchY = SWITCH_Y_E;
        break;
    case 'F':
        *supXTarget = SUP_X_TARGET_F;
        *xTarget = X_TARGET_F;
        *yTarget = Y_TARGET_F;
        *finalXTarget = FINAL_X_TARGET_F;
        *postRampYDown = POST_RAMP_Y_DOWN_F;
        *switchX = SWITCH_X_F;
        *switchY = SWITCH_Y_F;
        break;
    case 'G':
        *supXTarget = SUP_X_TARGET_G;
        *xTarget = X_TARGET_G;
        *yTarget = Y_TARGET_G;
        *finalXTarget = FINAL_X_TARGET_G;
        *postRampYDown = POST_RAMP_Y_DOWN_G;
        *switchX = SWITCH_X_G;
        *switchY = SWITCH_Y_G;
        break;
    case 'H':
        *supXTarget = SUP_X_TARGET_H;
        *xTarget = X_TARGET_H;
        *yTarget = Y_TARGET_H;
        *finalXTarget = FINAL_X_TARGET_H;
        *postRampYDown = POST_RAMP_Y_DOWN_H;
        *switchX = SWITCH_X_H;
        *switchY = SWITCH_Y_H;
        break;
    }
}

