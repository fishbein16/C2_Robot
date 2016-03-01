#ifndef BUTTONSWITCH_H
#define BUTTONSWITCH_H

#include <FEHServo.h>

#define ROT_MIN         500.0
#define ROT_MAX         2355.0
#define FOR_BACK_MIN    500.0
#define FOR_BACK_MAX    2283.0

#define SERVO_OUT       0.0
#define SERVO_IN        0.0
#define BLUE_BUTTON     0.0
#define RED_BUTTON      0.0
#define MID_SWITCH      0.0
#define LEFT_SWITCH     0.0
#define RIGHT_SWITCH    0.0

class ButtonSwitch
{
public:
    ButtonSwitch();
    void ArmOut();
    void ArmIn();
    void ToBlueButton();
    void ToRedButton();
    void ToMiddleSwitch();
    void ToLeftSwitch();
    void ToRightSwitch();

private:
    FEHServo* rotationServo;
    FEHServo* forBackServo;
};

extern ButtonSwitch* buttonSwitch;

#endif // BUTTONSWITCH_H
