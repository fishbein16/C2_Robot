#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0,12.0);
FEHMotor left_motor(FEHMotor::Motor1,12.0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);



    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    //hint: set right motor backwards, left motor forwards

    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent

    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}



int main(void)
{
    int motor_percent = 25 ; //Input power level here
    int expected_counts = 220; //Input theoretical counts here
    int expected_countsL = 574;
    int expected_countsS= 165;
    int expected_countsM= 411;

    //Initialize the screen (GO BUCKS!)
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetFontColor( FEHLCD::Gray );

    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(motor_percent, expected_countsL); //see function
    Sleep(0.25);
    turn_left(motor_percent, expected_counts);
    Sleep(0.25);
    move_forward(motor_percent, expected_countsM); //see function
    Sleep(0.25);
    turn_right(motor_percent, expected_counts);
    Sleep(0.25);
    move_forward(motor_percent, expected_countsS); //see function

    Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    return 0;
}
