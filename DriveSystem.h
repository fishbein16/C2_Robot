#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>

class DriveSystem
{
public:
    DriveSystem();
    void WaitForSetpoint(int setpoint);
    void MoveForward(float percent);
    void MoveBackwards(float percent);
    void ZeroTurnRight(float angle);
    void ZeroTurnLeft(float angle);
    void ForwardTurn(float rightPercent, float leftPercent);
    void BackwardsTurn(float rightPercent, float leftPercent);
    void Stop();

private:
    FEHMotor* leftDrive;
    FEHMotor* rightDrive;

    DigitalInputPin* rightEncoder;
    DigitalInputPin* leftEncoder;
};

//Making object pointer global
extern DriveSystem* drive;

#endif // DRIVESYSTEM_H
