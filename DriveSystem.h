#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <FEHMotor.h>

class DriveSystem
{
public:
    DriveSystem();
    void MoveForward(float percent);
    void MoveBackwards(float percent);
    void ZeroTurnRight(float angle);
    void ZeroTurnLeft(float angle);
    void ForwardTurn(float rightPercent, float leftPercent);
    void BackwardsTurn(float rightPercent, float leftPercent);

private:
    FEHMotor leftDrive;
    FEHMotor rightDrive;
};

//Making object pointer global
extern DriveSystem* drive;

#endif // DRIVESYSTEM_H
