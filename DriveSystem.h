#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>

#include "Robot.h"

#define LEFT_THRESHOLD              0.500
#define MID_THRESHOLD               0.160
#define RIGHT_THRESHOLD             0.250

#define FULL_PERCENT                30
#define MINOR_PERCENT               -5
#define MAJOR_PERCENT               -30

#define INCH_COUNT_CONVERSION       48/10.5

enum LineFollowing {
    STATE_STRAIGHT,
    STATE_MINOR_LEFT,
    STATE_MINOR_RIGHT,
    STATE_MAJOR_LEFT,
    STATE_MAJOR_RIGHT,
    STATE_IDLE
};

class DriveSystem
{
public:
    DriveSystem();
    void WaitForSetpointAngle(int setpoint);
    void WaitForSetpointInch(double setpoint);
    void MoveForward(float percent);
    void MoveBackwards(float percent);
    void ZeroTurnClockwise(float angle);
    void ZeroTurnCounter(float angle);
    void ForwardTurn(float rightPercent, float leftPercent);
    void BackwardsTurn(float rightPercent, float leftPercent);
    void Stop();
    void LineFollowingFunc();
    void LineFollowingBack();

private:
    FEHMotor* leftDrive;
    FEHMotor* rightDrive;

    DigitalInputPin* rightEncoder;
    DigitalInputPin* leftEncoder;

    AnalogInputPin* leftSensor;
    AnalogInputPin* middleSensor;
    AnalogInputPin* rightSensor;

    bool leftSeen;
    bool midSeen;
    bool rightSeen;

    LineFollowing lineState;
};

//Making object pointer global
extern DriveSystem* drive;

#endif // DRIVESYSTEM_H
