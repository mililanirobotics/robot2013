#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick stick;
	Jaguar jaguar;
	
public:
	RobotDemo(void):
	
		stick(1),
		jaguar(2)

	{
		
	}
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	/**
	 * Runs the motors with tank steering. 
	 */
	void OperatorControl(void)
	{ 
		while (IsOperatorControl())
		{
			
		}
		
		
	}
	
	/**
	 * Runs during test mode
	 */
	
};

START_ROBOT_CLASS(RobotDemo);

