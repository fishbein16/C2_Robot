
#include "Robot.h"

Robot* robot = new Robot();

Robot::Robot()
{
  fuelSensor = new AnalogInputPin(FEHIO::P2_2);
  startSensor = new AnalogInputPin(FEHIO::P2_0);
}

bool Robot::Start()
{
    return StartValue() < RED_BLUE_THRESHOLD;
}

float Robot::FuelValue()
{
    return fuelSensor->Value();
}

float Robot::StartValue()
{
    return startSensor->Value();
}

void Robot::FlipSwitches(int left, int middle, int right)
{
    //insert decision making code here
    //call buttonSwitch->ToBlankSwitch()
}

void Robot::PressButton()
{
    if(FuelValue() < RED_BLUE_THRESHOLD)
    {
        buttonSwitch->ToRedButton();
    }
    else
    {
        buttonSwitch->ToBlueButton();
    }

    //drive forward x counts
    //do something to keep robot in place for five seconds
}
