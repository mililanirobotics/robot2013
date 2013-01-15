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
		potentiometer(1, 1) {
	}

	void OperatorControl(void) {
		DriverStationLCD *screen = DriverStationLCD::GetInstance();
		while (true) {
			screen->PrintfLine(DriverStationLCD::kUser_Line1, "Angle %f", potentiometer.GetVoltage());
			screen->UpdateLCD();
		}

	}
};
START_ROBOT_CLASS(RobotDemo)
;

