#include "WPILib.h"
#include "math.h"
#include "AnalogChannel.h"

/**
 * This code is able to control a two motor system and get encoder values.
 * Note that the drive system takes input from the left and right analog
 * sticks of the Logitech controllers. If you want to use the normal
 * joysticks, then change 
 */
class RobotDemo : public SimpleRobot {
	AnalogChannel potentiometer;
public:
	RobotDemo(void) :
		potentiometer(1)
	{
	}

	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Voltage %f", 3*potentiometer.GetVoltage());
			screen->UpdateLCD();
			Wait(0.1);
		}

	}
};
START_ROBOT_CLASS(RobotDemo);

