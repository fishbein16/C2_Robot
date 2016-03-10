#include "SupplyArm.h"

SupplyArm* supplyArm = new SupplyArm();

SupplyArm::SupplyArm()
{
    supplyServo = new FEHServo(FEHServo::Servo5);

    supplyServo->SetMin(SUPPLY_SERVO_MIN);
    supplyServo->SetMax(SUPPLY_SERVO_MAX);
}

void SupplyArm::ToPickUp()
{
    supplyServo->SetDegree(PICK_UP);
}

void SupplyArm::ToDropOff()
{
    supplyServo->SetDegree(DROP_OFF);
}
