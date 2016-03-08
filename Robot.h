#ifndef ROBOT_H
#define ROBOT_H

#include <FEHIO.h>
#include <FEHLCD.h>
#include "DriveSystem.h"
#include "ButtonSwitch.h"

#define RED_BLUE_THRESHOLD          0.5
#define BLUE_NO_LIGHT_THRESHOLD     1.0

class Robot
{
public:
  Robot();
  bool Start();
  float FuelValue();
  float StartValue();
  void FlipSwitches(int left, int middle, int right);
  void PressButton();

private:
  AnalogInputPin* fuelSensor;
  AnalogInputPin* startSensor;

};

extern Robot* robot;

#endif //ROBOT_H
