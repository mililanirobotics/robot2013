#include "WPILib.h"
#include "math.h"
#include "AnalogChannel.h"

/**
 * Measures potentiometer values plugged into slot 1 in the analouge breakout board and
 * prints out the angle it is at.
 */
class RobotDemo : public SimpleRobot 
{
	AnalogChannel potentiometer;
public:
	RobotDemo(void):
		potentiometer(1,1)
	{
		
	}

	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			//The potentiometer can turn up to 270 degrees, and returns 5 volts at maximum output.
			//Therefore, ideally angle = voltage times 270/5, or 54.
			//However, the potentiometer we have jumps a bit, and is only reliable up to 180 degrees.
			//At 180 degrees, the potentiometer outputs 2 volts.
			//Therefore, angle = voltage times 180/2, or 90.
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Angle %f", potentiometer.GetVoltage()*90);
			screen->UpdateLCD();
			Wait(0.1);
		}

	}
};
START_ROBOT_CLASS(RobotDemo);
