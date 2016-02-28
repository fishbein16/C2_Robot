#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "DriveSystem.h"
#include "Robot.h"

int main(void)
{
    while (true) {
        LCD.Clear();
//        LCD.WriteLine(robot->StartValue());
//        while (!(robot->IsRed(robot->StartValue())))
//        {
//            LCD.WriteLine(robot->StartValue());
//        }

        while (robot->StartButton());

    drive->ResetEncoders();

    drive->MoveBackwards(40.0);

    while((drive->GetLeftEncoderCounts() < 2500.0));

    LCD.Write("Left Encoder: ");
    LCD.WriteLine(drive->GetLeftEncoderCounts());

    LCD.Write("Right Encoder: ");
    LCD.WriteLine(drive->GetRightEncoderCounts());

    drive->Stop();

//    drive->ZeroTurnLeft(75.0);

//    drive->MoveBackwards(40.0);

//    drive->ResetEncoders();

//    while((drive->GetLeftEncoderCounts() < 5200.0));

//    drive->Stop();


    while(true)
    {
//        LCD.Clear();
//        LCD.Write("Fuel Light Value: ");
//        LCD.WriteLine(robot->FuelValue());

        LCD.Write("Fuel Light Value: ");
        if (robot->IsLit(robot->FuelValue()))
        {
           if (robot->IsRed(robot->FuelValue()))
           {
              LCD.WriteLine("RED LIGHT MUTHA FLUCKA");
           }
           else
           {
              LCD.WriteLine("BLUE LIGHTS 4 DAYS");
           }
        }

        while (robot->StartButton());
    }



    }
    return 0;
}

