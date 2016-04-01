#ifndef BUTTONSWITCH_H
#define BUTTONSWITCH_H

#include <FEHServo.h>

#define ROT_MIN         500.0
#define ROT_MAX         2355.0
#define FOR_BACK_MIN    500.0
#define FOR_BACK_MAX    2283.0

#define SERVO_OUT       120.0
#define SERVO_PULL      100.0
#define SERVO_FULL_IN   30.0
#define SERVO_IN        60.0
#define SERVO_IN_MID    70.0
#define START_ANGLE     45.0
#define SERVO_OUT_MID   150.0
#define BLUE_BUTTON     0.0
#define RED_BUTTON      65.0
#define NEUTRAL_BUTTON  35.0
#define MID_SWITCH_PUSH 75.0
#define MID_SWITCH_PULL 60.0
#define LEFT_SWITCH     150.0
#define RIGHT_SWITCH    10.0
#define LEFT_MID_GAP    115.0
#define RIGHT_MID_GAP   45.0

class ButtonSwitch
{
public:
    ButtonSwitch();
    void ArmOut();
    void ArmPull();
    void ArmFullIn();
    void ArmIn();
    void ArmInMid();
    void ArmOutMid();
    void ToStart();
    void ToBlueButton();
    void ToRedButton();
    void ToMiddleSwitchPush();
    void ToMiddleSwitchPull();
    void ToLeftSwitch();
    void ToRightSwitch();
    void ToLeftMidGap();
    void ToRightMidGap();
    void NeutralButton();

private:
    FEHServo* rotationServo;
    FEHServo* forBackServo;
};

extern ButtonSwitch* buttonSwitch;

#endif // BUTTONSWITCH_H
