#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <FEHMotor.h>

class DriveSystem
{
public:
    DriveSystem();
    void ();

private:
    FEHMotor leftDrive;
    FEHMotor rightDrive;
};

//Making object pointer global
extern DriveSystem* drive;

#endif // DRIVESYSTEM_H
