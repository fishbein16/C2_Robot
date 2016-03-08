#ifndef BUTTONSWITCH_H
#define BUTTONSWITCH_H

#include <FEHServo.h>

#define ROT_MIN         500.0
#define ROT_MAX         2355.0
#define FOR_BACK_MIN    500.0
#define FOR_BACK_MAX    2283.0

#define SERVO_OUT       120.0
#define SERVO_IN        60.0
#define SERVO_OUT_MID   130.0
#define BLUE_BUTTON     180.0
#define RED_BUTTON      90.0
#define MID_SWITCH      95.0
#define LEFT_SWITCH     10.0
#define RIGHT_SWITCH    170.0
#define LEFT_MID_GAP    45.0
#define RIGHT_MID_GAP   135.0

class ButtonSwitch
{
public:
    ButtonSwitch();
    void ArmOut();
    void ArmIn();
    void ArmOutMid();
    void ToBlueButton();
    void ToRedButton();
    void ToMiddleSwitch();
    void ToLeftSwitch();
    void ToRightSwitch();
    void ToLeftMidGap();
    void ToRightMidGap();

private:
    FEHServo* rotationServo;
    FEHServo* forBackServo;
};

extern ButtonSwitch* buttonSwitch;

#endif // BUTTONSWITCH_H
