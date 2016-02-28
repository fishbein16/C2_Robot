#ifndef ROBOT_H
#define ROBOT_H

#include <FEHIO.h>
#include <FEHLCD.h>
#include "DriveSystem.h"

#define LEFT_THRESHOLD              0.0
#define MID_THRESHOLD               0.0
#define RIGHT_THRESHOLD             0.0

#define RED_BLUE_THRESHOLD          0.9
#define BLUE_NO_LIGHT_THRESHOLD     1.3

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
  bool StartButton();
  bool IsRed(float light);
  bool IsLit(float light);
  
private:
  AnalogInputPin* leftSensor;
  AnalogInputPin* middleSensor;
  AnalogInputPin* rightSensor;
  
  AnalogInputPin* fuelSensor;
  AnalogInputPin* startSensor;

  ButtonBoard* buttons;
  
  bool leftSeen;
  bool midSeen;
  bool rightSeen;
  
  LineFollowing lineState;
};

extern Robot* robot;

#endif //ROBOT_H
