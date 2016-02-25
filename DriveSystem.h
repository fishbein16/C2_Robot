#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <FEHMotor.h>
#include <FEHIO.h>

class DriveSystem
{
public:
    DriveSystem();
    int GetLeftEncoderCounts();
    int GetRightEncoderCounts();
    void ResetEncoders();
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

    DigitalEncoder* rightEncoder;
    DigitalEncoder* leftEncoder;
};

//Making object pointer global
extern DriveSystem* drive;

#endif // DRIVESYSTEM_H
