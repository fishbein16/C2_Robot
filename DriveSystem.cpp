#include "DriveSystem.h"

DriveSystem* drive;

DriveSystem::DriveSystem()
{
  //Initialize stuff
  leftDrive = new FEHMotor(FEHMotor::Motor1);
  rightDrive = new FEHMotor(FEHMotor::Motor0);
  
  //Variables that must be initialized before running the robot
}

void DriveSystem::MoveForward(float percent)
{
  leftDrive.SetPercent(percent);
  rightDrive.SetPercent(percent);
}

void DriveSystem::MoveBackwards(float percent)
{
  leftDrive.SetPercent(-1*percent);
  rightDrive.SetPercent(-1*percent);
}

void DriveSystem::ZeroTurnRight(float angle)
{
  //Encoder calculations here
}

void DriveSystem::ZeroTurnLeft(float angle)
{
  //Encoder calculations here
}

void DriveSystem::ForwardTurn(float rightPercent, float leftPercent)
{
  rightDrive.SetPercent(rightPercent);
  leftDrive.SetPercent(leftPercent);
}

void DriveSytem::BackwardsTurn(float rightPercent, float leftPercent)
{
  rightDrive.SetPercent(-1*rightPercent);
  leftDrive.SetPercent(-1*leftPercent);
}
