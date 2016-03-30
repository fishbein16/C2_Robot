#ifndef SUPPLYARM_H
#define SUPPLYARM_H

#include <FEHServo.h>

#define SUPPLY_SERVO_MIN    500
#define SUPPLY_SERVO_MAX    2340

#define PICK_UP             180.0
#define DROP_OFF            20.0

class SupplyArm
{
public:
    SupplyArm();
    void ToPickUp();
    void ToDropOff();
private:
    FEHServo* supplyServo;
};

extern SupplyArm* supplyArm;

#endif // SUPPLYARM_H
