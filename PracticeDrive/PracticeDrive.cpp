#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive drive;
	Joystick leftStick, rightStick;
	
public:
	RobotDemo(void):
		drive(4,3,2,1),
		leftStick(1),
		rightStick(2)
	{
		
	}

	void Autonomous(void)
	{
		
	}

	/**
	 * Runs tank drive with four motors 
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			drive.TankDrive(leftStick, rightStick);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

