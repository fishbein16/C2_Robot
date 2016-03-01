#ifndef ROBOT_H
#define ROBOT_H

#include <FEHIO.h>
#include <FEHLCD.h>
#include "DriveSystem.h"
#include "ButtonSwitch.h"

#define LEFT_THRESHOLD              0.0
#define MID_THRESHOLD               0.0
#define RIGHT_THRESHOLD             0.0

#define RED_BLUE_THRESHOLD          0.0
#define BLUE_NO_LIGHT_THRESHOLD     0.0

#define FULL_PERCENT                50
#define MINOR_PERCENT               30
#define MAJOR_PERCENT               10

enum LineFollowing {
    STATE_STRAIGHT,
    STATE_MINOR_LEFT,
    STATE_MINOR_RIGHT,
    STATE_MAJOR_LEFT,
    STATE_MAJOR_RIGHT,
    STATE_IDLE
};

class Robot
{
public:
  Robot();
  void LineFollowingFunc(); //Stop condition as parameter?
  float FuelValue();
  float StartValue();
  void FlipSwitches(int left, int middle, int right);
  void PressButton();

private:
  AnalogInputPin* leftSensor;
  AnalogInputPin* middleSensor;
  AnalogInputPin* rightSensor;

  AnalogInputPin* fuelSensor;
  AnalogInputPin* startSensor;

  bool leftSeen;
  bool midSeen;
  bool rightSeen;

  LineFollowing lineState;
};

extern Robot* robot;

#endif //ROBOT_H
