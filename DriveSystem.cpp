#include "DriveSystem.h"

DriveSystem* drive = new DriveSystem();

DriveSystem::DriveSystem()
{
  //Initialize stuff
  rightDrive = new FEHMotor(FEHMotor::Motor0, 12.0);
  leftDrive = new FEHMotor(FEHMotor::Motor1, 12.0);

  rightEncoder = new DigitalInputPin(FEHIO::P1_0);
  leftEncoder = new DigitalInputPin(FEHIO::P1_2);

  leftSensor = new AnalogInputPin(FEHIO::P0_6);
  middleSensor = new AnalogInputPin(FEHIO::P0_3);
  rightSensor = new AnalogInputPin(FEHIO::P0_0);

  lineState = STATE_STRAIGHT;
}

void DriveSystem::WaitForSetpointAngle(int setpoint)
{
  int leftCounts = 0;
  int rightCounts = 0;
  bool oldLeftValue = leftEncoder->Value();
  bool oldRightValue = rightEncoder->Value();
  while((leftCounts + rightCounts)/2 < setpoint)
  {
//    LCD.Write("Left Encoder: ");
//    LCD.WriteLine(leftCounts);

    LCD.Write("RightEncoder: ");
    LCD.WriteLine(rightCounts);

    bool newLeftValue = leftEncoder->Value();
    if(newLeftValue != oldLeftValue)
    {
        leftCounts++;
        oldLeftValue = newLeftValue;
    }

    bool newRightValue = rightEncoder->Value();
    if(newRightValue != oldRightValue)
    {
      rightCounts++;
      oldRightValue = newRightValue;
    }
  }
}

void DriveSystem::WaitForSetpointInch(float setpoint)
{
    int leftCounts = 0;
    int rightCounts = 0;
    bool oldLeftValue = leftEncoder->Value();
    bool oldRightValue = rightEncoder->Value();

    int encoderSetpoint = setpoint * INCH_COUNT_CONVERSION;

    while((leftCounts + rightCounts)/2 < encoderSetpoint)
    {
      LCD.Write("Left Encoder: ");
      LCD.WriteLine(leftCounts);

      LCD.Write("Right Encoder: ");
      LCD.WriteLine(rightCounts);

      bool newLeftValue = leftEncoder->Value();
      if(newLeftValue != oldLeftValue)
      {
          leftCounts++;
          oldLeftValue = newLeftValue;
      }

      bool newRightValue = rightEncoder->Value();
      if(newRightValue != oldRightValue)
      {
        rightCounts++;
        oldRightValue = newRightValue;
      }
    }
}

void DriveSystem::MoveForward(float percent)
{
  leftDrive->SetPercent(-1 * percent);
  rightDrive->SetPercent(-1 * percent);
}

void DriveSystem::MoveBackwards(float percent)
{
  leftDrive->SetPercent(percent);
  rightDrive->SetPercent(percent);
}

void DriveSystem::ZeroTurnClockwise(float angle)
{
  int counts = angle/90 * 48;
  leftDrive->SetPercent(-1*30.0);
  rightDrive->SetPercent(30.0);
  WaitForSetpointAngle(counts);
  rightDrive->Stop();
  leftDrive->Stop();
}

void DriveSystem::ZeroTurnCounter(float angle)
{
    int counts = angle/90 * 48;
    leftDrive->SetPercent(30.0);
    rightDrive->SetPercent(-1*30.0);
    WaitForSetpointAngle(counts);
    rightDrive->Stop();
    leftDrive->Stop();

}

void DriveSystem::ForwardTurn(float leftPercent, float rightPercent)
{
  leftDrive->SetPercent(-1 * leftPercent);
  rightDrive->SetPercent(-1 * rightPercent);
}

void DriveSystem::BackwardsTurn(float leftPercent, float rightPercent)
{
  leftDrive->SetPercent(leftPercent);
  rightDrive->SetPercent(rightPercent);
}

void DriveSystem::Stop()
{
  leftDrive->Stop();
  rightDrive->Stop();
}

void DriveSystem::LineFollowingFunc()
{
    bool timeOut = false;

    float start = 0;

    float timer = TimeNow();

    LineFollowing lastLineState = STATE_STRAIGHT;

    while(!timeOut && TimeNow() - timer < 12) //Change later for some sort of condition
    {
        leftSeen = leftSensor->Value() < LEFT_THRESHOLD;
        rightSeen = rightSensor->Value() < RIGHT_THRESHOLD;
        midSeen = middleSensor->Value() < MID_THRESHOLD;

        if(midSeen && (!leftSeen && !rightSeen))
        {
            lineState = STATE_STRAIGHT;
        }
        else if((midSeen && rightSeen) &&!leftSeen)
        {
            lineState = STATE_MINOR_RIGHT;
        }
        else if ((midSeen && leftSeen) && !rightSeen)
        {
            lineState = STATE_MINOR_LEFT;
        }
        else if (leftSeen && (!rightSeen && !midSeen))
        {
            lineState = STATE_MAJOR_LEFT;
        }
        else if (rightSeen && (!leftSeen && !midSeen))
        {
            lineState = STATE_MAJOR_RIGHT;
        }

        switch(lineState)
        {
        case STATE_STRAIGHT:
            if(TimeNow() - timer < 10)
            {
                ForwardTurn(FULL_LEFT_PERCENT, FULL_RIGHT_PERCENT);
            }
            else
            {
                ForwardTurn(FULL_LEFT_PERCENT - 10, FULL_RIGHT_PERCENT);
            }
            LCD.WriteLine("STATE_STRAIGHT");
            if(start != 0 && TimeNow() - start > 1.5)
            {
                timeOut = true;
            }
            break;
        case STATE_MINOR_LEFT:
            ForwardTurn(MINOR_PERCENT, FULL_RIGHT_NOT_STRAIGHT);
            LCD.WriteLine("STATE_MIL");
            break;
        case STATE_MINOR_RIGHT:
            ForwardTurn(FULL_LEFT_PERCENT, MINOR_PERCENT);
            LCD.WriteLine("STATE_MIR");
            break;
        case STATE_MAJOR_LEFT:
            ForwardTurn(MAJOR_PERCENT, FULL_RIGHT_NOT_STRAIGHT);
            LCD.WriteLine("STATE_MAL");
            break;
        case STATE_MAJOR_RIGHT:
            ForwardTurn(FULL_LEFT_PERCENT, MAJOR_PERCENT);
            LCD.WriteLine("STATE_MAR");
            break;
        case STATE_IDLE:
            Stop();
            LCD.WriteLine("STATE_IDLE");
            break;
        }

        if(lineState == STATE_STRAIGHT && lastLineState != lineState)
        {
            start = TimeNow();
        }
        else if(lineState != STATE_STRAIGHT)
        {
            start = 0;
        }

        lastLineState = lineState;
    }

    Stop();
}

void DriveSystem::LineFollowingBack()
{
    bool startFollowing = false;
    bool lastRight = false;

    while(!startFollowing)
    {
        MoveBackwards(50);
        rightSeen = rightSensor->Value() < RIGHT_THRESHOLD;
        if(lastRight && !rightSeen)
        {
            startFollowing = true;
            Stop();
        }
        lastRight = rightSeen;
    }
}
