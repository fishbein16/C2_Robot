#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

//Percent for adjusting motor
#define FULL_PERCENT    50
#define MINOR_PERCENT   30
#define MAJOR_PERCENT   10

enum LineFollowing {
    STATE_STRAIGHT,
    STATE_MINOR_LEFT,
    STATE_MINOR_RIGHT,
    STATE_MAJOR_LEFT,
    STATE_MAJOR_RIGHT,
    STATE_IDLE
};

int main(void)
{
    LineFollowing lineState = STATE_IDLE;
    LineFollowing lastLineState = STATE_IDLE;

    AnalogInputPin left(FEHIO::P1_1);
    AnalogInputPin middle(FEHIO::P1_2);
    AnalogInputPin right(FEHIO::P1_3);

    ButtonBoard button(FEHIO::Bank3);

    FEHMotor leftDrive(FEHMotor::Motor1, 12.0);
    FEHMotor rightDrive(FEHMotor::Motor0, 12.0);

    bool leftSeen, rightSeen, midSeen;

    while(button.MiddleReleased());

    while(button.MiddlePressed());

    while(button.MiddleReleased()) {
        leftSeen = left.Value() > 1.2;
        rightSeen = right.Value() > 1.7;
        midSeen = middle.Value() > 1.8;

        if(midSeen && (!leftSeen && ! rightSeen)) {
            lineState = STATE_STRAIGHT;
        }
        else if((midSeen && rightSeen) &&!leftSeen) {
            lineState = STATE_MINOR_RIGHT;
        }
        else if ((midSeen && leftSeen) && !rightSeen) {
            lineState = STATE_MINOR_LEFT;
        }
        else if (leftSeen && (!rightSeen && !midSeen)) {
            lineState = STATE_MAJOR_LEFT;
        }
        else if (rightSeen && (!leftSeen && !midSeen)) {
            lineState = STATE_MAJOR_RIGHT;
        }

        switch(lineState) {
        case STATE_STRAIGHT:
            leftDrive.SetPercent(FULL_PERCENT);
            rightDrive.SetPercent(FULL_PERCENT);
            LCD.WriteLine("STATE_STRAIGHT");
            break;
        case STATE_MINOR_LEFT:
            leftDrive.SetPercent(MINOR_PERCENT);
            rightDrive.SetPercent(FULL_PERCENT);
            LCD.WriteLine("STATE_MIL");
            break;
        case STATE_MINOR_RIGHT:
            leftDrive.SetPercent(FULL_PERCENT);
            rightDrive.SetPercent(MINOR_PERCENT);
            LCD.WriteLine("STATE_MIR");
            break;
        case STATE_MAJOR_LEFT:
            leftDrive.SetPercent(MAJOR_PERCENT);
            rightDrive.SetPercent(FULL_PERCENT);
            LCD.WriteLine("STATE_MAL");
            break;
        case STATE_MAJOR_RIGHT:
            leftDrive.SetPercent(FULL_PERCENT);
            rightDrive.SetPercent(MAJOR_PERCENT);
            LCD.WriteLine("STATE_MAR");
            break;
        case STATE_IDLE:
            leftDrive.Stop();
            rightDrive.Stop();
            LCD.WriteLine("STATE_IDLE");
            break;
        }
        lastLineState = lineState;
    }
    leftDrive.Stop();
    rightDrive.Stop();

    return 0;
}

