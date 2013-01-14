#include "WPILib.h"
#include "math.h"
#include "AnalogChannel.h"

/**
 * Measures potentiometer values plugged into slot 1 in the analouge breakout board and
 * prints out the angle it is at.
 */
class RobotDemo : public SimpleRobot {
	AnalogChannel potentiometer;
public:
	RobotDemo(void) :
		potentiometer(1,1)
	{
	}

	void OperatorControl(void)
	{
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			//The potentiometer can turn up to 270 degrees, and returns 5 volts at maximum output.
			//Therefore, angle = voltage times 5/270, or 1/54.
			screen->PrintfLine(DriverStationLCD::kUser_Line1,"Angle %f", (1/54)*potentiometer.GetVoltage());
			screen->UpdateLCD();
			Wait(0.1);
		}

	}
};
START_ROBOT_CLASS(RobotDemo);
