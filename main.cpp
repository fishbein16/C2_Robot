#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "DriveSystem.h"
#include "Robot.h"

int main(void)
{
    drive->ResetEncoders();

    drive->MoveBackwards(50.0);

    int start = TimeNow();

    while(TimeNow() - start < 5);

    drive->Stop();

    LCD.Write("Left Encoder: ");
    LCD.WriteLine(drive->GetLeftEncoderCounts());

    LCD.Write("Right Encoder: ");
    LCD.WriteLine(drive->GetRightEncoderCounts());

    while(true)
    {
        LCD.Clear();
        LCD.Write("Fuel Light Value: ");
        LCD.WriteLine(robot->FuelValue());

        LCD.Write("Start Light Value: ");
        LCD.WriteLine(robot->StartValue());

        Sleep(1);
    }
    return 0;
}

