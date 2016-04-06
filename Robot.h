#ifndef ROBOT_H
#define ROBOT_H

#include <FEHIO.h>
#include <FEHLCD.h>
#include <cstring>
#include <FEHRPS.h>
#include "DriveSystem.h"
#include "ButtonSwitch.h"

#define RED_BLUE_THRESHOLD          0.5
#define BLUE_NO_LIGHT_THRESHOLD     1.0

//Course A
#define SUP_X_TARGET_A          28.3 //26.3  28.4
#define X_TARGET_A              30.0
#define Y_TARGET_A              64.1

#define SWITCH_X_A              6.0
#define SWITCH_Y_A              42.0

#define FINAL_X_TARGET_A        3.4
#define POST_RAMP_Y_DOWN_A      21.500

//Course B
#define SUP_X_TARGET_B          28.3 //26.3  28.4
#define X_TARGET_B              30.0
#define Y_TARGET_B              64.1

#define SWITCH_X_B              6.0
#define SWITCH_Y_B              42.0

#define FINAL_X_TARGET_B        3.400
#define POST_RAMP_Y_DOWN_B      21.500

//Course C
#define SUP_X_TARGET_C          28.1 //26.3  28.4
#define X_TARGET_C              30.2
#define Y_TARGET_C              63.9

#define SWITCH_X_C              6.0
#define SWITCH_Y_C              42.0

#define FINAL_X_TARGET_C        3.400
#define POST_RAMP_Y_DOWN_C      21.500

//Course D
#define SUP_X_TARGET_D          28.3 //26.3  28.4
#define X_TARGET_D              29.8
#define Y_TARGET_D              64.1

#define SWITCH_X_D              6.0
#define SWITCH_Y_D              42.0

#define FINAL_X_TARGET_D        3.400
#define POST_RAMP_Y_DOWN_D      21.500

//Course E
#define SUP_X_TARGET_E          29.3 //26.3  28.4 28.3
#define X_TARGET_E              30.2
#define Y_TARGET_E              64.1

#define SWITCH_X_E              6.0
#define SWITCH_Y_E              42.0

#define FINAL_X_TARGET_E        3.400
#define POST_RAMP_Y_DOWN_E      21.500

//Course F
#define SUP_X_TARGET_F          28.3 //26.3  28.4
#define X_TARGET_F              30.0
#define Y_TARGET_F              64.1

#define SWITCH_X_F              6.0
#define SWITCH_Y_F              42.0

#define FINAL_X_TARGET_F        3.400
#define POST_RAMP_Y_DOWN_F      21.500

//Course G
#define SUP_X_TARGET_G          28.3 //26.3  28.4
#define X_TARGET_G              30.0
#define Y_TARGET_G              64.1

#define SWITCH_X_G              6.0
#define SWITCH_Y_G              42.0

#define FINAL_X_TARGET_G        3.400
#define POST_RAMP_Y_DOWN_G      21.500

//Course H
#define SUP_X_TARGET_H          28.3 //26.3  28.4
#define X_TARGET_H              30.0
#define Y_TARGET_H              64.1

#define SWITCH_X_H              6.0
#define SWITCH_Y_H              42.0

#define FINAL_X_TARGET_H        3.400
#define POST_RAMP_Y_DOWN_H      21.500

#define YELLOW_BLUE_THRESHOLD   1.25


class Robot
{
public:
  Robot();
  bool Start();
  float FuelValue();
  float StartValue();
  void FlipSwitches(int left, int middle, int right);
  bool IsRed();
  bool IsBlue();
  void PressButton();
  void SelectRPSRegionVariables(float *supXTarget, float *xTarget, float *yTarget, float *finalXTarget, float *postRampYDown, float *switchX, float *switchY);

private:
  AnalogInputPin* fuelSensor;
  AnalogInputPin* startSensor;

  bool isRed;
};

extern Robot* robot;

#endif //ROBOT_H
