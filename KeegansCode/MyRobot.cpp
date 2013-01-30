#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	Joystick rightstick;
	Joystick leftstick;
	Jaguar jag1;
	Jaguar jag2;
	Jaguar jag3;
	Jaguar jag4;
	RobotDrive drive;

public:
	RobotDemo(void):
	
		leftstick(1),
		rightstick(2),
		jag1(3),
		jag2(4),
		jag3(5),
		jag4(6),
		drive(jag1,jag2,jag3,jag4)

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
		
		drive.TankDrive(leftstick,rightstick);
			

	}
	
	/**
	 * Runs during test mode
	 */
	
};

START_ROBOT_CLASS(RobotDemo);

