#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "DriveSystem.h"
#include "Robot.h"

int main(void)
{
    while (true) {
        LCD.Clear();
        LCD.WriteLine(robot->StartValue());
        while (!(robot->IsRed(robot->StartValue())))
        {
            LCD.WriteLine(robot->StartValue());
        }


    drive->ResetEncoders();

    drive->MoveBackwards(40.0);

    while((drive->GetLeftEncoderCounts() < 1500.0));

//    LCD.Write("Left Encoder: ");
//    LCD.WriteLine(drive->GetLeftEncoderCounts());

//    LCD.Write("Right Encoder: ");
//    LCD.WriteLine(drive->GetRightEncoderCounts()*1.75-300);

    drive->Stop();

    drive->ZeroTurnLeft(55.0);

    drive->MoveBackwards(40.0);

    drive->ResetEncoders();

    while((drive->GetLeftEncoderCounts() < 2500.0));

    drive->Stop();


    while(true)
    {
        LCD.Clear();
        LCD.Write("Fuel Light Value: ");
        LCD.WriteLine(robot->FuelValue());

        LCD.Write("Start Light Value: ");
        LCD.WriteLine(robot->StartValue());

        while (robot->StartButton());
    }



    }
    return 0;
}

