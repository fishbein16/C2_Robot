#ifndef ROBOT_H
#define ROBOT_H

#include <FEHIO.h>
#include "DriveSystem.h"

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
  void LineFollowing();
  
private:
  AnalogInputPin left;
  AnalogInputPin middle;
  AnalogInputPin right;
  
  bool leftSeen;
  bool midSeen;
  bool rightSeen;
  
  LineFollowing lineState;
};
