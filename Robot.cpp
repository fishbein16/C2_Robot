#include "Robot.h"

Robot::Robot()
{
  leftSensor = new AnalogInputPin(FEHIO::P0_0);
  middleSensor = new AnalogInputPin(FEHIO::P0_1);
  rightSensor = new AnalogInputPin(FEHIO::P0_1);
  
  lineState = STATE_IDLE;
}

void Robot::LineFollowing()
{
  while(true) //Change later for some sort of condition
  {
    leftSeen = left.Value() > LEFT_THRESHOLD;
    rightSeen = right.Value() > MID_THRESHOLD;
    midSeen = middle.Value() > RIGHT_THRESHOLD;

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

  }
}
