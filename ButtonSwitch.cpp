#include "ButtonSwitch.h"

ButtonSwitch* buttonSwitch = new ButtonSwitch();

ButtonSwitch::ButtonSwitch()
{
    rotationServo = new FEHServo(FEHServo::Servo7);
    forBackServo = new FEHServo(FEHServo::Servo6);

    rotationServo->SetMax(ROT_MAX);
    rotationServo->SetMin(ROT_MIN);

    forBackServo->SetMax(FOR_BACK_MAX);
    forBackServo->SetMin(FOR_BACK_MIN);
}

void ButtonSwitch::ArmOut()
{
    forBackServo->SetDegree(SERVO_OUT);
}

void ButtonSwitch::ArmFullIn()
{
    forBackServo->SetDegree(SERVO_FULL_IN);
}

void ButtonSwitch::ArmIn()
{
    forBackServo->SetDegree(SERVO_IN);
}

void ButtonSwitch::ArmInMid()
{
    forBackServo->SetDegree(SERVO_IN_MID);
}

void ButtonSwitch::ArmOutMid()
{
    forBackServo->SetDegree(SERVO_OUT_MID);
}

void ButtonSwitch::ToStart()
{
    forBackServo->SetDegree(START_ANGLE);
}

void ButtonSwitch::ToBlueButton()
{
    rotationServo->SetDegree(BLUE_BUTTON);
}

void ButtonSwitch::ToRedButton()
{
    rotationServo->SetDegree(RED_BUTTON);
}

void ButtonSwitch::ToMiddleSwitchPush()
{
    rotationServo->SetDegree(MID_SWITCH_PUSH);
}

void ButtonSwitch::ToMiddleSwitchPull()
{
    rotationServo->SetDegree(MID_SWITCH_PULL);
}

void ButtonSwitch::ToLeftSwitch()
{
    rotationServo->SetDegree(LEFT_SWITCH);
}

void ButtonSwitch::ToRightSwitch()
{
    rotationServo->SetDegree(RIGHT_SWITCH);
}

void ButtonSwitch::ToLeftMidGap()
{
    rotationServo->SetDegree(LEFT_MID_GAP);
}

void ButtonSwitch::ToRightMidGap()
{
    rotationServo->SetDegree(RIGHT_MID_GAP);
}

void ButtonSwitch::NeutralButton()
{
    rotationServo->SetDegree(NEUTRAL_BUTTON);
}
