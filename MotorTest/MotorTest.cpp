#include "WPILib.h"

/**
 *  Test code for jaguar motors.
 *  Uses joystick 1's throttle to control speed, and button 1 to toggle motor.
 */
class RobotDemo: public SimpleRobot { // driver station object for getting selections
	Joystick leftstick;
	Jaguar shooter1;
	//Jaguar shooter2;

public:
	RobotDemo(void) :
		leftstick(1),
		shooter1(1)
		
	{

	}
	void OperatorControl() {
		{
			DriverStationLCD *screen = DriverStationLCD::GetInstance();

			while (IsOperatorControl()) {
				screen->PrintfLine(DriverStationLCD::kUser_Line1,"Z input: %f", leftstick.GetThrottle());
				if(leftstick.GetRawButton(2))
				{
					shooter1.Set(leftstick.GetThrottle());
					//shooter2.Set(leftstick.GetThrottle());
				}
				else
				{
					shooter1.Set(0.0);
				}
				if (leftstick.GetRawButton(2))
					servo.Set(0.0);
				if (leftstick.GetRawButton(3))
					servo.Set(1.0);
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo)
;

