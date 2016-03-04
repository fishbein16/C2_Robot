#include "DriveSystem.h"

DriveSystem* drive = new DriveSystem();

DriveSystem::DriveSystem()
{
  //Initialize stuff
  rightDrive = new FEHMotor(FEHMotor::Motor0, 12.0);
  leftDrive = new FEHMotor(FEHMotor::Motor1, 12.0);

  rightEncoder = new DigitalInputPin(FEHIO::P1_0);
  leftEncoder = new DigitalInputPin(FEHIO::P1_1);

  leftSensor = new AnalogInputPin(FEHIO::P0_0);
  middleSensor = new AnalogInputPin(FEHIO::P0_1);
  rightSensor = new AnalogInputPin(FEHIO::P0_2);

  lineState = STATE_IDLE;
}

void DriveSystem::WaitForSetpoint(int setpoint)
{
  int leftCounts = 0;
  int rightCounts = 0;
  bool oldLeftValue = leftEncoder->Value();
  bool oldRightValue = rightEncoder->Value();
  while(rightCounts < setpoint)
  {
    LCD.Write("Left Encoder: ");
    LCD.WriteLine(leftCounts);

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
  WaitForSetpoint(counts);
  rightDrive->Stop();
  leftDrive->Stop();
}

void DriveSystem::ZeroTurnCounter(float angle)
{
    int counts = angle/90 * 48;
    leftDrive->SetPercent(30.0);
    rightDrive->SetPercent(-1*30.0);
    WaitForSetpoint(counts);
    rightDrive->Stop();
    leftDrive->Stop();

}

void DriveSystem::ForwardTurn(float rightPercent, float leftPercent)
{
  rightDrive->SetPercent(-1 * rightPercent);
  leftDrive->SetPercent(-1 * leftPercent);
}

void DriveSystem::BackwardsTurn(float rightPercent, float leftPercent)
{
  rightDrive->SetPercent(rightPercent);
  leftDrive->SetPercent(leftPercent);
}

void DriveSystem::Stop()
{
  rightDrive->Stop();
  leftDrive->Stop();
}

void DriveSystem::LineFollowingFunc(int target)
{
    int leftCount = 0;
    int rightCount = 0;
    bool oldLeftValue;
    bool oldRightValue;

    int majorCount = 0;

    LineFollowing lastLineState = STATE_IDLE;

    while(true) //Change later for some sort of condition
    {
        leftSeen = leftSensor->Value() > LEFT_THRESHOLD;
        rightSeen = rightSensor->Value() > MID_THRESHOLD;
        midSeen = middleSensor->Value() > RIGHT_THRESHOLD;

        if(midSeen && (!leftSeen && !rightSeen)) {
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
            drive->ForwardTurn(FULL_PERCENT, FULL_PERCENT);
            LCD.WriteLine("STATE_STRAIGHT");
            break;
        case STATE_MINOR_LEFT:
            drive->ForwardTurn(MINOR_PERCENT, FULL_PERCENT);
            LCD.WriteLine("STATE_MIL");
            break;
        case STATE_MINOR_RIGHT:
            drive->ForwardTurn(FULL_PERCENT, MINOR_PERCENT);
            LCD.WriteLine("STATE_MIR");
            break;
        case STATE_MAJOR_LEFT:
            drive->ForwardTurn(MAJOR_PERCENT, FULL_PERCENT);
            LCD.WriteLine("STATE_MAL");
            break;
        case STATE_MAJOR_RIGHT:
            drive->ForwardTurn(FULL_PERCENT, MAJOR_PERCENT);
            LCD.WriteLine("STATE_MAR");
            if(lastLineState != lineState)
            {
                majorCount++;
            }

            if(majorCount == 2)
            {
                oldLeftValue = leftEncoder->Value();
                oldRightValue = rightEncoder->Value();
            }
            break;
        case STATE_IDLE:
            drive->Stop();
            LCD.WriteLine("STATE_IDLE");
            break;
        }

        lastLineState = lineState;

        if(majorCount == 2)
        {
            LCD.Write("Left Encoder: ");
            LCD.WriteLine(leftCount);

            LCD.Write("RightEncoder: ");
            LCD.WriteLine(rightCount);

            bool newLeftValue = leftEncoder->Value();
            if(newLeftValue != oldLeftValue)
            {
                leftCount++;
                oldLeftValue = newLeftValue;
            }

            bool newRightValue = rightEncoder->Value();
            if(newRightValue != oldRightValue)
            {
              rightCount++;
              oldRightValue = newRightValue;
            }
        }
        if((leftCount + rightCount) / 2.0 >= target)
        {
            break;
        }
    }
}
