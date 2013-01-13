#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive rightdrive;
	RobotDrive leftdrive;// robot drive system
	Joystick stick; // must be a logitech controller, otherwise this will be difficult for the driver

public:
	RobotDemo(void):
		rightdrive(1,2),
		leftdrive(3,4),
		stick(1)
	{
		rightdrive.SetExpiration(0.1);
		leftdrive.SetExpiration(0.1);
	}

	void Autonomous(void)
	{
		rightdrive.SetSafetyEnabled(false);
		leftdrive.SetSafetyEnabled(false);
	}

	/**
	 * Runs tank drive with four motors 
	 */
	void OperatorControl(void)
	{
		rightdrive.SetSafetyEnabled(true);
		leftdrive.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			rightdrive.TankDrive(-stick.GetY(),stick.GetY());
			leftdrive.TankDrive(stick.GetTwist(),-stick.GetTwist());
			
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

